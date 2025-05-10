// arquivo hal_button.h

#ifndef HAL_BUTTON_H
#define HAL_BUTTON_H

#include <stdbool.h>

void hal_button_init(void);
bool hal_button_is_pressed(void);
bool hal_button_was_pressed(void);  // Nova função para detectar pressionamento

#endif