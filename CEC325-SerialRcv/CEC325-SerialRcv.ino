/*  CEC325-SerialRcv.ino
 *  
 *  Demonstrates receiving and reacting to serial input.
 *  Uses the ERAU CEC325 board v0.3 which has an 
 *  Arduino Nano RP2040 Connect on board.
 *  
 *  Seth McNeill
 *  2022 February 09
 *  
 *  This code in the public domain.
 */

#include <WiFiNINA.h>  // for RGB LED and A7 (right button)

// pins for the LEDs:
#define LEFT_BUTTON_PIN   9 // buttons cannot be 3 since internal pullup not available
#define RIGHT_BUTTON_PIN  A7 // requires external pullup, including WiFiNINA.h and #define
#define LIGHT_PIN         A0 // photocell
#define POT_PIN           A1 // potentiometer
#define BUZZ_PIN          A2 // buzzer
#define BAT_PIN           A3 // battery voltage divider


void setup() {
  // initialize serial:
  Serial.begin(115200);
  while(!Serial) delay(100); // wait for serial to begin
  Serial.println("Starting...");
  
  // make the pins outputs:
  pinMode(LEDR, OUTPUT);  // WiFiNINA RGB LED red
  pinMode(LEDG, OUTPUT);  // WiFiNINA RGB LED green
  pinMode(LEDB, OUTPUT);  // WiFiNINA RGB LED blue
  pinMode(LEFT_BUTTON_PIN, INPUT_PULLUP); // needs the internal pullup
  pinMode(RIGHT_BUTTON_PIN, INPUT);  // internal pullup not tied to IDE
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUZZ_PIN, OUTPUT);  // buzzer pin is output
}

void loop() {
  while(Serial.available() > 0) {  // characters have been received
    char inChar = Serial.read();
    switch(inChar) {
      case 'a': digitalWrite(LED_BUILTIN,HIGH); break;
      case 'A': digitalWrite(LED_BUILTIN,LOW); break;
      case 'b': digitalWrite(LEDB, HIGH); break;
      case 'r': digitalWrite(LEDR, HIGH); break;
      case 'g': digitalWrite(LEDG, HIGH); break;
      case 'p': readPot(); break;
      case 'l': readLight(); break;
      case '+': add(); break;
      case 'o': ledsOff(); break;
      case 'z': tone(BUZZ_PIN, 1000, 100); break;
      case '\n': break;
      default: Serial.print("Unknown character: "); Serial.println(inChar);
    }
  }
}

// turns off all 4 LEDs
void ledsOff() {
  digitalWrite(LED_BUILTIN,LOW);
  digitalWrite(LEDR,LOW);
  digitalWrite(LEDG,LOW);
  digitalWrite(LEDB,LOW);
}

// Adds characters received subsequent to +
void add() {
  Serial.println("Adding single digit numbers");
  int a = Serial.read() - 48; // subtract off value of ASCII 0
  int b = Serial.read() - 48; // subtract off value of ASCII 0
  Serial.print(a);
  Serial.print('+');
  Serial.print(b);
  Serial.print('=');
  Serial.println(a+b);
}

// Prints the potentiometer ADC value
void readPot() {
  Serial.print("potentiometer: ");
  Serial.println(analogRead(POT_PIN));
}

// Prints the light sensor ADC value
void readLight() {
  Serial.print("light: ");
  Serial.println(analogRead(LIGHT_PIN));
}
