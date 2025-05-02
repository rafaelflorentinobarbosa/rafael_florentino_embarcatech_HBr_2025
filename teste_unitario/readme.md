# 🌡️ Projeto: Teste unitário para Leitura de Temperatura Interna no RP2040 

Este projeto em C foi desenvolvido para o Raspberry Pi Pico (RP2040) com o objetivo de realizar teste unitário para verificação da conversão de valores ADC para temperatura em Celsius usando o framework Unit

## 🔧 Funcionalidades

- ✅ Leitura do sensor de temperatura interno do RP2040
- 🔁 Conversão da leitura para °C
- 🖼️ Exibição da temperatura no terminal
- 💬 Uso da biblioteca Unity para o teste unitário

## 📷 Demonstração Executando o teste no terminal

```bash
    cd .\test\

    gcc test_adc_temp.c unity/unity.c -o test_adc_temp.exe

    ./test_adc_temp.exe
```
## 📜 Créditos

Este projeto foi desenvolvido como parte do Programa de Residência **Embarcatech**. Sinta-se livre para explorar, modificar e aprimorar! 🚀

---

## 👨‍💻 **Desenvolvido por:** Rafael Florentino