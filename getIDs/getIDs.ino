/* getIDs.ino
 * 
 * Collects the ID from the Nano Connect RP2040's cryptography chip,
 * and the IDs off the 1-wire temperature sensors.
 * 
 * Seth McNeill
 * 2022 September 05
 */

#define OW_PIN            10  // pin for 1-Wire devices (DS18B20)
#define PARASITE_POWER    false

// cryptology chip libraries
#include <ArduinoECCX08.h>
#include <utility/ECCX08JWS.h>
#include <utility/ECCX08DefaultTLSConfig.h>

// OneWire includes for DS18B20 temperature sensors
#include "OneWireNg_CurrentPlatform.h"
#include "drivers/DSTherm.h"
#include "utils/Placeholder.h"
static Placeholder<OneWireNg_CurrentPlatform> _ow;

// must be named this for the ArduinoECCX08 library to work, 
// also must modify ECCX08.cpp to not define a variable with this name
ECCX08Class ECCX08(Wire, (uint8_t)0x60); 


void setup() {
  Serial.begin(115200);
  while(!Serial);  // wait for serial to begin

  Serial.println("\n===============================");

  // setup DS18B20 1-Wire temperature sensors
  new (&_ow) OneWireNg_CurrentPlatform(OW_PIN, false);
  DSTherm drv(_ow);
  drv.writeScratchpadAll(0, 0, DSTherm::RES_12_BIT);
  drv.copyScratchpadAll(PARASITE_POWER);
  print1WireIDs();

  if (!ECCX08.begin()) {
    Serial.println("No ECCX08 present!");
    while (1);
  }
  Serial.println("");

  Serial.println("Crypto Serial Number:");
  String serNum = ECCX08.serialNumber();
  Serial.println(serNum);

// Check if the chip is already locked. If not, give it default Arduino configuration.
  if (!ECCX08.locked()) {
    Serial.println("ECCX08 is not locked");
  }
}

void loop() {
  delay(1000);
}


bool print1WireIDs() {
  for (const auto& id: (OneWireNg&)_ow) {
    const char *name = DSTherm::getFamilyName(id);
    printId(id);
/*    if (name) {
      Serial.print(" -> ");
      Serial.prinln(name);
    }
*/
  }
}

// From OneWireNG example
/* returns false if not supported */
static bool printId(const OneWireNg::Id& id)
{
    const char *name = DSTherm::getFamilyName(id);

    Serial.print(id[0], HEX);
    for (size_t i = 1; i < sizeof(OneWireNg::Id); i++) {
        Serial.print(':');
        if(id[i] < 16) {
          Serial.print("0");
        }
        Serial.print(id[i], HEX);
    }
    if (name) {
        Serial.print(" -> ");
        Serial.print(name);
    }
    Serial.println();

    return (name != NULL);
}
