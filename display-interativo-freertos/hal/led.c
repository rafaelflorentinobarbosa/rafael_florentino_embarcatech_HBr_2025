#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "include/led.h"  // Inclui o cabeçalho com os pinos

void led_rgb_init() {
    gpio_init(LED_R); gpio_set_dir(LED_R, GPIO_OUT);
    gpio_init(LED_G); gpio_set_dir(LED_G, GPIO_OUT);
    gpio_init(LED_B); gpio_set_dir(LED_B, GPIO_OUT);

    // Inicia desligado
    gpio_put(LED_R, 0);
    gpio_put(LED_G, 0);
    gpio_put(LED_B, 0);
}

void set_led_color(int color) {
    // Desliga todos primeiro
    gpio_put(LED_R, 0);
    gpio_put(LED_G, 0);
    gpio_put(LED_B, 0);

    // Liga o LED desejado
    switch(color) {
        case 0: gpio_put(LED_B, 1); break; // Azul
        case 1: gpio_put(LED_G, 1); break; // Verde
        case 2: gpio_put(LED_R, 1); break; // Vermelho
        case -1: default: break;           // Desligado
    }
}
