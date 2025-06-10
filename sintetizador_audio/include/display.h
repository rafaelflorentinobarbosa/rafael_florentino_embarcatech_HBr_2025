
#ifndef DISPLAY_H
#define DISPLAY_H

#include "../drivers/ssd1306.h"
#include "hardware/i2c.h"
#include <string.h>
#include "pico/stdlib.h" 

#define I2C_SDA 14
#define I2C_SCL 15 

void screem_init();

void screem_mensage(const char* msg);
void screem_mensage_multiline(const char* msg);
void screem_centered_message(const char* msg);
void display_show_logo();

#endif 