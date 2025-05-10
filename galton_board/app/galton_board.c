#include "pico/stdlib.h"
#include "hal_display.h"
#include "hal_button.h"
#include "config.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(void) {
    stdio_init_all();
    hal_button_init();
    hal_display_init();
    
    srand(time(NULL));
    uint8_t ball_counts[BIN_COUNT] = {0};
    Ball balls[TOTAL_BALLS] = {0};
    absolute_time_t last_drop_time = get_absolute_time();
    bool running = true;

    hal_display_print("Galton Board");
    sleep_ms(1500);

    while(1) {
        if (running) {
            // Libera nova bola periodicamente
            if (absolute_time_diff_us(last_drop_time, get_absolute_time()) > DROP_DELAY_MS * 1000) {
                for (int i = 0; i < TOTAL_BALLS; i++) {
                    if (!balls[i].active) {
                        balls[i].x = SSD1306_WIDTH / 2;
                        balls[i].y = 15;
                        balls[i].active = true;
                        last_drop_time = get_absolute_time();
                        hal_display_increment_counter(); // Incrementa o contador
                        break;
                    }
                }
            }

            bool any_active = false;
            uint16_t active_balls = 0;
            
            for (int i = 0; i < TOTAL_BALLS; i++) {
                if (balls[i].active) {
                    active_balls++;
                    any_active = true;
                    balls[i].y += BALL_SPEED;
                    
                    // Movimento aleatório
                    if (balls[i].y >= 15 && balls[i].y <= 15 + (PIN_ROWS * 10)) {
                        if ((balls[i].y % 3) == 0) {
                            int8_t move = (rand() % 5) - 2;
                            balls[i].x += move;
                            
                            if (balls[i].x < 5) balls[i].x = 5;
                            if (balls[i].x > SSD1306_WIDTH - 5) balls[i].x = SSD1306_WIDTH - 5;
                        }
                    }
                    
                    // Chegou na base
                    if (balls[i].y >= 70) {
                        balls[i].active = false;
                        int bin_width = (SSD1306_WIDTH - 20) / BIN_COUNT;
                        int bin = (balls[i].x - 10) / bin_width;
                        
                        if (bin < 0) bin = 0;
                        if (bin >= BIN_COUNT) bin = BIN_COUNT - 1;
                        
                        ball_counts[bin]++;
                    }
                }
            }

            hal_display_galton_board(ball_counts, balls, active_balls, true);
        }

        // Verifica botão
        if (hal_button_was_pressed()) {
            running = !running;
            if (!running) {
                hal_display_results(ball_counts);
            } else {
                // Reset opcional
                // hal_display_reset_counter();
                // memset(ball_counts, 0, sizeof(ball_counts));
            }
        }

        sleep_ms(ANIMATION_DELAY);
    }
}