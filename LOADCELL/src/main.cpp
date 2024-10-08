#include <Arduino.h>
#include <HX711.h>

const int LOADCELL_DOUT_PIN = 23;
const int LOADCELL_SCK_PIN = 22;

HX711 scale;

// How to calibrate your load cell
// 1. Call set_scale() with no parameter.
// 2. Call tare() with no parameter.
// 3. Place a known weight on the scale and call get_units(10).
// 4. Divide the result in step 3 to your known weight. You should get about the parameter you need to pass to set_scale().
// 5. Adjust the parameter in step 4 until you get an accurate reading.

void setup() {
  Serial.begin(9600);
  Serial.println("Load Cell HX711 Test");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  scale.set_scale(-2947260);
  scale.tare();
}

void loop() {
  float weight = scale.get_units(10);
  if (weight < 1) {
    Serial.print("Reading: ");
    Serial.print(weight * 1000.0);
    Serial.println(" g");
  } else {
    Serial.print("Reading: ");
    Serial.print(weight);
    Serial.println(" kg");
  }

  scale.power_down();
  delay(5000);
  scale.power_up();
}