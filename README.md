# SemaforoPico
Este projeto implementa um semáforo utilizando LEDs no Raspberry Pi Pico. O sistema alterna entre os estados vermelho, amarelo e verde em intervalos de tempo definidos, simulando o funcionamento de um semáforo real.

# Requisitos

Para rodar este projeto, você precisará de:
Raspberry Pi Pico

-3 LEDs (Vermelho, Amarelo e Verde)

-3 resistores de 330Ω (opcional, mas recomendado)

-Jumpers e uma protoboard

-SDK do Raspberry Pi Pico configurado


# Esquema de Ligação

Os LEDs devem ser conectados aos seguintes pinos:

-LED Vermelho → GPIO 13

-LED Amarelo → GPIO 12

-LED Verde → GPIO 11


O outro terminal de cada LED deve ser conectado ao GND através de um resistor.

# Funcionamento

O código funciona da seguinte maneira:

-Inicializa os LEDs e configura-os como saída.

-Começa no estado vermelho.

-Um temporizador alterna os LEDs a cada 3 segundos.

-O estado do semáforo segue esta sequência: vermelho → amarelo → verde → vermelho.

-Mensagens de depuração são enviadas pela porta serial.

Funcionamento
Semaforo rodando
Semáforo: VERMELHO
Semáforo: AMARELO
Semáforo: VERDE

# Link do vídeo
https://youtu.be/hP140QebJ8o
