# 🌡️ Projeto: Leitura de Temperatura Interna no RP2040 com Display OLED 🖥️

Este projeto em C foi desenvolvido para o Raspberry Pi Pico (RP2040) com o objetivo de ler a **temperatura interna** do microcontrolador e exibi-la em um **display OLED** via I2C. Ideal para aprendizado de sensores internos, ADCs e comunicação I2C com periféricos visuais! 🚀

## 🔧 Funcionalidades

- ✅ Leitura do sensor de temperatura interno do RP2040
- 🔁 Conversão da leitura do ADC para °C
- 🖼️ Exibição da temperatura em tempo real no display OLED SSD1306
- 💬 Também imprime no terminal serial

## 📷 Demonstração

```bash
    TEMP INTERNA
    27 32 C
```

## 🧰 Componentes Utilizados

- Raspberry Pi Pico 🧠
- Display OLED 0.96" I2C (SSD1306) 🖥️
- Jumpers 🔌

## 📝 Código-fonte

### Trecho principal da conversão da temperatura:
```c
adc_set_temp_sensor_enabled(true); // Habilita o sensor de temperatura interno
adc_select_input(4); // Usa o canal 4 (sensor interno)

uint16_t raw = adc_read();
float voltage = raw * 3.3f / 4095.0f;
float temperature = 27.0f - (voltage - 0.706f) / 0.001721f;
```
---

## 📜 Créditos

Este projeto foi desenvolvido como parte do Programa de Residência **Embarcatech**. Sinta-se livre para explorar, modificar e aprimorar! 🚀

---

## 👨‍💻 **Desenvolvido por:** Rafael Florentino