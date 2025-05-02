#ifndef ADC_TEMP_H
#define ADC_TEMP_H

#include <stdint.h>
#include "rp2040.h"

float adc_to_celsius(uint16_t adc_val);
float hal_temperature_read(); 

#endif