#include "hardware/adc.h"
#include "hardware/dma.h"
#include "pico/stdlib.h"
#include "include/microphone.h"

// Inicialização do microfone
void microphone_init() {
    adc_init();
    adc_gpio_init(MICROPHONE);
}

// Detecção de som baseada na amplitude (diferença entre máximo e mínimo)
bool microphone_detect_sound() {
    adc_select_input(2); // ADC2 -> GPIO28

    uint16_t max_value = 0;
    uint16_t min_value = 4095;

    const int samples = 200;

    for (int i = 0; i < samples; i++) {
        uint16_t val = adc_read();
        if (val > max_value) max_value = val;
        if (val < min_value) min_value = val;
        sleep_us(200); // Pequeno delay para espaçar as leituras
    }

    uint16_t amplitude = max_value - min_value;

    // Teste e ajuste: valores típicos de 50 a 500 dependendo do microfone.
    const uint16_t threshold = 150; // quanto maior, menos sensível

    return amplitude > threshold;
}