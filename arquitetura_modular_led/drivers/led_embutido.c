#include <stdio.h>
#include "pico/cyw43_arch.h"
#include "include/led_embutido.h"

void led_embutido_init() {
    cyw43_arch_init();
}

void led_embutido_set(int state) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, state);
}