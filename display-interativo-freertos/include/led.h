#ifndef LED_H
#define LED_H

// Definições dos pinos
#define LED_G 11
#define LED_B 12
#define LED_R 13

// Prototipos das funções
void led_rgb_init();
void set_led_color(int color);

#endif