// 4X4 I2C KEYPAD TESTER - VERSION 0.0.0

// Written for the TTGO T-Beam Board used in combination
// with the Wholesome Circuits 4x4 Mechanical I2C Keypad
// setup with the default harware I2C address (all jumpers
// set to 0)

// Displays keystrokes as 0s and 1s on the SSD1306 OLED display


//LIBRARIES ----------------------------------------------------------------------------
#include <Wire.h>
#include "Adafruit_MCP23017.h"
#include <SPI.h>
#include "ssd1306.h"

Adafruit_MCP23017 keypad;

//Variables to parse, convert and display key states
bool keypad_states[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
char keypad_array[16] = "0";
String keypad_string = "abcdefg";
  
void setup() 
{ 
  Serial.begin(115200); 
  
  keypad.begin();   //Initialize MUX object with default I2C address

  //Set all MUX pins as input pins and enable pullups
  for(int i = 0; i < 16; i++)
  {
    keypad.pinMode(i, INPUT);
    keypad.pullUp(i, HIGH);
  }
  ssd1306_128x64_i2c_init();
  splashscreen_oled();
}

void loop() 
{
  poll_buttons();
  display_keypad_states_oled();
  serial_debug();
}

//Function to read values out of each one of the MUX's I/O pins
void poll_buttons()
{
  for (int i = 0; i < 16; i++)
  {
    keypad_states[i] = keypad.digitalRead(i);
  }
}

//Funcrion to print currrent button states to Serial monitor
void serial_debug()
{
  for (int i = 0; i < 16; i++)
  {
    Serial.print(keypad_states[i]);
    Serial.print(",");
  }
  Serial.println();
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
  ssd1306_printFixed(25,  50, "I2C KEYPAD POLLER", STYLE_NORMAL);
  delay(1111);
  ssd1306_clearScreen();
}

//Function that handles the conversion of the read bool array into a format
//that the SSD1306 library will like. Not as concise as I want this to be,
//but works for now
void display_keypad_states_oled()
{
  ssd1306_setFixedFont(ssd1306xled_font6x8);
  ssd1306_clearScreen();
  for (int i = 0; i < 16; i++)
  {
    if (i == 0) {keypad_string = " ";}   //Clear the string at the first iteration of the loop
    if (keypad_states[i] == 0) {keypad_string += "0";}    //Put the string together char by char
    else if (keypad_states[i] == 1) {keypad_string += "1";}   //Put the string together char by char
  }
  keypad_string.toCharArray(keypad_array, 16);
  ssd1306_printFixed(2,  10, keypad_array, STYLE_NORMAL);
}
