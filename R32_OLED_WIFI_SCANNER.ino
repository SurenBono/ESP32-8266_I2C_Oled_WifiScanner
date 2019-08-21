/** 
4 WIRE i2c OLED VCC=3V3,Common GND,SCL & SDA.
R32 are UNO styled microcontroller uploaded with ESP32 DEV MODULE
Boot up on your own logo http://javl.github.io/image2cpp/ ,splash.h modification in lib,backup existing. 
,if failed return to default splash= choose erase all flash when reflashing after restoring backup splash.h
Choose custom font  :   http://oleddisplay.squix.ch/#/home
Modified & Developed by https://srotogargees.business.site/
Created on:11-02-2019
Revised on:21-08-2019
*/

//#include "ESP8266WiFi.h"                                                         // Uncomment for esp8266 modules
#include "WiFi.h"                                                                  // esp32 wifi driver,Comment if esp8266 vice versa
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET     4 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);          // i[]c constructors
      
                                   
void setup()   {                
 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);                                        //start the OLED @ Hex addy 0x3C
  display.display();                                                                //show the Adafruit Logo or custom logo splash.h
  delay(2000);                                                                      //for 2 seconds
  display.clearDisplay();                                                           //clear display & buffer
  WiFi.mode(WIFI_STA);                                                              //set WiFi mode
  WiFi.disconnect();                                                                //WiFi disconnect
  delay(100);                                                                       //short wait
 
}
 
 
void loop() {
 
  display.clearDisplay();                                                           //clear display @ beginning of each loop
  display.setTextSize(1);                                                           //set smallest text size
  display.setTextColor(WHITE);                                                      //set text color to WHITE
  display.setCursor(0,0);                                                           //cursor to upper left
 
  //display.println("scan start");
 
int n = WiFi.scanNetworks();                                                        //get # of networks
  display.print("__ WiFi Found : ");                                                //compacted title with scan result (n)
  
  if (n == 0)                                                                       //if no networks found
    display.println("no networks found");                                           //print msg to buffer
  else                                                                              //otherwise..
  { 
    display.print(n);                                                               //print number of AP found to compacted title
    display.println(" __");  
                                                                
    for (int i = 0; i < n; ++i)                                                     //for loop for # of networks
    {
                                                                                    //print SSID and RSSI for each network found
      display.print(i + 1);
      display.print(" ");
      display.print(WiFi.SSID(i));
      display.print(" ");
      display.print(WiFi.RSSI(i));
      display.print(" ");                                                                    // leave a empty colomn space
      //display.print((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" Unsecured":" Secured");    // Wifi Security Check protocol
      display.println();                                                                     // add next AP in new row to buffer
      delay(10);
    }
  }
  display.println("");                                                             //display everything in bitween " "
  display.display();                                                               //show data in buffer 
  delay(5000);                                                                     //wait 5 seconds till next loop
}
