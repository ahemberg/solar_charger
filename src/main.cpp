#include <Arduino.h>
#include <LowPower.h>
#include <PowerMeter.h>

const uint8_t solar_pin = A2;
const uint8_t bus_pin = A1;
const uint8_t batt_pin = A0;
const uint8_t led_discharge_pin = 9;
const uint8_t led_charge_pin = 10;
const uint8_t led_both_pin = 11;

const float shunt_res = 2.2;


float ic_current, charge_current;


PowerMeter batt_meter = PowerMeter(batt_pin, bus_pin, shunt_res);
PowerMeter solar_meter = PowerMeter(solar_pin, bus_pin, shunt_res);

void setup() {
  pinMode(batt_pin, INPUT);
  pinMode(bus_pin, INPUT);
  pinMode(solar_pin, INPUT);
  pinMode(led_discharge_pin, OUTPUT);
  pinMode(led_charge_pin, OUTPUT);
  pinMode(led_both_pin, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  delay(1000); //Let system settle

  batt_meter.measure();
  solar_meter.measure();

  ic_current = batt_meter.current + solar_meter.current;

  //Calculate current charging battery
  if (batt_meter.current < 0) {
    charge_current = (solar_meter.supply_voltage - batt_meter.supply_voltage)/(shunt_res*2);
  } else {
    charge_current = 0;
  }

  //INTERACT
  digitalWrite(led_charge_pin, LOW);
  digitalWrite(led_discharge_pin, LOW);
  digitalWrite(led_both_pin, LOW);
  if (charge_current > 0) {
    digitalWrite(led_charge_pin, HIGH);
  } else if (batt_meter.current > 0 && solar_meter.current > 0) {
    digitalWrite(led_both_pin, HIGH);
  } else {
    digitalWrite(led_discharge_pin, HIGH);
  }
  
  //Sleep for one minute (52s)
  for (uint8_t i=0; i<10; i++) {
      LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }

}
