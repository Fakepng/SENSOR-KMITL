#include <Arduino.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

const int REPORTING_PERIOD_MS = 100;

PulseOximeter pox;

unsigned long tsLastReport = 0;

void onBeatDetected() {
  Serial.println("B:1");
}

void setup() {
  Serial.begin(115200);

  if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }
  pox.setIRLedCurrent(MAX30100_LED_CURR_46_8MA);

  // pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop() {
  pox.update();

  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    Serial.print(">Heartrate:");
    Serial.println(pox.getHeartRate());
    Serial.print(">OxygenSat:");
    Serial.println(pox.getSpO2());

    tsLastReport = millis();
  }
}

