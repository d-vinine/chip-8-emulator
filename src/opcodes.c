#include <string.h>
#include "opcodes.h"
#include "chip8.h"

void chip8_OP_00E0(Chip8 *const chip) {
  memset(chip->disp_buffer, 0, sizeof(chip->disp_buffer));
}

void chip8_OP_00EE(Chip8 *const chip) {
  --chip->sp;
  chip->pc = chip->stack[chip->sp];
}

void chip8_OP_1NNN(Chip8 *const chip) {
  uint16_t address = chip->opcode & 0x0FFFu;

  chip->pc = address;
}

void chip8_OP_2NNN(Chip8 *const chip) {
  uint16_t address = chip->opcode & 0x0FFFu;
  chip->stack[chip->sp] = chip->pc;
  ++chip->sp;
  chip->pc = address;
}

void chip8_OP_3XKK(Chip8 *const chip) {
  uint8_t Vx = (chip->opcode & 0x0F00u) >> 8;
  uint8_t KK = chip->opcode & 0x00FFu;

  if (chip->registers[Vx] == KK) {
    chip->pc += 2;
  }
}

void chip8_OP_4XKK(Chip8 *const chip) {
  uint8_t Vx = (chip->opcode & 0x0F00u) >> 8;
  uint8_t KK = chip->opcode & 0x00FFu;

  if (chip->registers[Vx] != KK) {
    chip->pc += 2;
  }
}

void chip8_OP_5XY0(Chip8 *const chip) {
  uint8_t Vx = (chip->opcode & 0x0F00u) >> 8;
  uint8_t Vy = (chip->opcode & 0x00F0u) >> 4;

  if (chip->registers[Vx] == chip->registers[Vy]) {
    chip->pc += 2;
  }
}

void chip8_OP_6XKK(Chip8 *const chip) {
  uint8_t Vx = (chip->opcode & 0x0F00u) >> 8;
  uint8_t KK = chip->opcode & 0x00FFu;

  chip->registers[Vx] = KK;
}

void chip8_OP_7XKK(Chip8 *const chip) {
  uint8_t Vx = (chip->opcode & 0x0F00u) >> 8;
  uint8_t KK = chip->opcode & 0x00FFu;

  chip->registers[Vx] += KK;
}

void chip8_OP_8XY0(Chip8 *const chip) {
  uint8_t Vx = (chip->opcode & 0x0F00u) >> 8;
  uint8_t Vy = (chip->opcode & 0x00F0u) >> 4;

  chip->registers[Vx] = chip->registers[Vy];
}

void chip8_OP_8XY1(Chip8 *const chip) {
  uint8_t Vx = (chip->opcode & 0x0F00u) >> 8;
  uint8_t Vy = (chip->opcode & 0x00F0u) >> 4;

  chip->registers[Vx] |= chip->registers[Vy];
}

void chip8_OP_8XY2(Chip8 *const chip) {
  uint8_t Vx = (chip->opcode & 0x0F00u) >> 8;
  uint8_t Vy = (chip->opcode & 0x00F0u) >> 4;

  chip->registers[Vx] &= chip->registers[Vy];
}

void chip8_OP_8XY3(Chip8 *const chip) {
  uint8_t Vx = (chip->opcode & 0x0F00u) >> 8;
  uint8_t Vy = (chip->opcode & 0x00F0u) >> 4;

  chip->registers[Vx] ^= chip->registers[Vy];
}

void chip8_OP_8XY4(Chip8 *const chip) {
  uint8_t Vx = (chip->opcode & 0x0F00u) >> 8;
  uint8_t Vy = (chip->opcode & 0x00F0u) >> 4;

  uint16_t sum = chip->registers[Vx] + chip->registers[Vy];

  if (sum > 0xFFu) {
    chip->registers[0xF] = 1;
  } else {
    chip->registers[0xF] = 0;
  }

  chip->registers[Vx] = sum & 0xFFu;
}

void chip8_OP_8XY5(Chip8 *const chip) {
  uint8_t Vx = (chip->opcode & 0x0F00u) >> 8;
  uint8_t Vy = (chip->opcode & 0x00F0u) >> 4;

  if (chip->registers[Vx] > chip->registers[Vy]) {
    chip->registers[0xF] = 1;
  } else {
    chip->registers[0xF] = 0;
  }

  chip->registers[Vx] -= chip->registers[Vy];
}

void chip8_OP_8XY6(Chip8 *const chip) {
  uint8_t Vx = (chip->opcode & 0x0F00u) >> 8;

  chip->registers[0xF] = chip->registers[Vx] & 0x1;
  chip->registers[Vx] >>= 1;
}

void chip8_OP_8XY7(Chip8 *const chip) {
  uint8_t Vx = (chip->opcode & 0x0F00u) >> 8;
  uint8_t Vy = (chip->opcode & 0x00F0u) >> 4;

  if (chip->registers[Vy] > chip->registers[Vx]) {
    chip->registers[0xF] = 1;
  } else {
    chip->registers[0xF] = 0;
  }

  chip->registers[Vx] = chip->registers[Vy] - chip->registers[Vx];
}

void chip8_OP_8XYE(Chip8 *const chip) {
  uint8_t Vx = (chip->opcode & 0x0F00u) >> 8;

  chip->registers[0xF] = (chip->registers[Vx] & 0x80) >> 7;
  chip->registers[Vx] <<= 1;
}

void chip8_OP_9XY0(Chip8 *const chip) {
  uint8_t Vx = (chip->opcode & 0x0F00) >> 8;
  uint8_t Vy = (chip->opcode & 0x00F0) >> 4;

  if (chip->registers[Vx] != chip->registers[Vy]) {
    chip->pc += 2;
  }
}

void chip8_OP_ANNN(Chip8 *const chip) {
  uint16_t address = chip->opcode & 0x0FFF;
  chip->index = address;
}

void chip8_OP_BNNN(Chip8 *const chip) {
  uint16_t address = chip->opcode & 0x0FFF;
  chip->pc = chip->registers[0] + address;
}

void chip8_OP_CXKK(Chip8 *const chip) {
  uint8_t Vx = (chip->opcode & 0x0F00) >> 8;
  uint8_t byte = chip->opcode & 0x00FF;

  chip->registers[Vx] = chip8_rand_byte() & byte;
}

void chip8_OP_DXYN(Chip8 *const chip) {
  uint8_t Vx = (chip->opcode & 0x0F00) >> 8;
  uint8_t Vy = (chip->opcode & 0x00F0) >> 4;
  uint8_t n = chip->opcode & 0x000F;

  uint8_t x = chip->registers[Vx] % DISP_WIDTH;
  uint8_t y = chip->registers[Vy] % DISP_HEIGHT;

  chip->registers[0xF] = 0;

  for (int i = 0; i < n; i++) {
    uint8_t spriteByte = chip->memory[chip->index + i];

    for (int j = 0; j < 8; j++) {
      uint8_t spritePixel = (spriteByte >> j) & 1;
      uint8_t *screenPixel = &chip->disp_buffer[(y + i) * DISP_WIDTH + (x + j)];

      if (*screenPixel) {
        chip->registers[0xF] = 1;
      }

      *screenPixel ^= 1;
    }
  }
}

void chip8_OP_EX9E(Chip8 *const chip) {
  uint8_t Vx = (chip->opcode & 0x0F00) >> 8;

  uint8_t key = chip->registers[Vx];

  if (chip->keypad[key]) {
    chip->pc += 2;
  }
}

void chip8_OP_EXA1(Chip8 *const chip) {
  uint8_t Vx = (chip->opcode & 0x0F00) >> 8;

  uint8_t key = chip->registers[Vx];

  if (!chip->keypad[key]) {
    chip->pc += 2;
  }
}

void chip8_OP_FX07(Chip8 *const chip) {
  uint8_t Vx = (chip->opcode & 0x0F00) >> 8;

  chip->registers[Vx] = chip->delay_timer;
}

void chip8_OP_FX0A(Chip8 *const chip) {
  uint8_t Vx = (chip->opcode & 0x0F00) >> 8;

  if (chip->keypad[0]) {
    chip->registers[Vx] = 0;
  } else if (chip->keypad[1]) {
    chip->registers[Vx] = 1;
  } else if (chip->keypad[2]) {
    chip->registers[Vx] = 2;
  } else if (chip->keypad[3]) {
    chip->registers[Vx] = 3;
  } else if (chip->keypad[4]) {
    chip->registers[Vx] = 4;
  } else if (chip->keypad[5]) {
    chip->registers[Vx] = 5;
  } else if (chip->keypad[6]) {
    chip->registers[Vx] = 6;
  } else if (chip->keypad[7]) {
    chip->registers[Vx] = 7;
  } else if (chip->keypad[8]) {
    chip->registers[Vx] = 8;
  } else if (chip->keypad[9]) {
    chip->registers[Vx] = 9;
  } else if (chip->keypad[10]) {
    chip->registers[Vx] = 10;
  } else if (chip->keypad[11]) {
    chip->registers[Vx] = 11;
  } else if (chip->keypad[12]) {
    chip->registers[Vx] = 12;
  } else if (chip->keypad[13]) {
    chip->registers[Vx] = 13;
  } else if (chip->keypad[14]) {
    chip->registers[Vx] = 14;
  } else if (chip->keypad[15]) {
    chip->registers[Vx] = 15;
  } else {
    chip->pc -= 2;
  }
}

void chip8_OP_FX15(Chip8 *const chip) {
  uint8_t Vx = (chip->opcode & 0x0F00) >> 8;

  chip->delay_timer = chip->registers[Vx];
}

void chip8_OP_FX18(Chip8 *const chip) {
  uint8_t Vx = (chip->opcode & 0x0F00) >> 8;

  chip->sound_timer = chip->registers[Vx];
}

void chip8_OP_FX1E(Chip8 *const chip) {
  uint8_t Vx = (chip->opcode & 0x0F00) >> 8;

  chip->index += chip->registers[Vx];
}

void chip8_OP_FX29(Chip8 *const chip) {
  uint8_t Vx = (chip->opcode & 0x0F00) >> 8;
  uint8_t digit = chip->registers[Vx];

  chip->index = FONT_START_ADDRESS + (5 * digit);
}

void chip8_OP_FX33(Chip8 *const chip) {
  uint8_t Vx = (chip->opcode & 0x0F00) >> 8;
  uint8_t val = chip->registers[Vx];

  chip->memory[chip->index + 2] = val % 10;
  val /= 10;

  chip->memory[chip->index + 1] = val % 10;
  val /= 10;

  chip->memory[chip->index] = val % 10;
}

void chip8_OP_FX55(Chip8 *const chip) {
  uint8_t Vx = (chip->opcode & 0x0F00) >> 8;

  for (uint8_t i = 0; i <= Vx; i++) {
    chip->memory[chip->index + i] = chip->registers[i];
  }
}

void chip8_OP_FX65(Chip8 *const chip) {
  uint8_t Vx = (chip->opcode & 0x0F00) >> 8;

  for (uint8_t i = 0; i <= Vx; i++) {
    chip->registers[i] = chip->memory[chip->index + i];
  }
}


