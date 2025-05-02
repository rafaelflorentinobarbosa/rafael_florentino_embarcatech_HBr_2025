
#include <stdio.h> // Entrada e saída (como printf)
#include <string.h> // Manipulação de strings (snprintf, memset).
#include "pico/stdlib.h" // Funções básicas da Raspberry Pi Pico (como sleep_ms)
#include "hardware/adc.h" // Manipular ADC (leitura analógica)
#include "hardware/i2c.h" // Comunicação com dispositivos I2C (como o display)
#include "drivers/ssd1306.h"  // Biblioteca específica para o display OLED SSD1306
#include "include/adc_temp.h" // Função para converter ADC em temperatura
#include "include/rp2040.h"

int main() {

    stdio_init_all();
    sensor_temperatura_init(); 

    float temperature;

    while (true) {

        temperature = hal_temperature_read(); // Lê a temperatura
        printf("Temperatura: %.2f °C\n", temperature); // Imprime a temperatura no console
        sleep_ms(1000);
    }

    return 0;
}