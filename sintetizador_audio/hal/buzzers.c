#include "include/buzzers.h"
#include "hardware/pwm.h"
#include "pico/stdlib.h"

#define BUZZER_PIN 21 // ou 10, se quiser usar o segundo buzzer
#define SAMPLE_RATE 8000
#define NUM_SAMPLES (SAMPLE_RATE * 3)

static uint slice_num;
static uint channel;

void buzzers_init() {
    gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM);
    slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);
    channel = pwm_gpio_to_channel(BUZZER_PIN);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_wrap(&config, 4095);         // Resolução de 12 bits
    pwm_config_set_clkdiv(&config, 1.0f);       // Sem divisão extra
    pwm_init(slice_num, &config, true);

    pwm_set_gpio_level(BUZZER_PIN, 0); // Silencioso inicialmente
}

void buzzer_play(uint16_t *buffer) {
    const uint32_t delay_us = 1000000 / SAMPLE_RATE;

    for (uint32_t i = 0; i < NUM_SAMPLES; i++) {
        pwm_set_gpio_level(BUZZER_PIN, buffer[i]);
        sleep_us(delay_us);
    }

    pwm_set_gpio_level(BUZZER_PIN, 0); // para o som
}
