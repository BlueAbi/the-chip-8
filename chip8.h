#ifndef CHIP8_H
#define CHIP8_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_keyboard.h>

#define MEM 4096
#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32
#define STACK_SIZE 16
#define NUM_REGS 16
#define KEYPAD_SIZE 16

typedef struct Chip8 {
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
    bool drawFlag;                                    // Flag to tell when to refresh screen
} Chip8;

void chip8_initialize(struct Chip8* chip8);
void emulateCycle(struct Chip8* chip8);
void setupInput();
void setKeys(struct Chip8* chip8);
void setupGraphics(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture);
void drawGraphics(struct Chip8* chip8);
void loadGame();


#endif
