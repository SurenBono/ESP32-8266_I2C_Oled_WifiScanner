# ESP32/8266_I2C-OLED-128x64/32_WIFI_SCANNER
Scan network on Adafruit OLED derived from Default Wifi Scanner normally monitored on serial port.
Tested on R32 ( Esp32 Dev Module Compatible ).
Esp8266 Scrolling WifiScanner on 128x64/128x32 pixel tested on WeMos D1 R1 .
4 wire (3v3,GND,SCL,SDA)
Change resolution possible from 128x64 to 128x32 vice versa.
Use scrolling for display longevity.
Boot up on your own logo http://javl.github.io/image2cpp/ ,splash.h modification in Adafruit_SSD1306 folder..etc , 2 sizes (82x64 & 115x32) ,backup existing splash.h.
Return to default splash = choose erase all flash when reflashing after restoring backup splash.h
Choose custom font  :   http://oleddisplay.squix.ch/#/home
Modified & Developed by https://srotogargees.business.site/
Created on:11-02-2019

P/S: Multiplex for multi OLED for bigger screen...wish it was 4x8cm uno size screen with multi button on A0
