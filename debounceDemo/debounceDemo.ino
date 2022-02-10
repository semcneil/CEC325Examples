/* debounceDemo.ino
 *  
 *  Demonstrate the need to debounce and methods to deal with debounce
 *  
 *  Seth McNeill
 *  2022 January 31
 */

#define LEFT_BUTTON_PIN   9 // buttons cannot be 3 since internal pullup not available
#define RIGHT_BUTTON_PIN  10
#define LIGHT_PIN         A7
#define TEMPERATURE_PIN   A2
#define POT_PIN           A1
#define BAT_PIN           A3
int reportDiff = 1000; // number of millis between reports

void setup() {
  Serial.begin(115200);
  while(!Serial) delay(10);

  Serial.println("Starting...");

  pinMode(LEFT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

}

int count = 0;  // count the number of changes
int lastState = HIGH;  // current state of the button
long int lastSendMillis = 0;
void loop() {
  int currentState = digitalRead(RIGHT_BUTTON_PIN);

  if(currentState != lastState) {
    count++;
    lastState = currentState;
    digitalWrite(LED_BUILTIN, HIGH);
  }

  if(millis() - lastSendMillis > reportDiff) {
    Serial.print(count);
    Serial.print(", ");
    Serial.print(lastState);
    Serial.print(", ");
    Serial.println(currentState);
    lastSendMillis = millis();
    digitalWrite(LED_BUILTIN, LOW);
  }
  delay(2);
}
