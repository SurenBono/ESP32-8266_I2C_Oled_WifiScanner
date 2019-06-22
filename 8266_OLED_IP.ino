#include <ESP8266WiFi.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET     2 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);                                        //start the OLED @ Hex addy 0x3C
  display.display();                                                                //show the Adafruit Logo
  delay(2000);                                                                      //for 2 seconds
  display.clearDisplay();  
  display.print("Connecting");
  Serial.begin(115200);
  Serial.println();

  WiFi.begin("Arduino Wifi", "tm1010101");
  
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    display.print(".");
  }
  display.println();

  display.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  display.clearDisplay();                                                           //clear display @ beginning of each loop
  display.setTextSize(1);                                                           //set smallest text size
  display.setTextColor(WHITE);                                                      //set text color to WHITE
  display.setCursor(0,0);   
  display.print(WiFi.localIP());
  display.display();
}

void loop() {
    
  
  
  }
