// chip8.h
#ifndef CHIP8_H
#define CHIP8_H

#include <stdint.h>

#define MEM_SIZE 4096
#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32
#define STACK_SIZE 16
#define NUM_REGS 16
#define KEYPAD_SIZE 16

struct Chip8 {
    uint8_t memory[MEM_SIZE];         // 4KB of RAM
    uint8_t V[NUM_REGS];                 // V0 to VF registers
    uint16_t I;                          // Index register
    uint16_t pc;                         // Program counter
    uint16_t stack[STACK_SIZE];         // Call stack
    uint8_t sp;                          // Stack pointer
    uint8_t delay_timer;                // Delay timer
    uint8_t sound_timer;                // Sound timer
    uint8_t display[DISPLAY_WIDTH * DISPLAY_HEIGHT];  // Monochrome screen
    uint8_t keypad[KEYPAD_SIZE];        // Key states (pressed or not)
};

void chip8_initialize(struct Chip8 *chip);

#endif
