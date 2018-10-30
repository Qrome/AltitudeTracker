/* The MIT License (MIT)
Copyright (c) 2018 David Payne
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/***********************************************************************
 * Altitude Tracker Designed for use with the following components:
 * Arduino Nano - https://goo.gl/EB2WN2
 * BMP280 Barameter - https://goo.gl/KBD7lA
 * 0.91 Inch OLED Display 128x32 - https://goo.gl/dZC9nm
 * 
 * Code by David Payne - Qrome@yahoo.com
 * 
 * I2C pins are the Arduino Standard:
 * SDA = A4
 * SCL = A5
 * 
 * IMPORTANT:  Using the Adafruit_BMP280.h you must update the
 * I2C address in the file to: #define BMP280_ADDRESS        (0x76)
 */

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <math.h>


const int PREASURE = 1005;  // local air preasure
float HomeAlt = 0.0;
float lastAlt = 0.0;
int MaxAlt = 0;
float temp = 0.0;
const int sampleMax = 20;
int sampleCount = 0;
int samples[sampleMax];
