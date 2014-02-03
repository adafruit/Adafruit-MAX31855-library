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
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdlib.h>


Adafruit_MAX31855::Adafruit_MAX31855(int8_t SCLK, int8_t CS, int8_t MISO) {
  sclk = SCLK;
  cs = CS;
  miso = MISO;

  //define pin modes
  pinMode(cs, OUTPUT);
  pinMode(sclk, OUTPUT); 
  pinMode(miso, INPUT);

  digitalWrite(cs, HIGH);
}


double Adafruit_MAX31855::readInternal(void) {
  uint32_t v;

  v = spiread32();

  // ignore bottom 4 bits - they're just thermocouple data
  v >>= 4;

  // pull the bottom 11 bits off
  float internal = v & 0x7FF;
  internal *= 0.0625; // LSB = 0.0625 degrees
  // check sign bit!
  if (v & 0x800) 
    internal *= -1;
  //Serial.print("\tInternal Temp: "); Serial.println(internal);
  return internal;
}

double Adafruit_MAX31855::readCelsius(void) {

  int32_t v;

  v = spiread32();

  //Serial.print("0x"); Serial.println(v, HEX);

  /*
  float internal = (v >> 4) & 0x7FF;
  internal *= 0.0625;
  if ((v >> 4) & 0x800) 
    internal *= -1;
  Serial.print("\tInternal Temp: "); Serial.println(internal);
  */

  if (v & 0x7) {
    // uh oh, a serious problem!
    return NAN; 
  }

  // get rid of internal temp data, and any fault bits
  v >>= 18;
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

  digitalWrite(sclk, LOW);
  _delay_ms(1);
  digitalWrite(cs, LOW);
  _delay_ms(1);

  for (i=31; i>=0; i--)
  {
    digitalWrite(sclk, LOW);
    _delay_ms(1);
    d <<= 1;
    if (digitalRead(miso)) {
      d |= 1;
    }

    digitalWrite(sclk, HIGH);
    _delay_ms(1);
  }

  digitalWrite(cs, HIGH);
  //Serial.println(d, HEX);
  return d;
}
