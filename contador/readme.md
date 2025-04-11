# ⏱️ Projeto: Contador Decrescente com Raspberry Pi Pico + Display OLED 🖥️

Este projeto utiliza a **BitDogLab** e utiliza da placa o **Raspberry Pi Pico**, dois botões físicos (A e B) e um **display OLED I2C (SSD1306)** para criar um contador decrescente interativo! 🔁

---

## 📦 Funcionalidades

✅ Contador decrescente de **9 até 0**  
✅ Botão **A (GPIO 5)**: Inicia ou reinicia a contagem  
✅ Botão **B (GPIO 6)**: Conta quantas vezes foi pressionado **durante a contagem**  
✅ Exibição das informações no **display OLED 128x64**  
✅ Utiliza **interrupções** para resposta rápida aos botões  
✅ Mensagem final com o total de pressões no botão B  
✅ Mensagem inicial no display ao ligar o sistema

---

## 🎮 Como funciona

1. O display mostra uma mensagem inicial.
2. Pressione o botão **A** para iniciar a contagem de 9 até 0.
3. Durante essa contagem:
   - O botão **B** incrementa um contador a cada toque.
   - O botão **A** reinicia a contagem.
4. Ao final, o display mostra:
   - `Contagem: 0`
   - `Total B: <quantidade>`

---

## 🛠️ Hardware necessário

- Raspberry Pi Pico 🧠
- Display OLED I2C (SSD1306) 🖥️
- 2 botões push-button 🔘🔘
- Resistores de pull-up (opcional, mas recomendável)
- Jumpers e protoboard

---

## ⚙️ Conexões

| Componente | GPIO Pico |
|------------|------------|
| Botão A    | 5          |
| Botão B    | 6          |
| SDA (Display) | 14      |
| SCL (Display) | 15      |

---

## 📜 Créditos

Este projeto foi desenvolvido como parte do Programa de Residência **Embarcatech**. Sinta-se livre para explorar, modificar e aprimorar! 🚀

---

👨‍💻 **Desenvolvido por:** Rafael Florentino