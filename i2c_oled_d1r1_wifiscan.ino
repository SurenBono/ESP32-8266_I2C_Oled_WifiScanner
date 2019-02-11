/**
Esp8266 Scrolling WifiScanner on 128x64/128x32 pixel tested on 
Adafruit 12c OLED derived from Serial Monitored WifiScanner.
Boot up on your own logo http://javl.github.io/image2cpp/ ,splash.h modification in lib,backup existing. 
,if failed return to default splash= choose erase all flash when reflashing after restoring backup splash.h
Choose custom font  :   http://oleddisplay.squix.ch/#/home
Modified & Developed by https://srotogargees.business.site/
Created on:11-02-2019
*/
#include "ESP8266WiFi.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 32 //64
#define OLED_RESET     2 //4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
      
                                   
 
void setup()   {                
 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);                                        //start the OLED @ Hex addy 0x3C
  display.display();                                                                //show the Adafruit Logo
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
    display.println("Scan WiFi");                                                   //print title to buffer
  
  if (n == 0)                                                                       //if no networks found
    display.println("no networks found");                                           //print msg to buffer
  else                                                                              //otherwise..
  { 
    display.setCursor(64,0);
    display.print(n);
    display.setCursor(70,0);
    display.println(" = Found  ");                                                  //print n to buffer
                                                                
    for (int i = 0; i < n; ++i)                                                     //for loop for # of networks
    {                                                                               //print SSID and RSSI for each network found
      display.print(i + 1);
      display.print(": ");
      display.print(WiFi.SSID(i));
      display.print(" (");
      display.print(WiFi.RSSI(i));
      display.print(")");

      delay(10);
    }
  }
  Serial.println("");
 
  display.display();                                                                // Display Buffer
  display.startscrollleft(0x00, 0x0F);                                              // Scroll to left
  delay(20000);                                                                     //wait 5 seconds
}
