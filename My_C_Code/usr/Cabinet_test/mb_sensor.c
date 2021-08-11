#include "usr/Cabinet_test/cabinet.h"
#include "usr/Cabinet_test/hardware.h"
#include "usr/Cabinet_test/inverter.h"
#include "drv/motherboard.h"
#include "usr/Cabinet_test/mb_sensor.h"

#include <stdint.h>
#include <stdio.h>
#include "sys/defines.h"
//#include "SIL_specific.h"

#define MB_CURRENtSENSOR_ZERO_HEX 0x8E38   // 2.5V vias
#define MB_CURRENtSENSOR_FULLADC 0xFFFF



double mb_int32todouble_current(int32_t data_raw){
    double data;
    int32_t data_raw_16;
    data_raw_16 = data_raw & 0x0000FFFF;
    data = ((double)data_raw_16 - (double)MB_CURRENtSENSOR_ZERO_HEX)/(double)MB_CURRENtSENSOR_FULLADC;
    data = data*4.5;
    return data;
}

double get_mb_current_adc(mb_channel_e mbCh){
    float mb_adc;
    int32_t data_raw;
    if(motherboard_get_data(mbCh, &data_raw)==SUCCESS){
        mb_adc = mb_int32todouble_current(data_raw);
    	//mb_adc = data_raw;
        //return (int32_t) data_raw;
        return (double) mb_adc;

    }
    return (double) 0;
}

double get_mb_current_adc(mb_sensor sensor){

    double adc = get_mb_current_adc(sensor.mbCh);
    double out = sensor.adcGain*adc + sensor.adcOffset;
    return out;
}

void get_mb_currents_three_phase_abc(double *Iabc, InverterThreePhase_t *inv){

    //sensor = inv->HW->mb_csensor->mb_Ia;
	//Iabc[0] = read_mb_current_sensor(sensor);
    Iabc[0] = get_mb_current_adc(inv->HW->mb_csensor.mb_Ia);
    //sensor = inv->HW->mb_csensor->Ib;
    Iabc[1] = get_mb_current_adc(inv->HW->mb_csensor.mb_Ib);
	//Iabc[1] = read_mb_current_sensor(sensor);
    //sensor = inv->HW->mb_csensor->Ic;
    Iabc[2] = get_mb_current_adc(inv->HW->mb_csensor.mb_Ic);
	//Iabc[2] = read_mb_current_sensor(sensor);
}


