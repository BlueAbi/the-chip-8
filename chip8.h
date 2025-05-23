#ifndef CHIP8_H
#define CHIP8_H

#include <stdint.h>

#define MEM 4096
#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32
#define STACK_SIZE 16
#define NUM_REGS 16
#define KEYPAD_SIZE 16

struct Chip8 {
    uint8_t memory[MEM];                              // Memory array, size 4096 bytes
    uint8_t V[NUM_REGS];                              // 16 registers
    unsigned short I;                                 // Index register
    unsigned short pc;                                // Program counter
    uint16_t stack[STACK_SIZE];                       // Stack for subroutine calls
    uint8_t sp;                                       // Stack pointer
    uint8_t delay_timer;
    uint8_t sound_timer;
    uint8_t display[DISPLAY_WIDTH * DISPLAY_HEIGHT];  // Display
    uint8_t keypad[KEYPAD_SIZE];                      // Keypad 16 keys
    unsigned short opcode;                            // stores opcode value
};

void decode_opcode(struct Chip8* chip8, unsigned short opcode);
