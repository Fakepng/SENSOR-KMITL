#include <Arduino.h>
#include <max6675.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

int max6675SO  = 21;
int max6675CS  = 22;
int max6675CLK = 23;

MAX6675 max6675(max6675CLK, max6675CS, max6675SO);

#define ONE_WIRE_BUS 19

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18T20(&oneWire);

void setup() {
  Serial.begin(9600);
  Serial.println("MAX6675 test");
  // wait for MAX chip to stabilize
  DS18T20.begin();
  delay(500);
}

void loop() {
  Serial.printf("MAX6675\n");
  Serial.printf("C: ");
  Serial.println(max6675.readCelsius());
  Serial.printf("F: ");
  Serial.println(max6675.readFahrenheit());
  Serial.printf("K: ");
  Serial.println(max6675.readCelsius() + 273);
  Serial.printf("DS18T20\n");
  DS18T20.requestTemperatures();
  Serial.printf("C: ");
  Serial.println(DS18T20.getTempCByIndex(0));
  delay(1000);
}

