#include "chip8.h"
#include "renderer.h"
#include <stdio.h>

int main() {
  uint8_t buffer[DISP_WIDTH * DISP_HEIGHT] = {0};

  printf("\e[2J\e[?25l");

  for (int y = 0; y < DISP_HEIGHT; y++) {
    for (int x = 0; x < DISP_WIDTH; x++) {
      // Check if the sum of tile coordinates is even
      if ((y + x) % 2 == 0) {
        buffer[y * DISP_WIDTH + x] = 1;
      } else {
        buffer[y * DISP_WIDTH + x] = 0;
      }
    }
  }

  renderer_update(buffer);

  // Show cursor again and move down so prompt doesn't overwrite display
  printf("\e[?25h\n");
  return 0;
}
