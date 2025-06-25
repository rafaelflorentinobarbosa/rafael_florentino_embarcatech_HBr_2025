#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "pico/stdlib.h"

// Includes dos drivers
#include "include/led.h"
#include "include/buttons.h"
#include "include/buzzers.h"
#include "include/display.h"
#include "include/joystick.h"
#include "include/microphone.h"

// Estados globais
static int led_color = -1;
static bool alarm_active = false;
static bool sound_detected = false;
static uint16_t joystick_value = 0;

// ========================
// Atualiza Display
void update_display() {
    char line1[20];
    char line2[20];
    char line3[20];
    char line4[20];

    const char* led_color_str = (led_color == -1) ? "Desligado" :
                                (led_color == 0) ? "Azul" :
                                (led_color == 1) ? "Verde" : "Vermelho";

    sprintf(line1, "LED: %s", led_color_str);
    sprintf(line2, "Som: %s", sound_detected ? "Detectado" : "Nao");
    sprintf(line3, "Joystick: %d", joystick_value);
    sprintf(line4, "Alarme: %s", alarm_active ? "Ativo" : "Inativo");

    screem_message_4lines(line1, line2, line3, line4);
}

// Task: LED
void task_led(void *pvParameters) {
    while (true) {
        if (button_a_pressed()) {
            if (led_color == 2) {
                led_color = -1;
            } else {
                led_color++;
            }
            set_led_color(led_color);
        }
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

// Task: Buzzer
void task_buzzer(void *pvParameters) {
    static uint32_t freq = 1000;
    static bool going_up = true;

    while (true) {
        if (button_b_pressed()) {
            alarm_active = !alarm_active;
        }

        if (alarm_active) {
            buzzer_play_tone(freq, 50);  // Tom atual

            // Ajusta frequência para simular sirene
            if (going_up) {
                freq += 50;
                if (freq >= 2000) going_up = false;
            } else {
                freq -= 50;
                if (freq <= 1000) going_up = true;
            }
        } else {
            buzzer_stop();
            freq = 1000;
            going_up = true;
        }

        vTaskDelay(pdMS_TO_TICKS(30));
    }
}

// Task: Microfone
void task_microphone(void *pvParameters) {
    while (true) {
        bool new_sound = microphone_detect_sound();
        sound_detected = new_sound;
        vTaskDelay(pdMS_TO_TICKS(300));
    }
}

// Task: Display
void task_display(void *pvParameters) {
    while (true) {
        uint16_t joy_x, joy_y;
        joystick_read(&joy_x, &joy_y);
        joystick_value = joy_x;

        update_display();

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

// MAIN
int main() {
    stdio_init_all();

    buttons_init();
    buzzers_init();
    screem_init();
    joystick_init();
    microphone_init();
    led_rgb_init();

    set_led_color(-1);
    update_display();

    xTaskCreate(task_led, "LED", 256, NULL, 1, NULL);
    xTaskCreate(task_buzzer, "BUZZER", 512, NULL, 1, NULL);
    xTaskCreate(task_microphone, "MIC", 256, NULL, 1, NULL);
    xTaskCreate(task_display, "DISPLAY", 512, NULL, 1, NULL);

    vTaskStartScheduler();

    while (1);
}