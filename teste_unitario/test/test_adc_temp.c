#include <stdio.h>
#include "unity/unity.h"

void setUp(void) {}
void tearDown(void) {}

float adc_to_celsius(uint16_t adc_val)
{
    const float conversao = 3.3f / (1 << 12);
    float voltagem = adc_val * conversao;
    float temperatura = 27.0f - (voltagem - 0.706f) / 0.001721f;

    return temperatura;
}

void adc_to_celsius_unity_test(void)
{
    uint16_t tensao = 876;
    float temperatura_esperada = 27.0f;
    float buffer = 1.0f;
    TEST_ASSERT_FLOAT_WITHIN(buffer, temperatura_esperada, adc_to_celsius(tensao));
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(adc_to_celsius_unity_test);
    return UNITY_END();
}