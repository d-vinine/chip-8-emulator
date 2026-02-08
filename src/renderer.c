#include "renderer.h"
#include "chip8.h"
#include <stdio.h>

void renderer_update(uint8_t *const buffer) {
  printf("\e[H"); // Move cursor to top-left

  for (int i = 0; i < DISP_HEIGHT; i += 2) {
    for (int j = 0; j < DISP_WIDTH; j++) {
      int top = buffer[i * DISP_WIDTH + j];
      int bottom = buffer[(i + 1) * DISP_WIDTH + j];

      if (top && bottom) {
        printf("\e[37;47m▀\e[0m");
      } else if (top && !bottom) {
        printf("\e[37;40m▀\e[0m");
      } else if (!top && bottom) {
        printf("\e[30;47m▀\e[0m");
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }
  fflush(stdout);
}

int renderer_process_input(uint8_t *keys);
