#include <Arduino.h>

const int currentSensor = 34;
double averageCurrent = 0.0;
int averageCount = 200;
double rawCurrentRange[2] = {1150.0, 2520.0};
double currentRange[2] = {-5.0, 5.0};

int getRawCurrent(int currentSensor);
double getCurrent(int rawCurrent);
double getContinuousAverage(double current);

void setup() {
  Serial.begin(9600);

  Serial.println("Current Sensor Test");
}

void loop() {
  int rawCurrent = getRawCurrent(currentSensor);
  double current = getCurrent(rawCurrent);
  double average = getContinuousAverage(current);

  Serial.print("Average: ");
  Serial.println(average);
  delay(1000);
}

int getRawCurrent(int currentSensor) {
  int rawCurrent = analogRead(currentSensor);
  return rawCurrent;
}

double getCurrent(int rawCurrent) {
  double current = map(rawCurrent, rawCurrentRange[0], rawCurrentRange[1], currentRange[0], currentRange[1]);
  return current;
}

double getContinuousAverage(double current) {
  averageCurrent = (averageCurrent * (averageCount - 1) + current) / averageCount;
  return averageCurrent;
}