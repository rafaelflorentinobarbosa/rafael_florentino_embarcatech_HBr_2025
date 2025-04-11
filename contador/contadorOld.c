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
 #include <stdlib.h>
 #include <math.h>
 #include "pico/stdlib.h"
 #include "pico/binary_info.h"
 #include "inc/ssd1306.h"
 #include "hardware/i2c.h"
 #include "hardware/clocks.h"

const uint BUTTON_A = 5; 
const uint BUTTON_B = 6; 

// Tela OLED
const uint I2C_SDA = 14;
const uint I2C_SCL = 15;

// Função para exibir uma mensagem na tela OLED
void display_message(char *lines[], int num_lines, uint8_t *ssd, struct render_area *frame_area) {
    memset(ssd, 0, ssd1306_buffer_length);
    int y = 0;
    for (int i = 0; i < num_lines; i++) {
        ssd1306_draw_string(ssd, 5, y, lines[i]);
        y += 8;
    }
    render_on_display(ssd, frame_area);
}

// Função para exibir uma mensagem de Inicialização na tela OLED
void show_mensagem_inicial(uint8_t *ssd, struct render_area *frame_area) {

    char *text[] = {
        "     ",
        "     ",
        "    Contador ",
        "     ",
        "  Decrescente ", 
    };
    display_message(text, 5, ssd, frame_area);
}

// Função para mostrar o contador B, quantas vezes foram apertado o botao B, centralizada na tela
void show_contador_b(uint8_t *ssd, int contadorB, struct render_area *frame_area) {
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "Contador b: %d", contadorB);
    ssd1306_draw_string(ssd, 5, 0, buffer);
    render_on_display(ssd, frame_area);
}


void show_contagem_regressiva(uint8_t *ssd, int i, struct render_area *frame_area) {
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "Contagem: %d", i);
    ssd1306_draw_string(ssd, 5, 0, buffer);
    render_on_display(ssd, frame_area);
}


int main()
{
    stdio_init_all();

    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A); // Ativa o resistor de pull-up

    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B); // Ativa o resistor de pull-up

    // ----------- Tela OLED --------------------

    // Inicialização do i2c
    i2c_init(i2c1, ssd1306_i2c_clock * 1000); // Define a velocidade do clock,  frequência desejada (em kHz)
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); // Função de linha de dados serial, bidirecional. 
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); // Função de linha de clock serial. 
    gpio_pull_up(I2C_SDA); // Habilita um resistor de pull-up interno no pino GPIO, linha SDA fique em nível lógico alto quando nenhum dispositivo estiver ativamente a controlando
    gpio_pull_up(I2C_SCL); // Habilita um resistor de pull-up interno no pino GPIO, linha SCL fique em nível lógico alto quando nenhum dispositivo estiver ativamente a controlando

    // Processo de inicialização completo do OLED SSD1306
    ssd1306_init();    

    // Preparar área de renderização para o display (ssd1306_width pixels por ssd1306_n_pages páginas)
    struct render_area frame_area = {
        start_column : 0,
        end_column : ssd1306_width - 1,
        start_page : 0,
        end_page : ssd1306_n_pages - 1
    };

    calculate_render_area_buffer_length(&frame_area);

    // zera o display inteiro
    uint8_t ssd[ssd1306_buffer_length];
    memset(ssd, 0, ssd1306_buffer_length);
    render_on_display(ssd, &frame_area);

    // Limpa o buffer de renderização
    memset(ssd, 0, ssd1306_buffer_length);
    render_on_display(ssd, &frame_area);


    // ----------- Fim Tela OLED --------------------

    // Exiber mensagem de inicialização na tela OLED  1 vez depois sumir
    show_mensagem_inicial(ssd, &frame_area);
    sleep_ms(2000); // Aguarda 2 segundos antes de reiniciar o loop
    // Limpa o buffer de renderização   
    memset(ssd, 0, ssd1306_buffer_length);
    render_on_display(ssd, &frame_area);
    // Limpa o buffer de renderização
    memset(ssd, 0, ssd1306_buffer_length);

    
    while (true) {
        int contadorB=0;

        for (int i = 9; i >= 0; i--) {
            printf("%d\n", i);
            sleep_ms(1000); // Aguarda 1 segundo
            // Mostrar na tela oled o numero da contagem regressiva que se encontra em cada iteração
            
            show_contagem_regressiva(ssd, i, &frame_area);
            
            // Se o botão for pressionado, mensagem botão a precionado
            if (gpio_get(BUTTON_A) == 0) {
                printf("Botão A pressionado!\n");
                i = 9; // Reinicia o contador
            }
            if (gpio_get(BUTTON_B) == 0) {
                printf("Botão B pressionado!\n");
                contadorB++;
            }
        }
        printf("Contagem finalizada!\n");

        // Exibe o contador B na tela OLED
        show_contador_b(ssd, contadorB, &frame_area);

        // Congela o contador e ignora os cliques do botão B
        while (gpio_get(BUTTON_A) == 1) {
            // Aguarda até que o botão A seja pressionado novamente
            sleep_ms(100); // Aguarda 100ms para evitar leitura excessiva
        }
        // Tira da tela o contador B
        memset(ssd, 0, ssd1306_buffer_length);
        render_on_display(ssd, &frame_area);

        // Reinicia o contador e o contador B
        printf("Contador B: %d\n", contadorB);

        sleep_ms(2000); // Aguarda 2 segundos antes de reiniciar o loop
    }
}
