#ifndef SENSOR_INPUT_H
#define SENSOR_INPUT_H

#include "drv/analog.h"
#include "usr/Machine_Control/hardware.h"
#include "usr/Machine_Control/inverter.h"

double read_adc(analog_channel_e adcCh);
double read_analog_sensor(analog_sensor_t sense);
void input_read_currents_three_phase_abc(double *Iabc, InverterThreePhase_t *inv);
void input_read_currents_three_phase_xy(double *Ixy, InverterThreePhase_t *inv);
void input_read_current_single_phase(double *Iz, InverterSinglePhase_t *inv);


#endif // SENSOR_INPUT_H
