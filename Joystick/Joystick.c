/*  Tarefa 2
Faça um programa em C para ler os valores convertidos digitalmente do joystick da BitDogLab. 
Os valores podem ser mostrados no terminal ou então no display OLED. */

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "inc/ssd1306.h"

// Definição dos Pinos para tela OLED
const uint I2C_SDA = 14;
const uint I2C_SCL = 15;

// Definição dos pinos usados para o joystick e LEDs
const int VRX = 26;          // Pino de leitura do eixo X do joystick (conectado ao ADC)
const int VRY = 27;          // Pino de leitura do eixo Y do joystick (conectado ao ADC)
const int ADC_CHANNEL_0 = 0; // Canal ADC para o eixo X do joystick
const int ADC_CHANNEL_1 = 1; // Canal ADC para o eixo Y do joystick
const int SW = 22;           // Pino de leitura do botão do joystick

// Função para configurar o joystick (pinos de leitura e ADC)
void setup_joystick(){
  // Inicializa o ADC e os pinos de entrada analógica
  adc_init();         // Inicializa o módulo ADC
  adc_gpio_init(VRX); // Configura o pino VRX (eixo X) para entrada ADC
  adc_gpio_init(VRY); // Configura o pino VRY (eixo Y) para entrada ADC

  // Inicializa o pino do botão do joystick
  gpio_init(SW);             // Inicializa o pino do botão
  gpio_set_dir(SW, GPIO_IN); // Configura o pino do botão como entrada
  gpio_pull_up(SW);          // Ativa o pull-up no pino do botão para evitar flutuações
}

// Definições do display OLED, largura e altura, número de páginas e tamanho do buffer. 
uint8_t ssd[ssd1306_buffer_length]; // ssd = buffer da tela, frame_area = tela toda
struct render_area frame_area = {
    .start_column = 0,
    .end_column = ssd1306_width - 1,
    .start_page = 0,
    .end_page = ssd1306_n_pages - 1
};

// Função para renderizar o buffer na tela
void display_message(const char *line1, const char *line2) {
    memset(ssd, 0, ssd1306_buffer_length); // Limpa o buffer
    ssd1306_draw_string(ssd, 5, 0, line1); // Escreve linha 1
    ssd1306_draw_string(ssd, 5, 16, line2); // Escreve linha 2
    render_on_display(ssd, &frame_area);  // Mostra na tela
}

// Função para configurar o display OLED.
void setup_display() {

    // Inicialização do i2c
    i2c_init(i2c1, 400 * 1000); // Define a velocidade do clock, frequência desejada (em kHz)
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); // Função de linha de dados serial, bidirecional. 
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); // Função de linha de clock serial. 
    gpio_pull_up(I2C_SDA); // Habilita um resistor de pull-up interno no pino GPIO, linha SDA fique em nível lógico alto quando nenhum dispositivo estiver ativamente a controlando
    gpio_pull_up(I2C_SCL); // Habilita um resistor de pull-up interno no pino GPIO, linha SCL fique em nível lógico alto quando nenhum dispositivo estiver ativamente a controlando
    ssd1306_init(); // Inicializa o display OLED
    calculate_render_area_buffer_length(&frame_area); // Calcula o tamanho do buffer de renderização
    memset(ssd, 0, ssd1306_buffer_length); // Limpa o buffer
    render_on_display(ssd, &frame_area); // Mostra na tela
}

// Função de configuração geral
void setup(){
  stdio_init_all();  // Inicializa a porta serial para saída de dados
  setup_joystick();  // Chama a função de configuração do joystick
}

// Função para ler os valores dos eixos do joystick (X e Y)
void joystick_read_axis(uint16_t *vrx_value, uint16_t *vry_value){
  // Leitura do valor do eixo X do joystick
  adc_select_input(ADC_CHANNEL_0); // Seleciona o canal ADC para o eixo X
  sleep_us(2);  // Pequeno delay para estabilidade
  *vrx_value = adc_read(); // Lê o valor do eixo X (0-4095)

  // Leitura do valor do eixo Y do joystick
  adc_select_input(ADC_CHANNEL_1); // Seleciona o canal ADC para o eixo Y
  sleep_us(2); // Pequeno delay para estabilidade
  *vry_value = adc_read(); // Lê o valor do eixo Y (0-4095)
}

int main() {
    uint16_t vrx_value, vry_value; // Variáveis para armazenar os valores dos eixos
    char linha1[20]; // Buffer para a primeira linha do display
    char linha2[20]; // Buffer para a segunda linha do display

    setup();           // Inicializa joystick e serial
    setup_display();   // Inicializa a tela OLED

    printf("Joystick - Leitura dos eixos X e Y\n");

    while (1) {
        joystick_read_axis(&vrx_value, &vry_value); // Lê os eixos X e Y
        bool sw_pressed = !gpio_get(SW); // Lê o botão (ativo em nível baixo)

        // Mostra no terminal (opcional)
        printf("Eixo X: %d\tEixo Y: %d\tBotão: %s\n", vrx_value, vry_value, sw_pressed ? "Pressionado" : "Solto");

        // Formata as strings para o display OLED
        sprintf(linha1, "X: %d  Y: %d", vrx_value, vry_value);
        sprintf(linha2, "Botao: %s", sw_pressed ? "Press" : "Solto");

        // Atualiza o display
        display_message(linha1, linha2);

        sleep_ms(200); // Delay entre leituras
    }
}