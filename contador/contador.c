/** Tarefa 1
 *  Faça um programa, em linguagem C, que implemente um contador decrescente controlado por interrupção, com o seguinte comportamento:
    Toda vez que o Botão A (GPIO5) for pressionado:
    O contador decrescente reinicia em 9 e o valor da contagem é mostrado no display OLED.
    O sistema entra em modo de contagem regressiva ativa, decrementando o contador de 1 em 1 a cada segundo até chegar em zero.
    Durante essa contagem (ou seja, de 9 até 0), o programa deve registrar quantas vezes o Botão B (GPIO6) foi pressionado. O valor deste registro de eventos de botão pressionado também deve ser mostrado no display OLED.
    Quando o contador atingir zero, o sistema congela e ignora temporariamente os cliques no Botão B (eles não devem ser acumulados fora do intervalo ativo).
    O sistema permanece parado após a contagem, exibindo:
    O valor 0 no contador
    A quantidade final de cliques no Botão B registrados durante o período de 9 segundo (contagem regressiva)
    Somente ao pressionar novamente o Botão A, o processo todo se reinicia:
    O contador volta para 9
    O número de cliques do Botão B é zerado
    A contagem recomeça do início
 */
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "inc/ssd1306.h"

// Definições de pinos
const uint BUTTON_A = 5;
const uint BUTTON_B = 6;

const uint I2C_SDA = 14;
const uint I2C_SCL = 15;

// Definições do display, contadores e variáveis
volatile bool iniciar_contagem = false;
volatile int contadorB = 0;
volatile bool contando = false;

// Definições do display OLED, largura e altura, número de páginas e tamanho do buffer. 
uint8_t ssd[ssd1306_buffer_length]; // ssd = buffer da tela, frame_area = tela toda
struct render_area frame_area = {
    .start_column = 0,
    .end_column = ssd1306_width - 1,
    .start_page = 0,
    .end_page = ssd1306_n_pages - 1
};

// Callback de interrupção, função é chamada quando um botão é pressionado, A ou B
void gpio_callback(uint gpio, uint32_t events) {
    if (gpio == BUTTON_A && (events & GPIO_IRQ_EDGE_FALL)) { // Verifica se foi uma borda de descida (botão pressionado)
        iniciar_contagem = true;
    }
    if (gpio == BUTTON_B && (events & GPIO_IRQ_EDGE_FALL) && contando) {
        contadorB++; // Só aumenta se contando == true (ou seja, estamos entre 9 e 0).
    }
}

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


// Função principal
// Inicializa o display, os botões e as interrupções. O loop principal aguarda a contagem ser iniciada pelo botão A.
int main() {
    stdio_init_all(); // Inicializa o USB (para printf)
    setup_display(); // Inicializa o display OLED

    display_message("    Contador", "  Aperte A "); // Mostra mensagem inicial no display

    gpio_init(BUTTON_A); // Inicializa o botão A
    gpio_set_dir(BUTTON_A, GPIO_IN); // Define o pino como entrada
    gpio_pull_up(BUTTON_A); // Habilita o resistor de pull-up interno, em nível lógico alto quando nenhum dispositivo estiver ativamente a controlando

    gpio_init(BUTTON_B); 
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);

    // Interrupções, a função gpio_callback() será chamada automaticamente quando os botões forem pressionados.
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_callback); // Ativa a interrupção e já define a função de callback
    gpio_set_irq_enabled(BUTTON_B, GPIO_IRQ_EDGE_FALL, true); // Ativa a interrupção, mas não define a função de callback (ela já foi definida acima)

    // Loop principal
    while (true) { // O sistema fica parado esperando iniciar_contagem == true, quando você pressiona o botão A, a interrupção ativa isso.
        if (iniciar_contagem) {
            iniciar_contagem = false;
            contadorB = 0;
            contando = true;

            // Inicia contagem de 9 até 0
            // Lembrando que o botão A e B estão sendo monitorados pelas interrupções.
            for (int i = 9; i >= 0; i--) {
                char linha1[20], linha2[20];
                snprintf(linha1, sizeof(linha1), "Contagem: %d", i); // Mostra contagem regressiva
                snprintf(linha2, sizeof(linha2), "B: %d", contadorB); // Mostra contador B, botão B pressionado
                display_message(linha1, linha2); // Atualiza display com contagem e contador B pressionado
                sleep_ms(1000); // Espera 1 segundo

                // Permite reiniciar durante a contagem, se o botão A for pressionado.
                if (iniciar_contagem) {
                    iniciar_contagem = false;
                    contadorB = 0;
                    i = 10; // volta para 9 na próxima iteração
                }
            }

            contando = false; // Congela contagem, não aceita mais cliques no botão B.

            // Mostra resultado final
            char final1[] = "Contagem: 0"; // Guarda contagem final, chegou a 0
            char final2[20]; // Guarda valor do contador B
            snprintf(final2, sizeof(final2), "Total B: %d", contadorB); // Mostra contador B, vezes que botão B pressionado
            display_message(final1, final2); // Atualiza display com contagem, e atualiza as vezes que botão B pressionado

            // Espera botão A para reiniciar
            // Fica aqui esperando algum evento externo mudar a variável
            while (!iniciar_contagem) {
                tight_loop_contents(); // Espera o botão A ser pressionado, não faz nada.
            }
        }

        sleep_ms(50);
    }
}
