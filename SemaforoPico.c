#include <stdio.h>
#include "hardware/timer.h"
#include "pico/stdlib.h"

// Define o numero do pino para cada LED
#define LED_R 13  // LED vermelho
#define LED_Y 12  // LED amarelo
#define LED_G 11  // LED verde

// Define tempo de espera entre cada acionamento (em milissegundos)
#define INTERVAL_DURATION 3000

// Armazena o estado atual do semaforo
volatile int state = 1;

// Funcao para configurar os LEDs
void define_all_leds() {
  // Inicializa e define o pino do LED vermelho como saida
  gpio_init(LED_R);
  gpio_set_dir(LED_R, GPIO_OUT);
  
  // Inicializa e define o pino do LED amarelo como saida
  gpio_init(LED_Y);
  gpio_set_dir(LED_Y, GPIO_OUT);
  
  // Inicializa e define o pino do LED verde como saida
  gpio_init(LED_G);
  gpio_set_dir(LED_G, GPIO_OUT);
}

// Funcao que controla a troca dos LEDs no semaforo
bool run_semaphore(struct repeating_timer *t) {
  // Desliga todos os LEDs
  gpio_put(LED_R, 0);
  gpio_put(LED_Y, 0);
  gpio_put(LED_G, 0);

  // Alterna o estado do semaforo e liga o LED correspondente
  switch (state) {
    case 0:
      gpio_put(LED_R, 1); // Liga o LED vermelho
      break;
    case 1:
      gpio_put(LED_Y, 1); // Liga o LED amarelo
      break;
    case 2:
      gpio_put(LED_G, 1); // Liga o LED verde
      break;
  }

  // Atualiza o estado para o proximo ciclo
  state = (state + 1) % 3;

  return true; // Retorna true para manter o timer rodando
}

int main() {
  struct repeating_timer timer;

  // Inicializa a comunicacao padrao
  stdio_init_all();
  
  // Configura os LEDs
  define_all_leds();
  
  // Liga inicialmente o LED vermelho
  gpio_put(LED_R, 1);
  
  // Configura um timer para alternar os LEDs a cada intervalo definido
  add_repeating_timer_ms(INTERVAL_DURATION, run_semaphore, NULL, &timer);

  while (true) {
    // Exibe uma mensagem na saida padrao indicando que o semaforo esta rodando
    printf("Semaforo rodando\n");
    sleep_ms(1000); // Aguarda 1 segundo antes de repetir a mensagem
  }
}
