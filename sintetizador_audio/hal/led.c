#include "include/led.h"
#include "hardware/gpio.h" // Inclui a biblioteca de GPIOs para o arquivo de implementação

void led_init(){
    // Inicializa cada pino como uma saída GPIO
    gpio_init(LED_PIN_AZUL);
    gpio_set_dir(LED_PIN_AZUL, GPIO_OUT);

    gpio_init(LED_PIN_VERDE);
    gpio_set_dir(LED_PIN_VERDE, GPIO_OUT);

    gpio_init(LED_PIN_VERMELHO);
    gpio_set_dir(LED_PIN_VERMELHO, GPIO_OUT);

    // Garante que todos os LEDs estão desligados na inicialização
    turn_off_led();
}

void turn_off_led(){
    gpio_put(LED_PIN_AZUL, 0);    // Define o pino AZUL para LOW (desliga)
    gpio_put(LED_PIN_VERDE, 0);   // Define o pino VERDE para LOW (desliga)
    gpio_put(LED_PIN_VERMELHO, 0); // Define o pino VERMELHO para LOW (desliga)
}

void turn_on_blue(){
    turn_off_led(); // Desliga todos os outros LEDs primeiro
    gpio_put(LED_PIN_AZUL, 1); // Define o pino AZUL para HIGH (liga)
}

void turn_on_green(){
    turn_off_led(); // Desliga todos os outros LEDs primeiro
    gpio_put(LED_PIN_VERDE, 1); // Define o pino VERDE para HIGH (liga)
}

void turn_on_red(){
    turn_off_led(); // Desliga todos os outros LEDs primeiro
    gpio_put(LED_PIN_VERMELHO, 1); // Define o pino VERMELHO para HIGH (liga)
}