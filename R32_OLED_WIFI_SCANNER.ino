//#include "ESP8266WiFi.h"
#include "WiFi.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET     4 
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
  display.println("_____ Scan WiFi _____");                                         //print title to buffer
  
  if (n == 0)                                                                       //if no networks found
    display.println("no networks found");                                           //print msg to buffer
  else                                                                              //otherwise..
  { 
    display.print(n);                                                               //print n to buffer
    display.println(" = Found  ");  
                                                                
    for (int i = 0; i < n; ++i)                                                     //for loop for # of networks
    {
                                                                                    //print SSID and RSSI for each network found
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
 
  display.display();                                                               //show buffer
  delay(5000);                                                                     //wait 5 seconds
}
