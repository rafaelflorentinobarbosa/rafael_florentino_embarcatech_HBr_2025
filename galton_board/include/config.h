// arquivo config.h

#ifndef CONFIG_H
#define CONFIG_H

#include "pico/stdlib.h"

#define BUTTON_PIN   5
#define I2C_SDA     14
#define I2C_SCL     15

// Adicione estas constantes
#define TOTAL_BALLS 100
#define DROP_DELAY_MS 300

#define ANIMATION_DELAY 30


#define PIN_ROWS 6       // Aumente para 6 linhas (5 linhas de pinos)
#define BIN_COUNT 8      // Aumente para 8 caixas
#define BALL_SPEED 3     // Aumente a velocidade

#endif