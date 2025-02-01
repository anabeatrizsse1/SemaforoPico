#include <stdio.h>

#include "hardware/timer.h"
#include "pico/stdlib.h"

// define o numero do pino para cada led
#define LED_R 13  // LED vermelho
#define LED_Y 12  // LED amarelo
#define LED_G 11  // LED verde
// define tempo de espera entre cada acionamento
#define INTERVAL_DURATION 3000

// armazena o estado atual do semaforo
volatile int state = 1;

void define_all_leds() {
  // inicia e define o led o tipo do pino do led vermelho
  gpio_init(RED_LED_PIN);
  gpio_set_dir(RED_LED_PIN, GPIO_OUT);
  // inicia e define o led o tipo do pino do led amarelo
  gpio_init(YELLOW_LED_PIN);
  gpio_set_dir(YELLOW_LED_PIN, GPIO_OUT);
  // inicia e define o led o tipo do pino do led verde
  gpio_init(GREEN_LED_PIN);
  gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);
}

bool run_semaphore(struct repeating_timer *t) {
  // Desliga todos os LEDs
  gpio_put(RED_LED_PIN, 0);
  gpio_put(YELLOW_LED_PIN, 0);
  gpio_put(GREEN_LED_PIN, 0);

  // Alterna o estado do semáforo
  switch (state) {
    case 0:
      gpio_put(RED_LED_PIN, 1);
      break;
    case 1:
      gpio_put(YELLOW_LED_PIN, 1);
      break;
    case 2:
      gpio_put(GREEN_LED_PIN, 1);
      break;
  }

  state = (state + 1) % 3;

  return true;
}

int main() {
  struct repeating_timer timer;

  stdio_init_all();
  define_all_leds();
  // liga inicialmente o led vermelho
  gpio_put(RED_LED_PIN, 1);
  add_repeating_timer_ms(INTERVAL_DURATION, run_semaphore, NULL, &timer);

  while (true) {
    printf("Semaforo rodando\n");
    sleep_ms(1000);
  }
}
