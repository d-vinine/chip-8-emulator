#ifndef __OPCODES_H__
#define __OPCODES_H__

typedef struct Chip8 Chip8;

void chip8_OP_00E0(Chip8 *const chip);
void chip8_OP_00EE(Chip8 *const chip);
void chip8_OP_1NNN(Chip8 *const chip);
void chip8_OP_2NNN(Chip8 *const chip);
void chip8_OP_3XKK(Chip8 *const chip);
void chip8_OP_4XKK(Chip8 *const chip);
void chip8_OP_5XY0(Chip8 *const chip);
void chip8_OP_6XKK(Chip8 *const chip);
void chip8_OP_7XKK(Chip8 *const chip);
void chip8_OP_8XY0(Chip8 *const chip);
void chip8_OP_8XY1(Chip8 *const chip);
void chip8_OP_8XY2(Chip8 *const chip);
void chip8_OP_8XY3(Chip8 *const chip);
void chip8_OP_8XY4(Chip8 *const chip);
void chip8_OP_8XY5(Chip8 *const chip);
void chip8_OP_8XY6(Chip8 *const chip);
void chip8_OP_8XY7(Chip8 *const chip);
void chip8_OP_8XYE(Chip8 *const chip);
void chip8_OP_9XY0(Chip8 *const chip);
void chip8_OP_ANNN(Chip8 *const chip);
void chip8_OP_BNNN(Chip8 *const chip);
void chip8_OP_CXKK(Chip8 *const chip);
void chip8_OP_DXYN(Chip8 *const chip);
void chip8_OP_EX9E(Chip8 *const chip);
void chip8_OP_EXA1(Chip8 *const chip);
void chip8_OP_FX07(Chip8 *const chip);
void chip8_OP_FX0A(Chip8 *const chip);
void chip8_OP_FX15(Chip8 *const chip);
void chip8_OP_FX18(Chip8 *const chip);
void chip8_OP_FX1E(Chip8 *const chip);
void chip8_OP_FX29(Chip8 *const chip);
void chip8_OP_FX33(Chip8 *const chip);
void chip8_OP_FX55(Chip8 *const chip);
void chip8_OP_FX65(Chip8 *const chip);

#endif
