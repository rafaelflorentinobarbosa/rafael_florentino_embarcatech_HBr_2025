#ifndef HAL_DISPLAY_H
#define HAL_DISPLAY_H

#include <stdint.h>
#include <stdbool.h>
#include "ssd1309.h"

typedef struct {
    uint8_t x;
    uint8_t y;
    bool active;
} Ball;

// Adicione esta declaração
void hal_display_increment_counter(void);
void hal_display_reset_counter(void);
uint32_t hal_display_get_ball_count(void);

void hal_display_init(void);
void hal_display_print(const char *message);
void hal_display_galton_board(uint8_t *ball_counts, Ball *balls, uint16_t total_balls, bool show_animation);
void hal_display_results(uint8_t *ball_counts);

#endif