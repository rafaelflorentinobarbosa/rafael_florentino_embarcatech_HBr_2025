/* Tarefa 3
   Faça um programa em C para ler a temperatura interna do RP2040
   Converta a leitura do ADC em um valor em ºC e mostre na tela OLED
*/

//  Inclusão das bibliotecas
#include <stdio.h> // Entrada e saída (como printf)
#include <string.h> // Manipulação de strings (snprintf, memset)
#include "pico/stdlib.h" // Funções básicas da Raspberry Pi Pico (como sleep_ms)
#include "hardware/adc.h" // Manipular ADC (leitura analógica)
#include "hardware/i2c.h" // Comunicação com dispositivos I2C (como o display)
#include "inc/ssd1306.h"  // Biblioteca específica para o display OLED SSD1306

// Definição dos pinos I2C para a tela OLED
const uint I2C_SDA = 14;
const uint I2C_SCL = 15;

// Buffer de vídeo para o display
uint8_t ssd[ssd1306_buffer_length];
// Definição da área da tela que será atualizada. Nesse caso a tela inteira
struct render_area frame_area = {
    .start_column = 0,
    .end_column = ssd1306_width - 1,
    .start_page = 0,
    .end_page = ssd1306_n_pages - 1
};

// Função para configurar o display OLED
void setup_display() {
    i2c_init(i2c1, 400 * 1000); // Inicializa o I2C com 400kHz
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); // Configura os pinos 14 e 15 para função I2C
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); 
    gpio_pull_up(I2C_SDA); // Ativa resistores de pull-up (necessários para I2C)
    gpio_pull_up(I2C_SCL);
    ssd1306_init(); // Inicializa o display OLED.
    calculate_render_area_buffer_length(&frame_area); // Ajusta o tamanho do buffer de acordo com a área definida
    memset(ssd, 0, ssd1306_buffer_length); // Limpa o buffer com zeros
    render_on_display(ssd, &frame_area); // Atualiza a tela com o conteúdo do buffer, neste caso, apagada
}

// Função para exibir a temperatura na tela OLED
void display_temperature(float temp) {
    char linha1[20], linha2[20];
    snprintf(linha1, sizeof(linha1), "Temp. Interna:"); // Monta strings com o texto a exibir
    snprintf(linha2, sizeof(linha2), "%.2f C", temp);

    memset(ssd, 0, ssd1306_buffer_length); // Limpa o buffer
    ssd1306_draw_string(ssd, 5, 0, linha1); // Desenha texto nas coordenadas (x, y)
    ssd1306_draw_string(ssd, 5, 16, linha2);
    render_on_display(ssd, &frame_area); // Envia o conteúdo do buffer para o display
}

int main() {
    stdio_init_all(); // Habilita printf() via USB
    setup_display(); // Inicializa o display OLED
    adc_init(); // Inicializa ADC
    adc_set_temp_sensor_enabled(true); // Habilita sensor de temperatura interno
    adc_select_input(4); // Usa canal 4, que é o sensor interno de temperatura

    while (true) {
        uint16_t raw = adc_read(); // Lê o valor bruto do sensor (de 0 a 4095)

        // Converte o valor lido para temperatura:
        float voltage = raw * 3.3f / 4095.0f; // Converte para tensão (em volts)
        float temperature = 27.0f - (voltage - 0.706f) / 0.001721f; // aplica a fórmula oficial do datasheet

        printf("Temperatura interna: %.2f °C\n", temperature); // Mostra a Temperatura  no terminal
        display_temperature(temperature); // Mostra a Temperatura na tela no OLED

        sleep_ms(1000); // Espera 1 segundo antes de fazer nova leitura
    }
}
