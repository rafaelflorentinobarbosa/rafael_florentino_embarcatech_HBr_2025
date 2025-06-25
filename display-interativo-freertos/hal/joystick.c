#include "include/joystick.h"
#include "pico/stdlib.h"  // Adiciona as funções sleep_us e sleep_ms

// Inicializa os ADCs e o botão do joystick
void joystick_init() {
    adc_init();

    // Configura os pinos dos eixos como entrada ADC
    adc_gpio_init(JOYSTICK_VRX);
    adc_gpio_init(JOYSTICK_VRY);

    // Configura o pino do botão como entrada digital com pull-up
    gpio_init(JOYSTICK_SW);
    gpio_set_dir(JOYSTICK_SW, GPIO_IN);
    gpio_pull_up(JOYSTICK_SW);
}

// Faz a leitura dos eixos X e Y do joystick
void joystick_read(uint16_t *x, uint16_t *y) {
    // Leitura do eixo X
    adc_select_input(JOYSTICK_ADC_CHANNEL_X);
    sleep_us(2); // Delay para estabilidade
    *x = adc_read();

    // Leitura do eixo Y
    adc_select_input(JOYSTICK_ADC_CHANNEL_Y);
    sleep_us(2); // Delay para estabilidade
    *y = adc_read();
}

// Verifica se o botão do joystick está pressionado
bool joystick_button_pressed() {
    // O botão é ativo em nível baixo
    return !gpio_get(JOYSTICK_SW);
}