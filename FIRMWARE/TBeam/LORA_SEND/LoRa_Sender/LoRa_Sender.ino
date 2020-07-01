// SIMPLE LORA TRANSMITTER CODE - VERSION 0.0.1

// Written for the TTGO T-Beam Board used in combination
// with a 128 x 64 SSD 1306 OLED display from HiLetGo.

// Displays transmitted packets, and other useful information

//LIBRARIES ----------------------------------------------------------------------------
#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include "ssd1306.h"  

//VARIABLES FOR LoRa --------------------------------------------------------------------
#define SS      18   // GPIO18 -- SX1278's CS
#define RST     14   // GPIO14 -- SX1278's RESET
#define DI0     26   // GPIO26 -- SX1278's IRQ(Interrupt Request)
#define BAND  915E6

unsigned int counter = 0;

String rssi = "RSSI --";
String packSize = "--";
String packet;
String message;

char packet_array[32] = "abcd";

//FUNCTIONS TO HANDLE DISPLAY TO THE OLED SCREEN -----------------------------------

void splashscreen_oled()
{
  ssd1306_setFixedFont(ssd1306xled_font8x16);
  ssd1306_clearScreen();
  ssd1306_printFixed(34,  2, "BE FREE", STYLE_NORMAL);
  delay(555);
  ssd1306_negativeMode();
  ssd1306_printFixed(28,  19, "TALK FREE", STYLE_NORMAL);
  ssd1306_positiveMode();
  delay(555);
  ssd1306_drawLine(0,40, 128, 40);
  delay(555);
  ssd1306_setFixedFont(ssd1306xled_font6x8);
  ssd1306_printFixed(25,  50, "LoRa - 915MHz", STYLE_NORMAL);
  ssd1306_printFixed(12,  60, "TX FIRMWARE v0.0.1", STYLE_NORMAL);
  delay(1111);
  ssd1306_clearScreen();
}

void tx_packet_display_oled()
{
  ssd1306_setFixedFont(ssd1306xled_font8x16);
  ssd1306_negativeMode();
  ssd1306_printFixed(2,  10, "TRANSMITTING", STYLE_NORMAL);
  ssd1306_positiveMode();
  ssd1306_printFixed(2,  30, packet_array, STYLE_NORMAL);
  ssd1306_drawLine(0, 45, 128, 45);
}

//SETUP AND LOOP -------------------------------------------------------------------

void setup() 
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println("LoRa Sender Test");
  
  SPI.begin(SCK,MISO,MOSI,SS);
  LoRa.setPins(SS,RST,DI0);
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("init ok");
  ssd1306_128x64_i2c_init();
  splashscreen_oled();
}

void loop() {
  Serial.println(counter);

  // send packet
  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.print(counter);
  LoRa.endPacket();

  message = "hello " + String(counter);
  message.toCharArray(packet_array, 32);
  tx_packet_display_oled();
  counter++;
  
  digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(2, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
