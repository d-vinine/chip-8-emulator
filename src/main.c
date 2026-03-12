#include "chip8.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#define FPS 60
#define CYCLE_PER_FRAME 10

#define WIDTH 640
#define HEIGHT 320

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: %s <ROM>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  char const *rom = argv[1];

  Chip8 chip = chip8_create();
  chip8_load_rom(&chip, rom);

  static const int keymap[16] = {
      KEY_X, KEY_ONE, KEY_TWO, KEY_THREE, KEY_Q,    KEY_W, KEY_E, KEY_A,
      KEY_S, KEY_D,   KEY_Z,   KEY_C,     KEY_FOUR, KEY_R, KEY_F, KEY_V};

  int pixelWidth = WIDTH / 64;
  int pixelHeight = HEIGHT / 32;
  InitWindow(WIDTH, HEIGHT, "Chip8");
  SetTargetFPS(FPS);

  while (!WindowShouldClose()) {

    for (int i = 0; i < 16; i++) {
      chip.keypad[i] = IsKeyDown(keymap[i]) ? 1 : 0;
    }
    for (int i = 0; i < CYCLE_PER_FRAME; i++) {

      chip8_cycle(&chip);
    }

    BeginDrawing();
    ClearBackground(BLACK);
    for (int row = 0; row < 32; row++) {
      for (int col = 0; col < 64; col++) {
        if (chip.disp_buffer[row * 64 + col]) {
          DrawRectangle(col * pixelWidth, row * pixelHeight, pixelWidth,
                        pixelHeight, WHITE);
        }
      }
    }
    EndDrawing();
  }
  CloseWindow();

  return 0;
}
