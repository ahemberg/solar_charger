/*
 * Used for calculating current draw from adc_measurements.
 * requires two adcs measuring voltage on each side of a shunt resistor
 * of known resistance
 *
 * INTENDED SYSTEM_SETUP:
 *
 *   + --------| shunt |------|load|-----> -
 *  Supply   |             |           Ground
 *           |             |
 *       ADC_SUPPLY     ADC_SHUNT
 *
 *
 * The current is calculated using ohms law on the voltage drop across
 * the shunt:
 *    I = V/R => I = (V_SUPPLY - V_SHUNT) / R_SHUNT
 *
 */

 //TODO: Possibility to easilly change supply voltage and number of bits
 //      in ADC

 #pragma once

 #define SUPPLY_VOLTAGE 5.0

 #include <Arduino.h>

 class PowerMeter {
 public:
  const uint8_t  supply_pin;
  const uint8_t  shunt_pin;
  uint16_t supply_adc;
  uint16_t shunt_adc;
  float    shunt_resistance;
  float    supply_voltage;
  float    shunt_voltage;
  float    voltage_drop;
  float    current;
  float    power_loss;
  float    total_power;

  PowerMeter(uint8_t _supply_pin, uint8_t _shunt_pin, float _shunt_r) :
    supply_pin(_supply_pin),
    shunt_pin(_shunt_pin),
    shunt_resistance(_shunt_r) {};

  void measure();

 protected:
 private:
   void  measure_supply_voltage(); //TODO: Bool? -Depends on analogRead()
   void  measure_shunt_voltage(); //TODO: Bool? -Depends on analogRead()

   void  calculate_voltage_drop();
   void  calculate_current();
   float calculate_voltage(uint16_t adc_value);
   void  calculate_shunt_power_loss();
   void  calculate_total_power();
 };
