#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "hardware/adc.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdint.h>
#include <stdbool.h>

// Definições dos pinos do joystick
#define JOYSTICK_VRX 26      // Eixo X (ADC0)
#define JOYSTICK_VRY 27      // Eixo Y (ADC1)
#define JOYSTICK_SW  22      // Botão do joystick

// Canais ADC correspondentes
#define JOYSTICK_ADC_CHANNEL_X 0
#define JOYSTICK_ADC_CHANNEL_Y 1

// Funções
void joystick_init();                          // Inicializa ADC e botão
void joystick_read(uint16_t *x, uint16_t *y);   // Lê valores dos eixos X e Y
bool joystick_button_pressed();                 // Verifica se o botão está pressionado

#endif