// SIMPLE LORA RECIEVER CODE - VERSION 0.0.1

// Written for the TTGO T-Beam Board used in combination
// with a 128 x 64 SSD 1306 OLED display from HiLetGo.

// Displays recieved packets, RSSI and other useful information

//LIBRARIES ----------------------------------------------------------------------------
#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include "ssd1306.h"


//VARIABLES FOR LoRa --------------------------------------------------------------------
#define SS      18   // GPIO18 -- SX1278's CS
#define RST     14   // GPIO14 -- SX1278's RESET
#define DI0     26   // GPIO26 -- SX1278's IRQ(Interrupt Request)
#define BAND    915E6   //This sets the transmit frequency (915MHz in the US)
String rssi = "RSSI --";
String packSize = "--";
String packet ;

char rssi_array[16] = "abcd";
char packet_array[32] = "abcd";

bool has_received = 0;

//FUNCTIONS TO HANDLE LoRa TRANSMIT/RRECIEVE ---------------------------------------------
void loraData() {

  Serial.print(packet);
  Serial.print(" + ");
  Serial.println(rssi); 
}

void cbk(int packetSize) {
  packet = "";
  packSize = String(packetSize, DEC);
  for (int i = 0; i < packetSize; i++) {
    packet += (char) LoRa.read();
  }
  rssi = "RSSI " + String(LoRa.packetRssi(), DEC) + "dBm";
  rssi.toCharArray(rssi_array, 16);
  packet.toCharArray(packet_array, 32);

  if (has_received == 0) { ssd1306_clearScreen(); }
  loraData();
  rx_packet_display_oled();
}

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
  ssd1306_printFixed(12,  60, "RX FIRMWARE v0.0.1", STYLE_NORMAL);
  delay(1111);
  ssd1306_clearScreen();
}

void rx_packet_display_oled()
{
  has_received = 1;
  
  ssd1306_setFixedFont(ssd1306xled_font8x16);
  ssd1306_printFixed(2,  10, packet_array, STYLE_NORMAL);
  ssd1306_drawLine(0, 45, 128, 45);
  ssd1306_printFixed(2,  50, rssi_array, STYLE_NORMAL);
}

void waiting_for_packets_display_oled()
{
  ssd1306_setFixedFont(ssd1306xled_font8x16);
  ssd1306_printFixed(2,  10, "LISTENING FOR", STYLE_NORMAL);
  ssd1306_printFixed(2,  30, "MESSAGES", STYLE_NORMAL);
  ssd1306_drawLine(0, 45, 128, 45);
  ssd1306_printFixed(2,  50, "RSSI  n/a", STYLE_NORMAL);
  
}

//SETUP AND LOOP -------------------------------------------------------------------

void setup() 
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println("LoRa Receiver Callback");
  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DI0);
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  //LoRa.onReceive(cbk);
  LoRa.receive();
  Serial.println("init ok");

  ssd1306_128x64_i2c_init();
  splashscreen_oled();
  waiting_for_packets_display_oled();
}

void loop() 
{ 
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    cbk(packetSize);
  }
  delay(10);
}
