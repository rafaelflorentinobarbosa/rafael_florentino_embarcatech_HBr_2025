#include "include/buzzers.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"

// Variáveis internas PWM
static uint slice_num;
static uint channel;

// Inicializa o buzzer
void buzzers_init() {
    gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM);
    slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);
    channel = pwm_gpio_to_channel(BUZZER_PIN);

    pwm_set_enabled(slice_num, false);
}

// PWM para sons simples
void buzzer_play_tone(uint32_t freq, uint8_t duty) {
    uint32_t clock = 125000000;
    uint32_t wrap = clock / freq - 1;

    pwm_set_wrap(slice_num, wrap);
    uint32_t level = (wrap * duty) / 100;
    pwm_set_chan_level(slice_num, channel, level);

    pwm_set_enabled(slice_num, true);
}

void buzzer_stop_tone() {
    pwm_set_enabled(slice_num, false);
}


// Alarme contínuo (tom fixo)
void buzzer_play() {
    buzzer_play_tone(1000, 50); // 1000 Hz
}

void buzzer_stop() {
    pwm_set_chan_level(slice_num, channel, 0);
    pwm_set_enabled(slice_num, false);
    gpio_put(BUZZER_PIN, 0); 
}


// Melodia 
void buzzer_play_melody() {
    const uint32_t NOTE_C = 261;
    const uint32_t NOTE_D = 294;
    const uint32_t NOTE_E = 329;
    const uint32_t NOTE_F = 349;
    const uint32_t NOTE_G = 392;
    const uint32_t NOTE_A = 440;
    const uint32_t NOTE_B = 493;
    const uint32_t NOTE_C_HIGH = 523;

    struct {
        uint32_t freq;
        uint32_t duration;
    } melody[] = {
        {NOTE_C, 300}, {NOTE_D, 300}, {NOTE_E, 300}, {NOTE_F, 300},
        {NOTE_G, 500}, {NOTE_C_HIGH, 500},
        {0, 300},
        {NOTE_G, 300}, {NOTE_F, 300}, {NOTE_E, 300}, {NOTE_D, 300}, {NOTE_C, 500},
    };

    int melody_size = sizeof(melody) / sizeof(melody[0]);

    for (int i = 0; i < melody_size; i++) {
        if (melody[i].freq == 0) {
            buzzer_stop_tone();
        } else {
            buzzer_play_tone(melody[i].freq, 50);
        }
        sleep_ms(melody[i].duration);
    }

    buzzer_stop_tone();
}