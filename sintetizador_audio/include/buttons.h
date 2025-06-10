
#ifndef BUTTONS_H
#define BUTTONS_H

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include <stdio.h>

#define BUTTON_A 5  //  para iniciar ou parar a gravação
#define BUTTON_B 6  //  para reprozuir o som gravado no buzzer

void buttons_init();
void check_buttons();

#endif 