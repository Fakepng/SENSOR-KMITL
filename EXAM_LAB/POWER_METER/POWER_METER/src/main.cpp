#include <Arduino.h>

// Voltage analog to pin 34
// Current analog to pin 35

const int DEBUG = 1;

const int ROLLING_AVERAGE_SIZE = 10;

const int VOLTAGE_SENSOR = 34;
const double VOLTAGE_RANGE[2][2] = {
  {0.0, 4096.0}, // ADC raw conversion
  {0.0, 25.0} // Voltage range
};
int VOLTAGE_AVERAGE[ROLLING_AVERAGE_SIZE];
int VOLTAGE_AVERAGE_INDEX = 0;

const int CURRENT_SENSOR = 35;
const double CURRENT_RANGE[2][2] = {
  {0.0, 4096.0}, // ADC raw conversion
  {-5.0, 5.0} // Current range
};
int CURRENT_AVERAGE[ROLLING_AVERAGE_SIZE];
int CURRENT_AVERAGE_INDEX = 0;

double readVoltage();
double readCurrent();
double readPower(double voltage, double current);
double readResistance(double voltage, double current);
double mapFloat(double val, double in_min, double in_max, double out_min, double out_max);

void setup() {
  Serial.begin(9600);

  pinMode(VOLTAGE_SENSOR, INPUT);
  pinMode(CURRENT_SENSOR, INPUT);

  Serial.println("Power meter");
}

void loop() {
  if (DEBUG) {
    double voltage = readVoltage();
    double current = readCurrent();

    Serial.print("Raw voltage: "); Serial.println(voltage);
    Serial.print("Raw current: "); Serial.println(current);

    delay(1000);
    return;
  }

  double voltage = readVoltage();
  double current = readCurrent();
  double power = readPower(voltage, current);
  double resistance = readResistance(voltage, current);

  Serial.print("Voltage: "); Serial.print(voltage); Serial.println(" V");
  Serial.print("Current: "); Serial.print(current); Serial.println(" A");
  Serial.print("Power: "); Serial.print(power); Serial.println(" W");
  Serial.print("Resistance: "); Serial.print(resistance); Serial.println(" Ohm");

  delay(1000);
}

double readVoltage() {
  int raw = analogRead(VOLTAGE_SENSOR);

  VOLTAGE_AVERAGE[VOLTAGE_AVERAGE_INDEX] = raw;
  VOLTAGE_AVERAGE_INDEX = (VOLTAGE_AVERAGE_INDEX + 1) % ROLLING_AVERAGE_SIZE;

  double sum = 0;
  for (int i = 0; i < ROLLING_AVERAGE_SIZE; i++) {
    sum += VOLTAGE_AVERAGE[i];
  }
  double avg = sum / ROLLING_AVERAGE_SIZE;

  if (DEBUG) {
    return avg;
  }

  return mapFloat(avg, VOLTAGE_RANGE[0][0], VOLTAGE_RANGE[0][1], VOLTAGE_RANGE[1][0], VOLTAGE_RANGE[1][1]);
}

double readCurrent() {
  int raw = analogRead(CURRENT_SENSOR);

  CURRENT_AVERAGE[CURRENT_AVERAGE_INDEX] = raw;
  CURRENT_AVERAGE_INDEX = (CURRENT_AVERAGE_INDEX + 1) % ROLLING_AVERAGE_SIZE;

  double sum = 0;
  for (int i = 0; i < ROLLING_AVERAGE_SIZE; i++) {
    sum += CURRENT_AVERAGE[i];
  }
  double avg = sum / ROLLING_AVERAGE_SIZE;

  if (DEBUG) {
    return avg;
  }

  return mapFloat(avg, CURRENT_RANGE[0][0], CURRENT_RANGE[0][1], CURRENT_RANGE[1][0], CURRENT_RANGE[1][1]);
}

double readPower(double voltage, double current) {
  return voltage * current;
}

double readResistance(double voltage, double current) {
  if (current <= 0) {
    return 0;
  }

  return voltage / current;
}

double mapFloat(double val, double in_min, double in_max, double out_min, double out_max) {
    return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}