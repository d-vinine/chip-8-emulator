#ifndef __CHIP8_H__
#define __CHIP8_H__

#include <stdint.h>

#define START_ADDRESS 0x200
#define MEMORY_SIZE 4096
#define FONT_START_ADDRESS 0x50
#define FONTSET_SIZE 80

#define DISP_WIDTH 64
#define DISP_HEIGHT 32

typedef struct Chip8 {

  uint8_t registers[16];

  uint8_t memory[MEMORY_SIZE];

  uint16_t index;
  uint16_t pc;

  uint16_t stack[16];
  uint8_t sp;

  uint8_t delay_timer;
  uint8_t sound_timer;

  uint8_t keypad[16];

  uint8_t disp_buffer[DISP_HEIGHT * DISP_WIDTH];

  uint16_t opcode;

} Chip8;
Chip8 chip8_create();
int chip8_load_rom(Chip8 *const chip, const char *filename);
uint8_t chip8_rand_byte();
void chip8_cycle(Chip8 *const chip);

extern uint8_t fontset[];
#endif
