
#include "include/adc_temp.h"
#include "include/rp2040.h"
#include <stdio.h>

float adc_to_celsius(uint16_t adc_val) {
    float voltage = (adc_val * 3.3f) / 4095.0f;
    return 27.0f - (voltage - 0.706f) / 0.001721f;
}

float hal_temperature_read() {
    uint16_t adcValue = sensor_temperatura_read(); // Lê o sensor de temperatura
    printf("Hal ADC Value: %d\n", adcValue); //print para debug
    return adc_to_celsius(adcValue); //devolve o valor convertido para Celsius
}