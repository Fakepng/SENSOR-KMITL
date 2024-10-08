#include <Arduino.h>

const int SENSOR_PIN = 23;

void setup() {
  Serial.begin(9600);

  pinMode(22, OUTPUT);
  digitalWrite(22, HIGH);
}

void loop() {
  int isMetal = digitalRead(SENSOR_PIN);

  if (isMetal != HIGH) {
    Serial.println("Metal detected!");
  } else {
    Serial.println("No metal detected!");
  }

  delay(500);
}
