/***************************************************************************
  This is a library for the BMP280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BMEP280 Breakout 
  ----> http://www.adafruit.com/products/2651

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required 
  to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <math.h>



Adafruit_BMP280 bme; // I2C

// Display Settings
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

const int PREASURE = 1005;  // local air preasure
float HomeAlt = 0.0;
int MaxAlt = 0;
float temp = 0.0;
float alt = 0.0;
  
void setup() {
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done

  // Clear the display buffer.
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("   Altitude Tracker");
  display.println();
  display.println("    by David Payne");
  display.display();
  
  Serial.println(F("BMP280 test"));
  
  if (!bme.begin()) {  
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }
  delay(2000);
  HomeAlt = bme.readAltitude(PREASURE);
  display.clearDisplay();
}
  
void loop() {
    temp = bme.readTemperature();
    alt = bme.readAltitude(PREASURE);

    if (getAltChange(alt) > MaxAlt) {
      MaxAlt = getAltChange(alt);
    }
    displayAltitude(alt, temp);;
}

void displayAltitude(float alt, float temp) {
  //Current Altitude
  display.setTextSize(3);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(0,0);
  String feet = String(getAltChange(alt));
  if (feet.indexOf("-") == -1) {
    feet = " " + feet;
  }
  display.print(feet + "   ");
  display.setTextSize(2);
  display.setCursor(100, 0);
  display.print("ft");

  //Max Altitude
  display.setTextSize(1);
  display.setCursor(0, 24);
  display.print(String(MaxAlt));
  display.print(" ft ");

  // Temp
  display.setTextSize(2);
  display.setCursor(90,18);
  String tmp = String(getFfromC(temp)) + "F";
  if (temp > 99) {
    tmp = " " + tmp;
  }
  display.print(tmp);
  display.display();
}

float getFeet(float meters) {
  return meters * 3.2808;
}

int getAltChange(float alt) {
  return round(getFeet(alt - HomeAlt));
}

int getFfromC(float temp) {
  return round((temp * 1.8) + 32);
}
