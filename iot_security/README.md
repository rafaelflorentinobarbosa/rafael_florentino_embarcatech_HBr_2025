
# Tarefa: IoT Security Lab - EmbarcaTech 2025

Autor: **Rafael Florentino Barbosa*

Curso: Residência Tecnológica em Sistemas Embarcados

Instituição: EmbarcaTech - HBr

Brasilia, maio de 2025

---

<!-- INSIRA O CONTEÚDO DO SEU README AQUI! -->

---

## 📜 Licença
GNU GPL-3.0.


# 🚀 Projeto de Segurança IoT com BitDogLab e Raspberry Pi Pico W 🔒

Este documento detalha a autenticação, criptografia e proteção contra ataques em comunicação MQTT em um sistema IoT usando a placa BitDogLab com Raspberry Pi Pico W, além de analisar a escalabilidade das técnicas em um cenário de rede.

---

## 🎯 Etapa Final: Relato e Análise

Nesta fase, demonstramos a execução das camadas de segurança adicionadas e discutimos a viabilidade de aplicar essas técnicas em uma rede maior.

---

### 1. 🧪 Demonstração da Execução das Etapas

Para reproduzir e observar o funcionamento do projeto, siga os passos abaixo:

#### a) Pré-requisitos 🛠️
* **Placa BitDogLab com Raspberry Pi Pico W:** Já configurada e pronta para uso.
* **Cabo USB:** Para alimentação e comunicação serial com o Pico W.
* **Computador com Terminal Serial:** Use ferramentas como PuTTY, Screen ou Thonny para visualizar os logs do Pico W.
* **Broker MQTT (Mosquitto):** Instalado e configurado em um PC ou servidor na mesma rede que o Pico W.
* **Cliente MQTT para Subscriber:** Pode ser `mosquitto_sub` (terminal) ou um script Python.

#### b) Configuração do Código (Pico W - Publisher) ⚙️
1.  Abra o arquivo `iot_security_lab.c` no seu ambiente de desenvolvimento.
2.  **Atualize** o `SSID` e a `Senha` da sua rede Wi-Fi.
3.  **Insira** o `IP do broker` MQTT onde seu Mosquitto está rodando.
4.  Certifique-se de que a linha de publicação com o timestamp esteja **descomentada**:
    ```c
    mqtt_comm_publish("escola/sala1/temperatura", (const uint8_t *)buffer, strlen(buffer));
    ```
5.  Compile e faça o upload do firmware para o seu Raspberry Pi Pico W.

#### c) Configuração do Broker MQTT (Mosquitto) 🌐
1.  Garanta que o Mosquitto esteja em execução e configurado com as credenciais (`aluno`/`senha123`) que você usou no código do Pico W.
2.  Inicie o broker (se necessário) com logs detalhados:
    ```bash
    # No Windows
    .\mosquitto -c mosquitto.conf -v
    # No Linux/macOS
    mosquitto -c mosquitto.conf -v
    ```

#### d) Configuração do Subscriber (Cliente MQTT) 📥
1.  Em um novo terminal, inicie o cliente subscriber. Para o teste inicial e visualizar a mensagem JSON, use `mosquitto_sub`:
    ```bash
    .\mosquitto_sub -h localhost -p 1883 -t "escola/sala1/temperatura" -u "aluno" -P "senha123"
    ```
    *(Se seu subscriber não estiver no mesmo computador do broker, substitua `localhost` pelo IP real do broker).*

#### e) Execução e Observação 🧐
1.  Ligue seu Raspberry Pi Pico W.
2.  No terminal serial conectado ao Pico W, observe as mensagens de conexão Wi-Fi e MQTT, além das confirmações de publicação.
3.  No terminal do subscriber, você verá as mensagens JSON com os timestamps.
4.  **Para demonstrar o replay:** Tente publicar uma mensagem manualmente usando `mosquitto_pub` com um timestamp **anterior** ou **igual** ao último timestamp válido que seu subscriber recebeu.
    ```bash
    # Exemplo: Substitua o timestamp para ser menor ou igual ao último recebido
    .\mosquitto_pub -h localhost -p 1883 -t "escola/sala1/temperatura" -u "aluno" -P "senha123" -m "{\"valor\":26.7,\"ts\":1678886400}"
    ```
    Você deverá ver a mensagem "REPLAY DETECTADO ou mensagem antiga" no seu subscriber. ✅

---

### 2. 📈 Discussão: Escalabilidade das Técnicas

Vamos analisar como as técnicas implementadas se comportam em um ambiente maior, como uma rede escolar.

#### a) Quais técnicas são escaláveis? 🤔

1.  **Conectividade Wi-Fi e MQTT:**
    * **Escalável:** 🎉 O **MQTT** é um protocolo incrivelmente escalável para IoT, podendo gerenciar milhares (ou milhões, com infraestrutura robusta) de clientes. O modelo *publish/subscribe* (publicação/assinatura) é flexível e permite adicionar novos dispositivos e aplicações sem impactar os existentes. O Wi-Fi é a base, amplamente disponível em escolas.
    * **Limitações:** O Wi-Fi pode ser um gargalo em ambientes com muitos dispositivos densamente localizados, pois eles competem pelo mesmo espectro de rádio e pontos de acesso. O número de conexões por AP também é limitado.

2.  **Criptografia (Ofuscação) XOR (como implementado):**
    * **Não Escalável para Segurança Real:** 👎 Apesar de ser simples e de baixo consumo de recursos para microcontroladores, a cifra **XOR NÃO é uma técnica de segurança criptográfica robusta ou escalável** para dados sensíveis. É muito vulnerável a ataques e não oferece autenticação, integridade ou sigilo forte. Use-a apenas para ofuscação **básica** e propósitos didáticos.

3.  **Proteção contra Replay (com Timestamp):**
    * **Escalável (com ressalvas):** ✅ A adição de timestamps é eficaz e o *overhead* é mínimo (apenas um campo extra no JSON).
    * **Ressalvas:**
        * **Sincronização de Tempo:** ⏳ A grande dependência da sincronização de tempo precisa entre todos os dispositivos (publishers e subscribers) é o maior desafio. Em uma escola com centenas de dispositivos, garantir que todos os Pico W tenham o horário exato (via NTP, por exemplo) é um desafio de infraestrutura e gerenciamento.
        * **Desvio de Relógio (Clock Drift):** Mesmo com NTP, pequenos desvios podem ocorrer. Pode ser necessário adicionar uma pequena margem de tolerância no subscriber, o que reduz ligeiramente a proteção contra replays muito rápidos.
        * **Ataques Avançados:** Um atacante sofisticado pode burlar isso se conseguir manipular o relógio do dispositivo ou se não houver autenticação e integridade mais fortes da mensagem.

---

#### b) Como aplicá-las com várias BitDogLab em rede escolar? 🏫

Para escalar o projeto em uma rede escolar com múltiplas BitDogLabs, considere:

1.  **Infraestrutura de Rede Wi-Fi Robusta:**
    * **Planejamento:** Garanta uma cobertura Wi-Fi forte e pontos de acesso suficientes em todas as áreas onde as BitDogLabs serão instaladas.
    * **Segmentação de Rede (VLANs):** Isole o tráfego dos dispositivos IoT em VLANs separadas para aumentar a segurança e o desempenho.
    * **SSID Dedicado:** Crie um SSID Wi-Fi exclusivo para os dispositivos IoT, separado da rede de alunos/professores.

2.  **Broker MQTT Centralizado e Seguro:**
    * Use um **único broker MQTT centralizado** (ou um cluster para alta disponibilidade) para gerenciar todas as BitDogLabs.
    * **Segurança do Broker:** Configure o broker com **TLS/SSL** para criptografia do tráfego e autenticação de clientes (usuário/senha forte ou, idealmente, certificados digitais).
    * **Controle de Acesso (ACLs):** Utilize as ACLs do Mosquitto para definir quais tópicos cada BitDogLab pode publicar ou assinar, seguindo o **princípio do menor privilégio**. Exemplo: um sensor da sala 1 só publica no tópico da sala 1.

3.  **Abordagem de Segurança para Dados:**
    * **Para dados sensíveis:** A cifra XOR é inadequada. Invista em **criptografia forte (TLS/SSL no MQTT)** e autenticação baseada em certificados, que exigem mais recursos e configuração, mas são essenciais para dados confidenciais.
    * **Para dados não sensíveis (temperatura):** A ofuscação XOR pode ser usada para demonstração, mas a segurança da camada de transporte (TLS no MQTT) é mais importante na prática. A proteção contra replay com timestamp ainda é valiosa.

4.  **Gerenciamento de Timestamps e Replay:**
    * **Sincronização NTP:** Implemente um **cliente NTP em cada Raspberry Pi Pico W**. Isso requer que o Pico W tenha acesso a um servidor NTP (pode ser um servidor NTP local na rede escolar).
    * **Tolerância ao Desvio:** No subscriber, adicione uma pequena margem de tolerância (ex: +/- 5 segundos) para os timestamps, a fim de compensar pequenos desvios de relógio.
    * **Centralização da Lógica:** A lógica de verificação de replay deve estar em um ou poucos subscribers confiáveis (ex: um servidor central da escola), não replicada em cada aplicação de visualização.

5.  **Provisionamento e Gerenciamento de Dispositivos:**
    * **Identificação Única:** Cada BitDogLab deve ter um **Client ID MQTT único**.
    * **Gerenciamento de Credenciais:** Tenha um sistema para gerenciar as credenciais MQTT de forma segura e fácil de atualizar em massa.
    * **Atualizações Over-the-Air (OTA):** A capacidade de atualizar o firmware das BitDogLabs remotamente (OTA) é crucial para aplicar patches de segurança e novas funcionalidades sem acesso físico a cada placa. (Embora complexo no Pico W, é uma consideração importante para escalabilidade).

6.  **Estrutura de Tópicos MQTT Organizada:**
    * Use uma estrutura de tópicos hierárquica e bem definida para facilitar a gestão e o controle de acesso:
        * `escola/sala1/temperatura`
        * `escola/sala2/luminosidade`
        * `escola/biblioteca/temperatura`

---

