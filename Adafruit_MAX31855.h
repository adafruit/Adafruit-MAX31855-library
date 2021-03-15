/*!
 * @file Adafruit_MAX31855.h
 *
 * This is the documentation for Adafruit's MAX31855 thermocouple breakout
 * driver for the Arduino platform.  It is designed specifically to work with
 * the Adafruit MAX31855 breakout: https://www.adafruit.com/products/269
 *
 * These sensors use SPI to communicate, 3 pins are required
 * to interface with the breakout.
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * Written by Limor Fried/Ladyada for Adafruit Industries.
 *
 * BSD license, all text above must be included in any redistribution.
 *
 */

#ifndef ADAFRUIT_MAX31855_H
#define ADAFRUIT_MAX31855_H

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Adafruit_SPIDevice.h>

/**************************************************************************/
/*!
    @brief  Sensor driver for the Adafruit MAX31855 thermocouple breakout.
*/
/**************************************************************************/
class Adafruit_MAX31855 {
public:
  Adafruit_MAX31855(int8_t _sclk, int8_t _cs, int8_t _miso);
  Adafruit_MAX31855(int8_t _cs, SPIClass *_spi = &SPI);

  bool begin(void);
  double readInternal(void);
  double readCelsius(void);
  double readFahrenheit(void);
  uint8_t readError();

private:
  Adafruit_SPIDevice spi_dev;
  bool initialized = false;

  uint32_t spiread32(void);
};

#endif
