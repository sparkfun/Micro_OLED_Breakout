/******************************************************************************
  MicroOLED_Multi.ino
  SFE_MicroOLED Multi OLED Demo
  Basuke Suzuki @basuke
  Original Creation Date: February 3, 2015

  This sketch demonstrates how to use multiple MicroOLED
  breakout boards from one Arduino.

  Hardware Connections:
    We'll be using the SPI interface on the MicroOLED.

    MicroOLED 1 ----------- Arduino
      GND ------------------- GND
      VDD ------------------- 3.3V (VCC)
    D1/MOSI ----------------- D11 (don't change)
    D0/SCK ------------------ D13 (don't change)
      D2
      D/C ------------------- D8 (can be any digital pin)
      RST ------------------- D9 (can be any digital pin)
      CS  ------------------- D10 (can be any digital pin)

    MicroOLED 2 ----------- Arduino
      GND ------------------- GND
      VDD ------------------- 3.3V (VCC)
    D1/MOSI ----------------- D11 (don't change)
    D0/SCK ------------------ D13 (don't change)
      D2
      D/C ------------------- D8 (shaed with first one)
      RST ------------------- D9 (shaed with first one)
      CS  ------------------- D7 (can be any digital pin,
                                  but not the same with first one)

  Development environment specifics:
  	IDE: Arduino 1.0.5
  	Hardware Platform: MicroOLED Breakout
                           Arduino Pro Mini 3.3V/8MHz

  Note: The display on the MicroOLED is a 1.8V-3.3V device only.
  Don't try to connect a 5V Arduino directly to it! Use level
  shifters in between the data signals if you have to resort to
  a 5V board.

  This code is beerware; if you see me (or any other SparkFun
  employee, or @basuke) at the local, and you've found our code helpful,
  please buy us a round!

  Distributed as-is; no warranty is given.
*******************************************************************************/
#include <Wire.h>  // Include Wire if you're using I2C
#include <SPI.h>  // Include SPI if you're using SPI
#include <SFE_MicroOLED.h>  // Include the SFE_MicroOLED library

//////////////////////////
// MicroOLED Definition //
//////////////////////////
#define PIN_RESET 9  // Connect RST to pin 9
#define PIN_DC    8  // Connect DC to pin 8
#define PIN_CS_1  10 // Connect first CS to pin 10
#define PIN_CS_2  7  // Connect second CS to pin 7

//////////////////////////////////
// MicroOLED Object Declaration //
//////////////////////////////////
// Declare a MicroOLED object. The parameters include:
// 1 - Reset pin: Any digital pin
// 2 - D/C pin: Any digital pin (SPI mode only)
// 3 - CS pin: Any digital pin (SPI mode only, 10 recommended)
MicroOLED oled1(PIN_RESET, PIN_DC, PIN_CS_1);
MicroOLED oled2(PIN_RESET, PIN_DC, PIN_CS_2);

void setup()
{
  // These three lines of code are all you need to initialize the
  // OLED and print the splash screen.

  // To use multiple MicroOLED boards, begin() cannot be used.
  // Insted, use pair of setup() and initialize() in that order.

  // Congigure pins to control OLEDs
  oled1.setup();
  oled2.setup();

  // Send initialize commands to each OLEDs
  oled1.initialize();
  oled2.initialize();

  // Display SparkFun logo as the splash screen only for first OLED
  oled1.loadSparkFunLogo();
  oled1.display();

  delay(1000);

  oled1.setFontType(1);
  oled2.setFontType(1);
}

void loop()
{
  oled1.clear(PAGE);
  oled2.clear(PAGE);

  oled1.setCursor(0, 0);
  oled2.setCursor(0, 0);

  oled1.print("Hello");
  oled2.print("world!");

  oled1.display();
  oled2.display();

  delay(2000);

  oled1.clear(PAGE);
  oled2.clear(PAGE);

  oled1.setCursor(0, 0);
  oled2.setCursor(0, 0);

  oled1.print("See you");
  oled2.print("again.");

  oled1.display();
  oled2.display();

  delay(2000);
}
