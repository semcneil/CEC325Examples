/*
  Reading a serial ASCII-encoded string.

  This sketch demonstrates the Serial parseInt() function.
  It looks for an ASCII string of comma-separated values.
  It parses them into ints, and uses those to fade an RGB LED.

  NOTE: RGB LED unavailable if Bluetooth is being used

  Circuit: Common-Cathode RGB LED wired like so:
  - red anode: digital pin LEDR on WiFiNINA module
  - green anode: digital pin LEDG on WiFiNINA module
  - blue anode: digital pin LEDB on WiFiNINA module
  - cathode: GND

  created 13 Apr 2012
  by Tom Igoe
  modified 14 Mar 2016
  by Arturo Guadalupi
  modified 09 Feb 2022
  by Seth McNeill

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/ReadASCIIString
*/

#include <WiFiNINA.h>

// pins for the LEDs:
#define redPin   LEDR
#define greenPin LEDG
#define bluePin  LEDB

void setup() {
  // initialize serial:
  Serial.begin(115200);
  // make the pins outputs:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

}

void loop() {
  // if there's any serial available, read it:
  while (Serial.available() > 0) {

    // look for the next valid integer in the incoming serial stream:
    int red = Serial.parseInt();
    // do it again:
    int green = Serial.parseInt();
    // do it again:
    int blue = Serial.parseInt();

    // look for the newline. That's the end of your sentence:
    if (Serial.read() == '\n') {
      // constrain the values to 0 - 255 and invert
      // if you're using a common-cathode LED, just use "constrain(color, 0, 255);"
      red = 255 - constrain(red, 0, 255);
      green = 255 - constrain(green, 0, 255);
      blue = 255 - constrain(blue, 0, 255);

      // fade the red, green, and blue legs of the LED:
      analogWrite(redPin, red);
      analogWrite(greenPin, green);
      analogWrite(bluePin, blue);

      // print the three numbers in one string as hexadecimal:
      Serial.print(red, HEX);
      Serial.print(',');
      Serial.print(green, HEX);
      Serial.print(',');
      Serial.println(blue, HEX);
    }
  }
}
