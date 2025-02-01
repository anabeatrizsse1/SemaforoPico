#include <stdio.h>               // Biblioteca para funções de entrada e saída
#include "hardware/timer.h"      // Biblioteca para manipulação de temporizadores
#include "pico/stdlib.h"         // Biblioteca padrão do Raspberry Pi Pico

// Definição dos pinos GPIO para os LEDs
#define LED_R 13  // LED vermelho
#define LED_Y 12  // LED amarelo
#define LED_G 11  // LED verde

// Definição do tempo de espera entre as mudanças do semáforo (em milissegundos)
#define INTERVAL_DURATION 3000  

// Variável global para armazenar o estado atual do semáforo (0 = vermelho, 1 = amarelo, 2 = verde)
volatile int estado = 1;

// Função chamada periodicamente pelo temporizador para atualizar o semáforo
bool atualizar_semaforo(struct repeating_timer *t) {
  // Desliga todos os LEDs antes de acender o próximo estado
  gpio_put(LED_R, 0);
  gpio_put(LED_Y, 0);
  gpio_put(LED_G, 0);

  // Liga o LED correspondente ao estado atual
  switch (estado) {
    case 0:
      gpio_put(LED_R, 1);  // Acende o LED vermelho
      break;
    case 1:
      gpio_put(LED_Y, 1);  // Acende o LED amarelo
      break;
    case 2:
      gpio_put(LED_G, 1);  // Acende o LED verde
      break;
  }

  // Atualiza o estado para o próximo ciclo (0 → 1 → 2 → 0)
  estado = (estado + 1) % 3;

  return true;  // Mantém o temporizador ativo
}

// Função para configurar os pinos dos LEDs como saída
void Config_Led() {
  // Inicializa e configura os pinos GPIO como saída
  gpio_init(LED_R);
  gpio_set_dir(LED_R, GPIO_OUT);

  gpio_init(LED_Y);
  gpio_set_dir(LED_Y, GPIO_OUT);

  gpio_init(LED_G);
  gpio_set_dir(LED_G, GPIO_OUT);
}

// Função principal
int main() {
  struct repeating_timer timer;  // Estrutura para o temporizador

  stdio_init_all();  // Inicializa a interface serial para debug
  Config_Led();      // Configura os LEDs como saída

  // Liga inicialmente o LED vermelho
  gpio_put(LED_R, 1);

  // Inicia o temporizador para chamar 'atualizar_semaforo' a cada INTERVAL_DURATION ms
  add_repeating_timer_ms(INTERVAL_DURATION, atualizar_semaforo, NULL, &timer);

  // Loop infinito para manter o programa rodando
  while (true) {
    printf("Semaforo rodando\n");  // Mensagem de depuração no terminal
    sleep_ms(1000);  // Aguarda 1 segundo antes de repetir a mensagem
  }
}
