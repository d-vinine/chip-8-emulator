#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define START_ADDRESS 0x200
#define MEMORY_SIZE 4096

typedef struct {

  uint8_t registers[16];

  uint8_t memory[MEMORY_SIZE];

  uint16_t index;
  uint16_t pc;

  uint16_t stack[16];
  uint8_t sp;

  uint8_t delay_timer;
  uint8_t sound_timer;

  uint8_t keypad[16];

  uint8_t disp_buffer[32 * 64];

  uint16_t opcode;

} Chip8;
int chip8_load_rom(Chip8 *const chip, const char *filename);


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
