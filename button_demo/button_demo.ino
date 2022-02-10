/* button_demo.ino
 *  
 *  Gives an example of how to use the buttons on 
 *  the CEC 325 board.
 *  
 *  Seth McNeill
 *  2022 February 03
 */

#include "WiFiNINA.h"  // for A4-A7 and wifi/bluetooth

#define LEFT_BUTTON_PIN   9 // This input is on the RP2040 and has builtin pullup that works
#define RIGHT_BUTTON_PIN  A7 // This input is on the WiFiNINA and doesn't have working internal pullup

void setup() {
  Serial.begin(115200);
  //while(!Serial) delay(10);
  delay(2000);

  Serial.println("Starting...");

  pinMode(LEFT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // note that the buttons read 1 (HIGH or true) when not pressed
  if(!digitalRead(LEFT_BUTTON_PIN)) {
    Serial.println("Left button pushed");
  }
  if(!digitalRead(RIGHT_BUTTON_PIN)) {
    Serial.println("Right button pushed");
  }
  delay(100); // keeps the loop from running too fast with nothing pushed
}
