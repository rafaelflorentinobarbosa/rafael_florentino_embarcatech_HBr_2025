#include <stdio.h>
#include "pico/stdlib.h"
#include "include/display.h"
#include "include/buttons.h"
#include "include/microphone.h"
#include "include/led.h"
#include "include/buzzers.h"

// Estados da aplicação
typedef enum {
    STATE_INIT_DISPLAY,
    STATE_WELCOME,
    STATE_WAIT_FOR_RECORD,
    STATE_RECORDING,
    STATE_WAIT_FOR_PLAY
} ProgramState;

ProgramState current_state = STATE_INIT_DISPLAY;

// Estados anteriores dos botões para detecção de borda
static bool button_a_last_state = true;
static bool button_b_last_state = true;

int main() {
    stdio_init_all();

    // Inicializações dos módulos
    screem_init();
    buttons_init();
    microphone_init();
    led_init();
    buzzers_init();

    // Buffer de áudio compartilhado
    extern uint16_t audio_buffer[NUM_SAMPLES];

    while (1) {
        // Lê estados atuais dos botões
        bool button_a_current_state = gpio_get(BUTTON_A);
        bool button_b_current_state = gpio_get(BUTTON_B);

        switch (current_state) {
            case STATE_INIT_DISPLAY:
                turn_on_green();
                display_show_logo();
                sleep_ms(2000);
                current_state = STATE_WELCOME;
                break;

            case STATE_WELCOME:
                screem_centered_message("Bem Vindo!");
                sleep_ms(2000);
                current_state = STATE_WAIT_FOR_RECORD;
                break;

            case STATE_WAIT_FOR_RECORD:
                screem_mensage_multiline("Aperte A\nGravar");
                turn_on_green();

                if (button_a_last_state && !button_a_current_state) {
                    sleep_ms(50); 
                    if (!gpio_get(BUTTON_A)) {
                        microphone_start_recording(audio_buffer);
                        current_state = STATE_RECORDING;
                    }
                }
                break;

            case STATE_RECORDING:
                turn_on_red();
                screem_mensage_multiline("Gravando...\nAperte A\nParar");
                microphone_process_recording();

                if (button_a_last_state && !button_a_current_state) {
                    sleep_ms(50);
                    if (!gpio_get(BUTTON_A)) {
                        current_state = STATE_WAIT_FOR_PLAY;
                    }
                }

                // Verifica fim automático
                if (!is_recording()) {
                    current_state = STATE_WAIT_FOR_PLAY;
                }
                break;

            case STATE_WAIT_FOR_PLAY:
                turn_on_green();
                screem_mensage_multiline("Aperte B\nReproduzir");

                if (button_b_last_state && !button_b_current_state) {
                    sleep_ms(50);
                    if (!gpio_get(BUTTON_B)) {
                        turn_on_blue();
                        buzzer_play(audio_buffer);
                        turn_on_green();
                        current_state = STATE_WAIT_FOR_RECORD;
                    }
                }
                break;
        }

        // Atualiza estados anteriores
        button_a_last_state = button_a_current_state;
        button_b_last_state = button_b_current_state;
    }

    return 0;
}
