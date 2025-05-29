#ifndef OPCODE_H
#define OPCODE_H

#include "chip8.h"

void decodeOpcode(struct Chip8* chip8, unsigned short opcode);
void drawSprite(struct Chip8* chip8, uint8_t x, uint8_t y, uint8_t height);

#endif // OPCODE_H
