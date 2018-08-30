#include "PowerMeter.h"

void PowerMeter::measure() {
  measure_supply_voltage();
  measure_shunt_voltage();
  calculate_voltage_drop();
  calculate_current();
  calculate_shunt_power_loss();
  calculate_total_power();
}

void PowerMeter::measure_supply_voltage() {
  supply_adc = analogRead(supply_pin);
  supply_voltage = calculate_voltage(supply_adc);
}

void PowerMeter::measure_shunt_voltage() {
  shunt_adc = analogRead(shunt_pin);
  shunt_voltage = calculate_voltage(shunt_adc);
}

void PowerMeter::calculate_voltage_drop() {
  voltage_drop = supply_voltage - shunt_voltage;
}

void PowerMeter::calculate_current() {
  current = voltage_drop/shunt_resistance;
}

float PowerMeter::calculate_voltage(uint8_t adc_value) {
  return ((float)adc_value*SUPPLY_VOLTAGE)/1023.0;
}

void PowerMeter::calculate_shunt_power_loss() {
  power_loss = abs(current*voltage_drop);
}

void PowerMeter::calculate_total_power() {
  total_power = abs(current*SUPPLY_VOLTAGE);
}
