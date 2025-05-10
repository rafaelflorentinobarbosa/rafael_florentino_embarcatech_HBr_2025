// ssd1309.h
#ifndef SSD1309_H
#define SSD1309_H

#include "pico/stdlib.h"
#include "hardware/i2c.h"

// Definições básicas para display OLED
#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64
#define SSD1306_BUFFER_SIZE (SSD1306_WIDTH * SSD1306_HEIGHT / 8)

// Estrutura para configuração do display
typedef struct {
    uint8_t width;
    uint8_t height;
    bool external_vcc;
    uint8_t address;
    i2c_inst_t *i2c;
} ssd1306_t;

// Área de renderização
typedef struct {
    uint8_t start_column;
    uint8_t end_column;
    uint8_t start_page;
    uint8_t end_page;
} render_area;

// Protótipos das funções básicas
void ssd1306_init(ssd1306_t *ssd);
void ssd1306_send_command(uint8_t cmd);
void ssd1306_send_buffer(uint8_t *buffer, int length);

// Funções de desenho
void ssd1306_set_pixel(uint8_t *buffer, int x, int y, bool set);
void ssd1306_draw_line(uint8_t *buffer, int x0, int y0, int x1, int y1, bool set);
void ssd1306_draw_char(uint8_t *buffer, int x, int y, char c);
void ssd1306_draw_string(uint8_t *buffer, int x, int y, char *str);

// Funções auxiliares
void calculate_render_area_buffer_length(render_area *area);
void render_on_display(uint8_t *buffer, render_area *area);

#endif