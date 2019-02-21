/*
 *  This sketch trys to Connect to the best AP based on a given list
 *
 */
//#include "ESP8266WiFi.h"
#include <WiFi.h>
#include <WiFiMulti.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET     2 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
WiFiMulti wifiMulti;

void setup()
{
    
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);                                        
	display.display();                                                                
	delay(2000);                                                                     
	display.clearDisplay();  
	display.setTextSize(1);                                                           
	display.setTextColor(WHITE);                                                      
	display.setCursor(0,0);     
    WiFi.disconnect();                           

    wifiMulti.addAP("Arduino Wifi", "xxxxxxx");
    wifiMulti.addAP("ultimate expansion@unifi", "xxxxxxxx");
 
	
    display.println("Connecting Wifi...");
    if(wifiMulti.run() == WL_CONNECTED) {
	   
        display.clearDisplay(); 
		display.setCursor(0,18);
        display.println("WiFi connected");
		display.setCursor(0,36);
        display.println("IP address: ");
		display.setCursor(0,54);
        display.println(WiFi.localIP());
		Serial.println("");
		display.display();
		display.startscrollleft(0x00, 0x0F);
		delay(20000);
    }
}

void loop()
{	
	display.clearDisplay();                                                           //clear display @ beginning of each loop
	if(wifiMulti.run() != WL_CONNECTED) {
        display.println("WiFi not connected!");
		Serial.println("");
		display.display();  
		display.startscrollleft(0x00, 0x0F);
        delay(2*5000);
    }
}