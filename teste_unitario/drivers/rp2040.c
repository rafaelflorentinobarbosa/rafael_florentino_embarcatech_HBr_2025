#include "hardware/adc.h"
#include "include/rp2040.h"
#include <stdio.h>

void sensor_temperatura_init() {
    adc_init();
    adc_set_temp_sensor_enabled(true);
}

uint16_t sensor_temperatura_read() {
    adc_select_input(4); 
    uint16_t adcValue = adc_read();
    printf("ADC Valor: %d\n", adcValue); 
    return adcValue;
}