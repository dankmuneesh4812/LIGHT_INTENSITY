#include "arduino_secrets.h"
/*
  Sketch generated by the Arduino IoT Cloud Thing "Light_intensity"
  https://create.arduino.cc/cloud/things/aff9ab24-1454-4fc6-852e-2ea9711ffe19

  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  CloudIlluminance sunlight_value;
  bool led;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

#include "thingProperties.h"
#include <Arduino.h>
#include <hp_BH1750.h>
hp_BH1750 sensor;


void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1000);

  // Defined in thingProperties.h
  initProperties();
  pinMode(LED_BUILTIN, OUTPUT);
  sensor.begin(BH1750_TO_GROUND);
  sensor.start();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
  */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  // Your code here
  float lux;
  lux = sensor.getLux();
  Serial.print("Light Lux Level: ");
  Serial.print(lux);
  if (lux > 500)
  {
    sunlight_value = sensor.getLux();
    led = true;
    digitalWrite(LED_BUILTIN, led);
    Serial.println(" Sunlight:detected");

  }
  else
  {
    led = false;
    digitalWrite(LED_BUILTIN, led);
    Serial.println(" Sunlight:not detected");

  }
  delay(1000);
  sensor.start();


}
/*
  Since Led is READ_WRITE variable, onLedChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onLedChange()  {
  // Add your code here to act upon Led change
}
