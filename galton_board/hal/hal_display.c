#include "hal_display.h"
#include "ssd1309.h"
#include "config.h"
#include <string.h>
#include <stdio.h>

uint8_t ssd[SSD1306_BUFFER_SIZE];
render_area frame_area = {
    .start_column = 0,
    .end_column = SSD1306_WIDTH - 1,
    .start_page = 0,
    .end_page = (SSD1306_HEIGHT / 8) - 1
};

ssd1306_t display = {
    .width = SSD1306_WIDTH,
    .height = SSD1306_HEIGHT,
    .external_vcc = false,
    .address = 0x3C,
    .i2c = i2c1
};

static uint32_t balls_released = 0;

void hal_display_init() {
    i2c_init(i2c1, 400 * 1000);
    gpio_set_function(14, GPIO_FUNC_I2C);
    gpio_set_function(15, GPIO_FUNC_I2C);
    gpio_pull_up(14);
    gpio_pull_up(15);
    
    ssd1306_init(&display);
    calculate_render_area_buffer_length(&frame_area);
    memset(ssd, 0, SSD1306_BUFFER_SIZE);
    render_on_display(ssd, &frame_area);
}

void hal_display_increment_counter(void) {
    balls_released++;
}

uint32_t hal_display_get_ball_count(void) {
    return balls_released;
}

void hal_display_reset_counter(void) {
    balls_released = 0;
}

void draw_circle(uint8_t *buffer, uint8_t x, uint8_t y, uint8_t radius) {
    for (int8_t i = -radius; i <= radius; i++) {
        for (int8_t j = -radius; j <= radius; j++) {
            if (i*i + j*j <= radius*radius) {
                ssd1306_set_pixel(buffer, x + i, y + j, true);
            }
        }
    }
}

void hal_display_galton_board(uint8_t *ball_counts, Ball *balls, uint16_t active_balls, bool show_animation) {
    memset(ssd, 0, SSD1306_BUFFER_SIZE);
    
    // Contador de bolas liberadas
    char counter_str[16];
    snprintf(counter_str, sizeof(counter_str), "Total: %lu", balls_released);
    ssd1306_draw_string(ssd, 2, 2, counter_str);
    
    // Desenha pinos começando da segunda linha
    for (uint8_t row = 1; row < PIN_ROWS; row++) {
        uint8_t pins_in_row = row;  // Uma pino a menos que a linha
        uint8_t start_x = (SSD1306_WIDTH - (pins_in_row * 14)) / 2;
        
        for (uint8_t pin = 0; pin < pins_in_row; pin++) {
            uint8_t x = start_x + (pin * 14);
            uint8_t y = 20 + (row * 10);
            draw_circle(ssd, x, y, 1);
        }
    }
    
    // Desenha bolas ativas
    if (show_animation) {
        for (uint16_t i = 0; i < TOTAL_BALLS; i++) {
            if (balls[i].active) {
                draw_circle(ssd, balls[i].x, balls[i].y, 2);
            }
        }
    }
    
    // Desenha caixas coletoras
    uint8_t bin_width = 16;
    uint8_t start_x = (SSD1306_WIDTH - (BIN_COUNT * bin_width)) / 2;
    uint8_t bin_y = 70;
    
    for (uint8_t bin = 0; bin < BIN_COUNT; bin++) {
        uint8_t x = start_x + (bin * bin_width);
        ssd1306_draw_line(ssd, x, bin_y, x + bin_width - 2, bin_y, true);
        ssd1306_draw_line(ssd, x, bin_y, x, bin_y + 10, true);
        ssd1306_draw_line(ssd, x + bin_width - 2, bin_y, x + bin_width - 2, bin_y + 10, true);
        
        char count_str[4];
        snprintf(count_str, sizeof(count_str), "%d", ball_counts[bin]);
        ssd1306_draw_string(ssd, x + (bin_width/2) - 3, bin_y + 12, count_str);
    }
    
    render_on_display(ssd, &frame_area);
}

void hal_display_print(const char *message) {
    memset(ssd, 0, SSD1306_BUFFER_SIZE);
    ssd1306_draw_string(ssd, 5, 16, (char *)message);
    render_on_display(ssd, &frame_area);
}

void hal_display_results(uint8_t *ball_counts) {
    memset(ssd, 0, SSD1306_BUFFER_SIZE);
    
    uint8_t bin_width = 16;
    uint8_t start_x = (SSD1306_WIDTH - (BIN_COUNT * bin_width)) / 2;
    uint8_t bin_y = 20;
    
    ssd1306_draw_string(ssd, 30, 5, "Resultados");
    
    for (uint8_t bin = 0; bin < BIN_COUNT; bin++) {
        uint8_t x = start_x + (bin * bin_width);
        ssd1306_draw_line(ssd, x, bin_y, x + bin_width - 2, bin_y, true);
        ssd1306_draw_line(ssd, x, bin_y, x, bin_y + 10, true);
        ssd1306_draw_line(ssd, x + bin_width - 2, bin_y, x + bin_width - 2, bin_y + 10, true);
        
        char count_str[4];
        snprintf(count_str, sizeof(count_str), "%d", ball_counts[bin]);
        ssd1306_draw_string(ssd, x + (bin_width/2) - 3, bin_y + 12, count_str);
    }
    
    render_on_display(ssd, &frame_area);
}