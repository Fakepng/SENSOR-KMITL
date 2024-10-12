#include <Arduino.h>
#include <MQUnifiedsensor.h>
#include <HX711.h>
#include <max6675.h>

// MQ135 A0 to pin 36 (VP)
// Loadcell DOUT to pin 23
// Loadcell SCK to pin 22
// MAX6675 SO to pin 17
// MAX6675 CS to pin 18
// MAX6675 CLK to pin 19

const int DEBUG = 1;

#define Board "ESP-32"
#define Pin 36
#define Type "MQ-135"
#define Voltage_Resolution 3.3
#define ADC_Bit_Resolution 12
#define RatioMQ135CleanAir 3.6

MQUnifiedsensor MQ135(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin, Type);

const int LOADCELL_DOUT_PIN  = 23;
const int LOADCELL_SCK_PIN   = 22;
const int LOADCELL_SCALE_CAL = -2947260;

HX711 scale;

const int max6675SO  = 17;
const int max6675CS  = 18;
const int max6675CLK = 19;

MAX6675 thermocouple(max6675CLK, max6675CS, max6675SO);

const int VIBRATION_PIN = 16;

void IRAM_ATTR VIBRATION_ISR();

void setup() {
  Serial.begin(9600);

  MQ135.setRegressionMethod(1);
  MQ135.init();

  Serial.print("Calibrating please wait.");
  float calcR0 = 0;
  for(int i = 1; i<=10; i ++)
  {
    MQ135.update();
    calcR0 += MQ135.calibrate(RatioMQ135CleanAir);
    Serial.print(".");
  }
  MQ135.setR0(calcR0/10);
  Serial.println("  done!.");

  if(isinf(calcR0)) {Serial.println("Warning: Conection issue, R0 is infinite (Open circuit detected) please check your wiring and supply"); while(1);}
  if(calcR0 == 0){Serial.println("Warning: Conection issue found, R0 is zero (Analog pin shorts to ground) please check your wiring and supply"); while(1);}

  Serial.print("Calibration successful R0 = ");
  Serial.println(calcR0);

  attachInterrupt(VIBRATION_PIN, VIBRATION_ISR, RISING);

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  if (DEBUG) {
    Serial.println("Calibrating load cell...");
    scale.set_scale();
  } else {
    scale.set_scale(LOADCELL_SCALE_CAL);
  }
  scale.tare();

  Serial.println("Starting loop...");
}

void loop() {
  MQ135.update();

  MQ135.setA(605.18); MQ135.setB(-3.937); // Configure the equation to calculate CO concentration value
  float CO = MQ135.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup

  MQ135.setA(77.255); MQ135.setB(-3.18); //Configure the equation to calculate Alcohol concentration value
  float Alcohol = MQ135.readSensor(); // SSensor will read PPM concentration using the model, a and b values set previously or from the setup

  MQ135.setA(110.47); MQ135.setB(-2.862); // Configure the equation to calculate CO2 concentration value
  float CO2 = MQ135.readSensor() + 400; // Sensor will read PPM concentration using the model, a and b values set previously or from the setup

  MQ135.setA(44.947); MQ135.setB(-3.445); // Configure the equation to calculate Toluen concentration value
  float Toluen = MQ135.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup

  MQ135.setA(102.2 ); MQ135.setB(-2.473); // Configure the equation to calculate NH4 concentration value
  float NH4 = MQ135.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup

  MQ135.setA(34.668); MQ135.setB(-3.369); // Configure the equation to calculate Aceton concentration value
  float Aceton = MQ135.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup

  Serial.println("Reading MQ135:");
  Serial.print("  CO: "); Serial.println(CO);
  Serial.print("  Alcohol: "); Serial.println(Alcohol);
  Serial.print("  CO2: "); Serial.println(CO2);
  Serial.print("  Toluen: "); Serial.println(Toluen);
  Serial.print("  NH4: "); Serial.println(NH4);
  Serial.print("  Aceton: "); Serial.println(Aceton);
  Serial.println();

  float weight = scale.get_units(10);
  Serial.println(weight);if (weight < 1) {
    Serial.print("Reading load cell: ");
    Serial.print(weight * 1000.0);
    Serial.println(" g");
  } else {
    Serial.print("Reading load cell: ");
    Serial.print(weight);
    Serial.println(" kg");
  }
  Serial.println();

  Serial.println("Reading thermocouple: ");
  Serial.print("  C: ");
  Serial.print(thermocouple.readCelsius());
  Serial.println(" C");
  Serial.print("  F: ");
  Serial.print(thermocouple.readFahrenheit());
  Serial.println(" F");
  Serial.print("  K: ");
  Serial.print(thermocouple.readCelsius() + 273.0);
  Serial.println();

  scale.power_down();
  delay(5000);
  scale.power_up();
}

void IRAM_ATTR VIBRATION_ISR() {
  Serial.println("Vibration detected!");
}