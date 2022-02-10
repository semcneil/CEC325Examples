/*  usb-log.ino
 *  
 *  Writes data as csv text to the host computer as a USB keyboard.
 *  
 *  based on
 *  https://docs.arduino.cc/tutorials/nano-rp2040-connect/rp2040-01-technical-reference#usb-keyboard
 *  
 *  Seth McNeill
 *  2022 February 09
 */

#include "WiFiNINA.h"  // for A4-A7 and wifi/bluetooth

#include "PluggableUSBHID.h"
#include "USBKeyboard.h"

#define LEFT_BUTTON_PIN   9 // buttons cannot be 3 since internal pullup not available
#define RIGHT_BUTTON_PIN  A7 // Doesn't work yet. Check whether WiFiNINA can pullup internally
#define LIGHT_PIN         A0
#define POT_PIN           A1
#define BUZZ_PIN          A2
#define BAT_PIN           A3


USBKeyboard Keyboard;

void setup() {
  Serial.begin(115200);
  //while(!Serial) delay(100);
  Serial.println("Starting...");
  
  pinMode(LEFT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUZZ_PIN, OUTPUT);
}

int isLogging = false;
int logdT = 1000; // time between log points in milliseconds
long int lastLogTime = 0;
int leftButtonState;
int leftLastButtonState = 1;
int rightButtonState;
int rightLastButtonState = 1;

void loop() {
  leftButtonState = digitalRead(LEFT_BUTTON_PIN);
  rightButtonState = digitalRead(RIGHT_BUTTON_PIN);
  // check for button state changes to prevent repeatedly doing the action
  if(leftButtonState != leftLastButtonState && leftButtonState == 0) {  
    Keyboard.printf("millis,Light,Potentiometer,Battery\n");
  }
  // toggle logging
  if(rightButtonState != rightLastButtonState && rightButtonState == 0) {
    isLogging = !isLogging;
    if(isLogging) {
      Serial.println("Logging start");
    } else {
      Serial.println("Logging stop");
    }
  }
  if(isLogging && (millis() - lastLogTime > logdT)) {
    int lightVal = analogRead(LIGHT_PIN);
    int potVal = analogRead(POT_PIN);
    int batVal = analogRead(BAT_PIN);
    Keyboard.printf("%d,%d,%d,%d\n", millis(), lightVal, potVal, batVal);
    lastLogTime = millis();
  }
  leftLastButtonState = leftButtonState;
  rightLastButtonState = rightButtonState;
  delay(10);
}
