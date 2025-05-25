// Nome do arquivo: iot_security_lab.c
// Bibliotecas necessárias
#include <string.h>         // Para funções de string como strlen()
#include "pico/stdlib.h"      // Biblioteca padrão do Pico (GPIO, tempo, etc.)
#include "pico/cyw43_arch.h"    // Driver WiFi para Pico W
#include "include/wifi_conn.h"   // Funções personalizadas de conexão WiFi
#include "include/mqtt_comm.h"   // Funções personalizadas para MQTT
#include "include/xor_cipher.h"   // Funções de cifra XOR
#include <time.h>                   // Para time(NULL) e timestamp

int main() {
  // Inicializa todas as interfaces de I/O padrão (USB serial, etc.)
  stdio_init_all();

  // Conecta à rede WiFi
  // Parâmetros: Nome da rede (SSID) e senha
  // !!! SUBSTITUA "SSID da rede" e "Senha da rede" pelos seus dados reais !!!
  connect_to_wifi("SSID da rede", "Senha da rede"); 

  // Configura o cliente MQTT
  // Parâmetros: ID do cliente, IP do broker, usuário, senha
  // !!! SUBSTITUA "IP do broker" pelo IP do seu broker MQTT !!!
  mqtt_setup("bitdog1", "IP do broker", "aluno", "senha123");

  // Buffer para a mensagem formatada com timestamp
  char buffer[64]; // Aumente o tamanho se suas mensagens forem maiores

  // Mensagem original a ser enviada
  const char *mensagem_valor = "26.5"; // Manter para fins de criptografia XOR se ativado

  // Buffer para mensagem criptografada (16 bytes)
  uint8_t criptografada[16];
  // Criptografa a mensagem usando XOR com chave 42
  // Observe que a criptografia XOR aqui é sobre o valor "26.5",
  // mas a publicação abaixo usará a string JSON com timestamp.
  // Você precisaria aplicar XOR ao JSON completo se quisesse criptografar a mensagem inteira.
  xor_encrypt((uint8_t *)mensagem_valor, criptografada, strlen(mensagem_valor), 42);

  // Loop principal do programa
  while (true) {
    // Obtém o timestamp atual
    unsigned long current_timestamp = time(NULL);

    // Formata a mensagem com o valor e o timestamp no formato JSON
    // O `%.1f` para o valor pode ser ajustado conforme a precisão necessária.
        // O `26.5` abaixo é hardcoded para demonstração. Em um cenário real, você leria de um sensor.
    sprintf(buffer, "{\"valor\":26.5,\"ts\":%lu}", current_timestamp);

    // Publica a mensagem formatada (JSON com timestamp)
    mqtt_comm_publish("escola/sala1/temperatura", (const uint8_t *)buffer, strlen(buffer));

    // Alternativa: Publica a mensagem criptografada (atualmente comentada)
    // Se você quiser criptografar a mensagem JSON completa, você precisaria aplicar
    // xor_encrypt ao buffer após sprintf e ajustar o tamanho do buffer criptografado.
    // mqtt_comm_publish("escola/sala1/temperatura", criptografada, strlen(buffer));

    // Aguarda 5 segundos antes da próxima publicação
    sleep_ms(5000);
  }
  return 0;
}

/*
* Comandos de terminal para testar o MQTT:
*
* Inicia o broker MQTT com logs detalhados:
* .\mosquitto -c mosquitto.conf -v
*
* Publica mensagem de teste no tópico de temperatura: em outro terminal
* .\mosquitto_pub -h localhost -p 1883 -t "escola/sala1/temperatura" -u "aluno" -P "senha123" -m "{\"valor\":26.6,\"ts\":1678886400}"
* Assina o tópico de temperatura (recebe mensagens): no primeiro terminal
* .\mosquitto_sub -h localhost -p 1883 -t "escola/sala1/temperatura" -u "aluno" -P "senha123"
*
*/