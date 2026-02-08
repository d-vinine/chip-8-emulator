#include "chip8.h"
#include "renderer.h"
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: %s <ROM>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  char const *rom = argv[1];

  Chip8 chip = chip8_create();
  chip8_load_rom(&chip, rom);

  int run = 1;
  float cycle_delay_ms = 1/120.0f * 1e3;

  struct timespec last_time, current_time;
  clock_gettime(CLOCK_MONOTONIC, &last_time);

  struct termios old;
  renderer_init(&old);
  while (run) {
    if (renderer_process_input(chip.keypad) == -1) {
      run = 0;
    }

    clock_gettime(CLOCK_MONOTONIC, &current_time);

    float dt = (current_time.tv_sec - last_time.tv_sec) * 1000 +
               (current_time.tv_nsec - last_time.tv_nsec) / 1e6;

    if (dt >= cycle_delay_ms) {
      last_time = current_time;

      chip8_cycle(&chip);

      renderer_update(chip.disp_buffer);
    }
  }
  renderer_close(&old);

  return 0;
}
