#include <stdio.h>
#include "include/hal_led.h"
#include "include/led_embutido.h"

static int estado_led = 0;

void hal_led_init() {
    led_embutido_init();
}

void hal_led_toggle() {
    estado_led = !estado_led;
    led_embutido_set(estado_led);
}