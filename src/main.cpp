#include <Arduino.h>
#include <LowPower.h>
#include <PowerMeter.h>

#define BATT_PIN A0
#define BUS_PIN A1
#define SOLAR_PIN A2

#define SHUNT_RES 4.7

PowerMeter batt_meter = PowerMeter(BATT_PIN, BUS_PIN, SHUNT_RES);
PowerMeter solar_meter = PowerMeter(SOLAR_PIN, BUS_PIN, SHUNT_RES);

void setup() {
  pinMode(BATT_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  batt_meter.measure();
  solar_meter.measure();

  Serial.print(batt_meter.supply_voltage);
  Serial.print(" ");
  Serial.print(solar_meter.supply_voltage);
  Serial.print(" ");
  Serial.print(batt_meter.shunt_voltage);
  Serial.println();
  Serial.print(batt_meter.current);
  Serial.print(" ");
  Serial.print(solar_meter.current);
  Serial.println();
  Serial.print(batt_meter.voltage_drop);
  Serial.print(" ");
  Serial.print(solar_meter.voltage_drop);
  Serial.println();
  Serial.print(batt_meter.power_loss);
  Serial.print(" ");
  Serial.print(solar_meter.power_loss);
  Serial.println();
  Serial.print("---------------------");
  Serial.println();

  Serial.flush();
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); //SLEEP

}
