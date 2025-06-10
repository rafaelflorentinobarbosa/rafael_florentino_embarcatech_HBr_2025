#include "include/buttons.h"

void buttons_init(){
    // Inicializando os botões A e B
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);

    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);
}

void check_buttons(){
    if (!gpio_get(BUTTON_A)) {  // Botão A pressionado Gravar/Parar
        printf("Botao A\n"); // Adicione '\n' para nova linha, facilita a visualização
        sleep_ms(200); // Atraso de 200ms para debounce
    }
    if (!gpio_get(BUTTON_B)) {  // Botão B pressionado Reproduzir
        printf("Botao B\n"); // Adicione '\n'
        sleep_ms(200); // Atraso de 200ms para debounce
    }
}