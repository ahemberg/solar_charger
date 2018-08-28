#include <Arduino.h>
#include <LowPower.h>

#define BATT_PIN A0
#define BUS_PIN A1
#define SOLAR_PIN A2

#define SHUNT_RES 4.7

uint16_t batt_adc, solar_adc, bus_adc;
float batt_voltage, solar_voltage, bus_voltage,batt_voltage_drop,
      solar_voltage_drop, batt_current, solar_current, power_loss_batt,
      power_loss_solar;

void setup() {
  pinMode(BATT_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  batt_adc = analogRead(BATT_PIN);
  solar_adc = analogRead(SOLAR_PIN);
  bus_adc = analogRead(BUS_PIN);

  batt_voltage = ((float)batt_adc*5.0)/1023.0;
  solar_voltage = ((float)solar_adc*5.0)/1023.0;
  bus_voltage = ((float)bus_adc*5.0)/1023.0;

  batt_voltage_drop = batt_voltage - bus_voltage;
  solar_voltage_drop = solar_voltage - bus_voltage;

  batt_current = (batt_voltage_drop/SHUNT_RES)*1000.0;
  solar_current = (solar_voltage_drop/SHUNT_RES)*1000.0;

  power_loss_batt = batt_voltage_drop*batt_current;
  power_loss_solar = solar_voltage_drop*solar_current;

  Serial.print(batt_voltage);
  Serial.print(" ");
  Serial.print(solar_voltage);
  Serial.print(" ");
  Serial.print(bus_voltage);
  Serial.println();
  Serial.print(batt_current);
  Serial.print(" ");
  Serial.print(solar_current);
  Serial.println();
  Serial.print(power_loss_batt);
  Serial.print(" ");
  Serial.print(power_loss_solar);
  Serial.println();
  Serial.print("---------------------");
  Serial.println();

  Serial.flush();
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); //SLEEP
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); //SLEEP
  delay(1000); //Delay 1 sec for cap to charge
}
