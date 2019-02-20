/*
 *  This sketch shows the WiFi event usage
 *
*/

/* 
* WiFi Events

SYSTEM_EVENT_WIFI_READY               < ESP32 WiFi ready
SYSTEM_EVENT_SCAN_DONE                < ESP32 finish scanning AP
SYSTEM_EVENT_STA_START                < ESP32 station start
SYSTEM_EVENT_STA_STOP                 < ESP32 station stop
SYSTEM_EVENT_STA_CONNECTED            < ESP32 station connected to AP
SYSTEM_EVENT_STA_DISCONNECTED         < ESP32 station disconnected from AP
SYSTEM_EVENT_STA_AUTHMODE_CHANGE      < the auth mode of AP connected by ESP32 station changed
SYSTEM_EVENT_STA_GOT_IP               < ESP32 station got IP from connected AP
SYSTEM_EVENT_STA_LOST_IP              < ESP32 station lost IP and the IP is reset to 0
SYSTEM_EVENT_STA_WPS_ER_SUCCESS       < ESP32 station wps succeeds in enrollee mode
SYSTEM_EVENT_STA_WPS_ER_FAILED        < ESP32 station wps fails in enrollee mode
SYSTEM_EVENT_STA_WPS_ER_TIMEOUT       < ESP32 station wps timeout in enrollee mode
SYSTEM_EVENT_STA_WPS_ER_PIN           < ESP32 station wps pin code in enrollee mode
SYSTEM_EVENT_AP_START                 < ESP32 soft-AP start
SYSTEM_EVENT_AP_STOP                  < ESP32 soft-AP stop
SYSTEM_EVENT_AP_STACONNECTED          < a station connected to ESP32 soft-AP
SYSTEM_EVENT_AP_STADISCONNECTED       < a station disconnected from ESP32 soft-AP
SYSTEM_EVENT_AP_PROBEREQRECVED        < Receive probe request packet in soft-AP interface
SYSTEM_EVENT_GOT_IP6                  < ESP32 station or ap or ethernet interface v6IP addr is preferred
SYSTEM_EVENT_ETH_START                < ESP32 ethernet start
SYSTEM_EVENT_ETH_STOP                 < ESP32 ethernet stop
SYSTEM_EVENT_ETH_CONNECTED            < ESP32 ethernet phy link up
SYSTEM_EVENT_ETH_DISCONNECTED         < ESP32 ethernet phy link down
SYSTEM_EVENT_ETH_GOT_IP               < ESP32 ethernet got IP from connected AP
SYSTEM_EVENT_MAX
*/

//#include "ESP8266WiFi.h"    // uncomment and comment <WiFi.h> for esp8266 board (untested yet)
#include <WiFi.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET     2 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
const char* ssid     = "AP NAME";				// Add your broadcasted Wifi Access Point 
const char* password = "PASSWORD";				// AP password


void WiFiEvent(WiFiEvent_t event)
{
	  display.clearDisplay();                                                           //clear display @ beginning of each loop
	  display.setTextSize(1);                                                           //set smallest text size
	  display.setTextColor(WHITE);                                                      //set text color to WHITE
	  display.setCursor(0,0);    
	  display.printf("[WiFi-event] event: %d\n", event);

    switch (event)
    {
    case SYSTEM_EVENT_STA_GOT_IP:
		display.setCursor(0,18); 
		display.println("WiFi Connected");
		display.setCursor(0,36); 
		display.println("Module IP Address: ");
		display.setCursor(0,54);
		display.println(WiFi.localIP());
    break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
		display.clearDisplay();
		display.println("WiFi lost connection");
    break;
    }
}

void WiFiGotIP(WiFiEvent_t event, WiFiEventInfo_t info)
{	
		display.setCursor(0,18); 
		display.println("WiFi Connected");
		display.setCursor(0,36);
		display.println("Module IP Address: ");
		display.setCursor(0,54);
		display.println(IPAddress(info.got_ip.ip_info.ip.addr));
}

void setup()
{
	  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);                                        //start the OLED @ Hex addy 0x3C
	  display.display();                                                                //show the Logo
	  delay(2000);                                                                      //for 2 seconds
	  display.clearDisplay();                                                           //clear display & buffer
	  WiFi.mode(WIFI_STA);  
	  WiFi.disconnect(true);

    delay(100);

    // Examples of diffrent ways to register wifi events
    WiFi.onEvent(WiFiEvent);
    WiFi.onEvent(WiFiGotIP, WiFiEvent_t::SYSTEM_EVENT_STA_GOT_IP);
    WiFiEventId_t eventID = WiFi.onEvent([](WiFiEvent_t event, WiFiEventInfo_t info){
		display.clearDisplay(); 
		display.setCursor(0,0); 	
        display.print("WiFi lost connection. Reason: ");
        display.println(info.disconnected.reason);
    }, WiFiEvent_t::SYSTEM_EVENT_STA_DISCONNECTED);

    // Remove WiFi event
	
    display.print("WiFi Event ID: ");
    display.println(eventID);
    // WiFi.removeEvent(eventID);

    WiFi.begin(ssid, password);

    display.clearDisplay();   
    display.println("Wifi Connecting ... ");
    
}

void loop()
{		
	  Serial.println("");
	  display.display(); 
	  delay(10000);
}
