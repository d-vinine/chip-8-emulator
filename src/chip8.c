#include "chip8.h"
#include "opcodes.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

Chip8 chip8_create() {
  Chip8 chip;
  chip.pc = START_ADDRESS;

  for (int i = 0; i < FONTSET_SIZE; i++) {
    chip.memory[FONT_START_ADDRESS + i] = fontset[i];
  }

  srand48(time(0));

  return chip;
}

int chip8_load_rom(Chip8 *const chip, const char *filename) {
  FILE *rom = fopen(filename, "rb");
  if (!rom) {
    perror("Error opening ROM file");
    return -1;
  }

  fseek(rom, 0, SEEK_END);
  int size = ftell(rom);
  rewind(rom);

  if (size > MEMORY_SIZE - START_ADDRESS) {
    printf("Error: ROM is too large for memory\n");
    fclose(rom);
    return -1;
  }

  uint8_t *buffer = malloc(size);
  if (!buffer) {
    printf("Error: Could not allocate memory for buffer\n");
    fclose(rom);
    return -1;
  }

  int bytes = fread(buffer, 1, size, rom);
  if (bytes != size) {
    printf("Error reading file\n");
    fclose(rom);
    return -1;
  }

  for (int i = 0; i < size; i++) {
    chip->memory[START_ADDRESS + i] = buffer[i];
  }
  printf("ROM loaded successfully\n");

  free(buffer);
  fclose(rom);
  return 0;
}

uint8_t chip8_rand_byte() { return lrand48() % 256; }

void chip8_cycle(Chip8 *const chip) {
  chip->opcode = (chip->memory[chip->pc] << 8) | chip->memory[chip->pc + 1]; 

  chip->pc += 2;

  switch ((chip->opcode & 0xF000) >> 12) {
    case 0x1: chip8_OP_1NNN(chip); break;
    case 0x2: chip8_OP_2NNN(chip); break;
    case 0x3: chip8_OP_3XKK(chip); break;
    case 0x4: chip8_OP_4XKK(chip); break;
    case 0x5: chip8_OP_5XY0(chip); break;
    case 0x6: chip8_OP_6XKK(chip); break;
    case 0x7: chip8_OP_7XKK(chip); break;
    case 0x9: chip8_OP_9XY0(chip); break;
    case 0xA: chip8_OP_ANNN(chip); break;
    case 0xB: chip8_OP_BNNN(chip); break;
    case 0xC: chip8_OP_CXKK(chip); break;
    case 0xD: chip8_OP_DXYN(chip); break;
    case 0x8:
      switch(chip->opcode & 0x000F) {
        case 0x0: chip8_OP_8XY0(chip); break;
        case 0x1: chip8_OP_8XY1(chip); break;
        case 0x2: chip8_OP_8XY2(chip); break;
        case 0x3: chip8_OP_8XY3(chip); break;
        case 0x4: chip8_OP_8XY4(chip); break;
        case 0x5: chip8_OP_8XY5(chip); break;
        case 0x6: chip8_OP_8XY6(chip); break;
        case 0x7: chip8_OP_8XY7(chip); break;
        case 0xE: chip8_OP_8XYE(chip); break;
      }
      break;
    case 0x0:
      switch(chip->opcode & 0x000F) {
        case 0x0: chip8_OP_00E0(chip); break;
        case 0xE: chip8_OP_00EE(chip); break;
      }
      break;
    case 0xE:
      switch(chip->opcode & 0x00FF) {
        case 0xA1: chip8_OP_EXA1(chip); break;
        case 0x9E: chip8_OP_EX9E(chip); break;
      }
      break;
    case 0xF:
      switch(chip->opcode & 0x00FF) {
        case 0x07: chip8_OP_FX07(chip); break;
        case 0x0A: chip8_OP_FX0A(chip); break;
        case 0x15: chip8_OP_FX15(chip); break;
        case 0x18: chip8_OP_FX18(chip); break;
        case 0x1E: chip8_OP_FX1E(chip); break;
        case 0x29: chip8_OP_FX29(chip); break;
        case 0x33: chip8_OP_FX33(chip); break;
        case 0x55: chip8_OP_FX55(chip); break;
        case 0x65: chip8_OP_FX65(chip); break;
      }
      break;
  }

  if (chip->delay_timer > 0) {
    chip->delay_timer--;
  }

  if (chip->sound_timer > 0) {
    chip->sound_timer--;
  }
}


uint8_t fontset[FONTSET_SIZE] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};


