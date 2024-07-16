#include <Arduino.h>

const int ANALOG_PIN = 32;

void setup() {
  Serial.begin(115200);
}

void loop() {
  int value = analogRead(ANALOG_PIN);
  float voltage = value * (30 / 4095.0);

  Serial.printf("Analog value: ");
  Serial.printf("%4d    ", value);
  Serial.printf("Voltage: ");
  Serial.printf("%1.2f\n", voltage);

  delay(100);
}