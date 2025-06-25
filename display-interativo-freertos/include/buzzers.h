#ifndef BUZZERS_H
#define BUZZERS_H

#include <stdint.h>
#include <stdbool.h>

// ======================
// Definição dos pinos
#define BUZZER_PIN 21
#define BUZZER_PIN_B 10

// ======================
// Funções básicas (modo digital)
void buzzers_init();
void buzzer_play();
void buzzer_stop();

// ======================
// Sons PWM customizados
void buzzer_play_tone(uint32_t freq, uint8_t duty);
void buzzer_stop_tone();

// ======================
// Efeitos sonoros
void buzzer_play_melody();         
       

#endif
