#include <Arduino.h>

float R1 = 29870;
float R2 = 7504;
float m = 0.9816;
float b = 0.55;

int location = 0;
int sensorMedian[5] = {0,0,0,0,0};

void setup() {
  Serial.begin(9600);
}

void loop() {
  int rawSensor = analogRead(34);
  if (location > 4) {
    location = 0;
  }

  sensorMedian[location] = rawSensor;
  location++;

  if (location == 4) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4 - i; j++) {
        if (sensorMedian[j] > sensorMedian[j + 1]) {
          int temp = sensorMedian[j];
          sensorMedian[j] = sensorMedian[j + 1];
          sensorMedian[j + 1] = temp;
        }
      }
    }
    rawSensor = sensorMedian[2];

    float voltage = rawSensor * (3.3 / 4095.0) * ((R1 + R2) / R2);
    float calRaw = m * voltage + b;
    Serial.printf("RAW: %d", rawSensor);
    Serial.printf("Voltage: %f\n", calRaw);
    delay(1000);
  }

  delay(1000);
}
