# Adafruit-MAX31855-library

## Overview

This is the Adafruit MAX31885 Arduino Library.

Tested and works great with the [Adafruit Thermocouple Breakout w/MAX31885K](http://www.adafruit.com/products/269).

These modules use SPI to communicate, 3 pins are required to interface.


## Usage

[Download the .zip here](https://github.com/adafruit/Adafruit-MAX31855-library/archive/master.zip), rename the uncompressed folder `Adafruit_MAX31885`. Check that the `Adafruit_MAX31885` folder contains `Adafruit_MAX31885.cpp` and `Adafruit_MAX31885.h`.

Place the Adafruit_MAX31885 library folder your <arduinosketchfolder>/libraries/ folder. You may need to create the libraries subfolder if its your first library. Restart the IDE.


<!-- START COMPATIBILITY TABLE -->
## Compatibility

MCU                 | Tested Works | Doesn't Work | Not Tested  | Notes
------------------- | :----------: | :----------: | :---------: | -----
Atmega328 @ 16MHz   |      X       |              |             |
Atmega328 @ 12MHz   |      X       |              |             | For LCD example had to move pin 7.
Atmega32u4 @ 16MHz  |      X       |              |             |
Atmega32u4 @ 8MHz   |      X       |              |             |
ESP8266             |      X       |              |             |
Atmega2560 @ 16MHz  |      X       |              |             |
ATSAM3X8E           |      X       |              |             |
ATSAM21D            |      X       |              |             |
ATtiny85 @ 16MHz    |              |      X       |             |
ATtiny85 @ 8MHz     |              |      X       |             |
Intel Curie @ 32MHz |              |              |      X      |
STM32F2             |              |              |      X      |

  * ATmega328 @ 16MHz : Arduino UNO, Adafruit Pro Trinket 5V, Adafruit Metro 328, Adafruit Metro Mini
  * ATmega328 @ 12MHz : Adafruit Pro Trinket 3V
  * ATmega32u4 @ 16MHz : Arduino Leonardo, Arduino Micro, Arduino Yun, Teensy 2.0
  * ATmega32u4 @ 8MHz : Adafruit Flora, Bluefruit Micro
  * ESP8266 : Adafruit Huzzah
  * ATmega2560 @ 16MHz : Arduino Mega
  * ATSAM3X8E : Arduino Due
  * ATSAM21D : Arduino Zero, M0 Pro
  * ATtiny85 @ 16MHz : Adafruit Trinket 5V
  * ATtiny85 @ 8MHz : Adafruit Gemma, Arduino Gemma, Adafruit Trinket 3V

<!-- END COMPATIBILITY TABLE -->

## About

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.
BSD license, check license.txt for more information
All text above must be included in any redistribution
