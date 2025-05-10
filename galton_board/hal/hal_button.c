// arquivo hal_button.c

#include "hal_button.h"
#include "pico/stdlib.h"

#define BUTTON_PIN 5

static bool last_button_state = false;

void hal_button_init(void) {
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);
}

bool hal_button_is_pressed(void) {
    return !gpio_get(BUTTON_PIN);
}

bool hal_button_was_pressed(void) {
    bool current_state = hal_button_is_pressed();
    bool was_pressed = !last_button_state && current_state;
    last_button_state = current_state;
    return was_pressed;
}