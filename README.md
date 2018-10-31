# AltitudeTracker
This is a functional altitude tracker that allows you to connect to a 5V pin on your RC plane.
It will display current altitude and retain the highest obtained during your flight.

Hardware list:

 Arduino Nano - https://amzn.to/2DdeWqt
 BMP280 Barameter - https://amzn.to/2yGTUN2
 0.91 Inch OLED Display 128x32 - https://amzn.to/2SxxyWQ
   
 I2C pins are the Arduino Standard:
 SDA = A4
 SCL = A5
  
 IMPORTANT:  Using the Adafruit_BMP280.h you must update the I2C address in the file to: 
 \#define BMP280_ADDRESS (0x76)