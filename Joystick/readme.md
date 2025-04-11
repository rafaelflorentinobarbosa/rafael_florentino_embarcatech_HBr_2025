# 🎮 Projeto Joystick + OLED com Raspberry Pi Pico

Este projeto em C utiliza o joystick da **BitDogLab** conectado ao **Raspberry Pi Pico**, lendo os valores dos eixos X e Y, além do botão, e exibindo essas informações diretamente no display **OLED SSD1306** via I2C. 📟

---

## 🔧 Componentes Utilizados

- 🧠 **Raspberry Pi Pico**
- 🎮 **Joystick Analógico BitDogLab**
- 📟 **Display OLED SSD1306 (I2C)**
- 🔌 Cabos jumpers
- 💻 Software baseado no **Pico SDK (C/C++)**

---

## 📷 Visão Geral

- Leitura dos valores **analógicos** dos eixos X e Y via **ADC** (0–4095).
- Leitura do **botão do joystick** com pull-up interno.
- Exibição das informações no terminal **e** na tela **OLED** ao mesmo tempo.
  
### 🖼 Exemplo na tela:

```bash
    X: 2048 Y: 1987
    Botao: Solto
```


## 📁 Estrutura do Código

### 🗂 Arquivos principais:

| Arquivo        | Descrição                              |
|----------------|----------------------------------------|
| `main.c`       | Lógica principal do programa           |
| `ssd1306.h`    | Biblioteca para controle da tela OLED  |
| `CMakeLists.txt` | Configuração do build com o Pico SDK |

---

### 🧠 Aprendizados
- Utilização de ADC com o Pico.

- Comunicação I2C com SSD1306.

- Uso de buffer para desenhar texto no display.

- Lógica condicional para detectar o botão do joystick.

---

### 📌 Observações
- O display deve estar conectado nos pinos:

- SDA: GPIO14

- SCL: GPIO15

- A alimentação dos componentes deve estar correta: 3.3V para o OLED e joystick.

---

### 💡 Futuras Melhorias
- Mostrar gráficos de movimento do joystick.

- Adicionar barra de força nos eixos.

- Animações no OLED com base nos movimentos.

---

## 📜 Créditos

Este projeto foi desenvolvido como parte do Programa de Residência **Embarcatech**. Sinta-se livre para explorar, modificar e aprimorar! 🚀

---

### 👨‍💻 Autor
- 🧑‍💻 **Desenvolvido por:** Rafael Florentino
- 📘 Estudante de Engenharia de Software 
- 🛠 Desenvolvedor entusiasta em projetos com Raspberry Pi e IoT 🚀

