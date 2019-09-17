/***************************************************
  This is a library for the Adafruit Thermocouple Sensor w/MAX31855K

  Designed specifically to work with the Adafruit Thermocouple Sensor
  ----> https://www.adafruit.com/products/269

  These displays use SPI to communicate, 3 pins are required to
  interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "Adafruit_MAX31855.h"
#ifdef __AVR
  #include <avr/pgmspace.h>
#elif defined(ESP8266)
  #include <pgmspace.h>
#endif

#include <stdlib.h>
#include <SPI.h>


Adafruit_MAX31855::Adafruit_MAX31855(int8_t _sclk, int8_t _cs, int8_t _miso) {
  sclk = _sclk;
  cs = _cs;
  miso = _miso;

  initialized = false;
}

Adafruit_MAX31855::Adafruit_MAX31855(int8_t _cs) {
  cs = _cs;
  sclk = miso = -1;

  initialized = false;
}

void Adafruit_MAX31855::begin(void) {
  //define pin modes
  pinMode(cs, OUTPUT);
  digitalWrite(cs, HIGH);

  MAXSPI = new SPIClass();

  if (sclk == -1) {
    // hardware SPI
    //start and configure hardware SPI
#ifdef ESP32	// if we have ESP32 - where we have 2 HW SPIs
    if(cs==5) MAXSPI->begin(18, 19, 23, 5);	// VSPI - pins SCLK = 18, MISO = 19, MOSI = 23, SS = 5
    else MAXSPI->begin(14, 12, 13, 15);		// HSPI - pins SCLK = 14, MISO = 12, MOSI = 13, SS = 15 - HSPI is default SPI on ESP32
    pinMode(cs, OUTPUT);
#elif		// everything else
    MAXSPI->begin();
#endif
  } else {
    pinMode(sclk, OUTPUT);
    pinMode(miso, INPUT);
  }
  initialized = true;
}

double Adafruit_MAX31855::readInternal(void) {
  uint32_t v;

  v = spiread32();

  // ignore bottom 4 bits - they're just thermocouple data
  v >>= 4;

  // pull the bottom 11 bits off
  float internal = v & 0x7FF;
  // check sign bit!
  if (v & 0x800) {
    // Convert to negative value by extending sign and casting to signed type.
    int16_t tmp = 0xF800 | (v & 0x7FF);
    internal = tmp;
  }
  internal *= 0.0625; // LSB = 0.0625 degrees
  //Serial.print("\tInternal Temp: "); Serial.println(internal);
  return internal;
}

double Adafruit_MAX31855::readCelsius(void) {

  int32_t v;

  v = spiread32();

  //Serial.print("0x"); Serial.println(v, HEX);

  if (v & 0x7) {
    // uh oh, a serious problem!
    return NAN;
  }

  if (v & 0x80000000) {
    // Negative value, drop the lower 18 bits and explicitly extend sign bits.
    v = 0xFFFFC000 | ((v >> 18) & 0x00003FFFF);
  }
  else {
    // Positive value, just drop the lower 18 bits.
    v >>= 18;
  }
  //Serial.println(v, HEX);

  double centigrade = v;

  // LSB = 0.25 degrees C
  centigrade *= 0.25;
  return centigrade;
}

uint8_t Adafruit_MAX31855::readError() {
  return spiread32() & 0x7;
}

double Adafruit_MAX31855::readFarenheit(void) {
  float f = readCelsius();
  f *= 9.0;
  f /= 5.0;
  f += 32;
  return f;
}

uint32_t Adafruit_MAX31855::spiread32(void) {
  int i;
  uint32_t d = 0;

  // backcompatibility!
  if (! initialized) {
    begin();
  }

  digitalWrite(cs, LOW);
  delay(1);

  if(sclk == -1) {
    // hardware SPI

    MAXSPI->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

    d = MAXSPI->transfer(0);
    d <<= 8;
    d |= MAXSPI->transfer(0);
    d <<= 8;
    d |= MAXSPI->transfer(0);
    d <<= 8;
    d |= MAXSPI->transfer(0);

    MAXSPI->endTransaction();
  } else {
    // software SPI

    digitalWrite(sclk, LOW);
    delay(1);

    for (i=31; i>=0; i--) {
      digitalWrite(sclk, LOW);
      delay(1);
      d <<= 1;
      if (digitalRead(miso)) {
	d |= 1;
      }

      digitalWrite(sclk, HIGH);
      delay(1);
    }
  }

  digitalWrite(cs, HIGH);
  //Serial.println(d, HEX);
  return d;
}
