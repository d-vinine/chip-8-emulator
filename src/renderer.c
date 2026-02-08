#include "renderer.h"
#include "chip8.h"
#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <termios.h>
#include <string.h>
#include <unistd.h>

void renderer_init(struct termios *old_settings) {
  struct termios new_settings;
  tcgetattr(STDIN_FILENO, old_settings);

  cfmakeraw(&new_settings);
  new_settings.c_cc[VMIN] = 0;
  new_settings.c_cc[VTIME] = 0;

  tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);

  printf("\e[2J\e[?25l");
}

void renderer_update(uint8_t *const buffer) {
  printf("\e[H");

  for (int i = 0; i < DISP_HEIGHT; i += 2) {
    for (int j = 0; j < DISP_WIDTH; j++) {
      int top = buffer[i * DISP_WIDTH + j];
      int bottom = (i + 1 < DISP_HEIGHT) ? buffer[(i + 1) * DISP_WIDTH + j] : 0;

      if (top && bottom) {
        fputs("\e[37;47m▀", stdout);
      } else if (top) {
        fputs("\e[37;40m▀", stdout);
      } else if (bottom) {
        fputs("\e[30;47m▀", stdout);
      } else {
        fputs("\e[30;40m ", stdout);
      }
    }
    fputs("\e[0m\r\n", stdout);
  }
  fflush(stdout);
}
int renderer_process_input(uint8_t *keys) {

  uint8_t ch;
  if (read(STDIN_FILENO, &ch, 1) != 1)
    return 0;

  if (ch == 27)
    return -1; 

  ch = toupper(ch);

  memset(keys, 0, 16);
  switch (ch) {
  case '1':
    keys[0x1] = 1;
    break;
  case '2':
    keys[0x2] = 1;
    break;
  case '3':
    keys[0x3] = 1;
    break;
  case '4':
    keys[0xC] = 1;
    break;

  case 'Q':
    keys[0x4] = 1;
    break;
  case 'W':
    keys[0x5] = 1;
    break;
  case 'E':
    keys[0x6] = 1;
    break;
  case 'R':
    keys[0xD] = 1;
    break;

  case 'A':
    keys[0x7] = 1;
    break;
  case 'S':
    keys[0x8] = 1;
    break;
  case 'D':
    keys[0x9] = 1;
    break;
  case 'F':
    keys[0xE] = 1;
    break;

  case 'Z':
    keys[0xA] = 1;
    break;
  case 'X':
    keys[0x0] = 1;
    break;
  case 'C':
    keys[0xB] = 1;
    break;
  case 'V':
    keys[0xF] = 1;
    break;

  case 27:
    return -1;
  }

  return 1; // Key was processed
}

void renderer_close(struct termios *old_settings) {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, old_settings);
  printf("\e[2J\e[?25l");
  printf("\e[?25h\n");
  printf("\e[H");
}
