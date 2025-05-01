
# 💡 Projeto: Piscar LED com Arquitetura Modular (Raspberry Pi Pico W)

Este projeto demonstra como **estruturar um código em C** para a Raspberry Pi Pico W de forma modular, seguindo uma arquitetura limpa e organizada, separando responsabilidades em **driver**, **HAL** (Hardware Abstraction Layer) e **aplicação**.

---

## 📁 Estrutura do Projeto

```
projeto/
├── app/
│   └── main.c                # Lógica principal da aplicação
├── drivers/
│   └── led_embutido.c        # Código de acesso direto ao hardware
├── hal/
│   └── hal_led.c             # Camada de abstração do hardware
├── include/
│   ├── led_embutido.h        # Header do driver
│   └── hal_led.h             # Header da HAL
├── CMakeLists.txt            # Arquivo de build do projeto
```

---

## 🎯 Objetivos

✅ Criar uma arquitetura modular para facilitar manutenção e reutilização  
✅ Separar responsabilidades entre controle de hardware, abstração e aplicação  
✅ Usar boas práticas de organização com o SDK da Raspberry Pi Pico  

---

## ⚙️ Como Funciona

- A **aplicação (`main.c`)** chama `hal_led_toggle()` a cada 500ms.
- A **HAL (`hal_led.c`)** alterna o estado do LED, usando a função `led_embutido_set()` do driver.
- O **driver (`led_embutido.c`)** controla diretamente o LED usando `cyw43_arch_gpio_put()`.

---

## 🛠️ Como Compilar

1. Clone ou baixe este projeto:
   ```bash
   git clone https://github.com/rafaelflorentinobarbosa/rafael_florentino_embarcatech_HBr_2025/tree/main/arquitetura_modular_led
   ```

2. Configure o SDK da Raspberry Pi Pico.

3. Compile o projeto:

## 🧠 Conceitos Envolvidos

📌 **Arquitetura modular**  
📌 **HAL (Hardware Abstraction Layer)**  
📌 **Drivers de hardware**  
📌 **Build com CMake**  
📌 **Programação embarcada com Raspberry Pi Pico W**  

---

## 🚀 Resultado

O LED embutido da Raspberry Pi Pico W pisca a cada 500ms, utilizando um design de software limpo e modular. 🔁✨

---

## 🧑‍💻 Autor

**Rafael Florentino**  
Estudante de Engenharia de Software e entusiasta de sistemas embarcados e IoT. 👨‍🔧📡

---

## 📄 Licença

Este projeto está sob a licença MIT. Sinta-se livre para usar e modificar!
