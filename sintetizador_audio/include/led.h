
#ifndef LED_H
#define LED_H

#include <stdio.h>
#include "pico/stdlib.h"    // Geralmente útil para sleep_ms e outras utilidades
#include "hardware/gpio.h" 

// Leds RGB solitario
#define LED_PIN_AZUL 12 // LED Azul
#define LED_PIN_VERDE 11 // LED Verde
#define LED_PIN_VERMELHO 13 // LED Vermelho

void led_init();
void turn_off_led();
void turn_on_blue();
void turn_on_green();
void turn_on_red();

#endif 