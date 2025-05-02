#include <stdio.h>
#include "../include/adc_temp.h"
#include "../include/rp2040.h"
#include "unity/unity.h"

void setUp(void) {}
void tearDown(void) {}

void test_adc_to_celsius_approx_27C(void) {
    uint16_t adc_val = (uint16_t)((0.706f * 4095.0f) / 3.3f);
    float temp = adc_to_celsius(adc_val);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 27.0f, temp);// tolerencia de 0.1 graus Celsius, temperaura esperada de 27 graus Celsius
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_adc_to_celsius_approx_27C);
    printf("Teste concluídos.\n");   
    UNITY_END();
}