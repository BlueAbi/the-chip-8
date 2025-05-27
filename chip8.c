#include "chip8.h"
#include "opcode.h"
#include <string.h> // used for memset
#include <time.h>
#include <stdlib.h>

void chip8_initialize(struct Chip8* chip8) {

    // seed the random number generator
    srand((unsigned int) time(NULL));

    // Initialize registers and memory once
    memset(chip8 -> memory, 0, MEM);
    memset(chip8 -> V, 0, NUM_REGS);
    memset(chip8 -> stack, 0, STACK_SIZE);
    memset(chip8 -> display, 0, DISPLAY_WIDTH * DISPLAY_HEIGHT);
    memset(chip8 -> keypad, 0, KEYPAD_SIZE);

    chip8 -> I = 0;
    chip8 -> pc = 0x200; // Start of most Chip8 programs
    chip8 -> sp = 0;
    chip8 -> delay_timer = 0;
    chip8 -> sound_timer = 0;
    chip8 -> opcode = 0;

    // Clear display
    // Clear stack
    // Clear registers V0-VF
    // Clear memory

    static const uint8_t fontset[80] = {
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

    // Load fontset at 0x50
    for (int i = 0; i < 80; ++i) {
        chip8 -> memory[0x50 + i] = fontset[i];
    }

    // Reset timers
}

void emulateCycle(struct Chip8* chip8) {
    // Fetch Opcode
    // memory[pc];     // first byte of opcode
    // memory[pc + 1]; // second byte of opcode  (opcodes are two bytes)
    unsigned short opcode = (chip8 -> memory[chip8 -> pc] << 8) | chip8 -> memory[chip8 -> pc + 1]; // grabs the opcode

    // Decode Opcode & Execute Opcode
    decodeOpcode(chip8, opcode);

    chip8 -> pc += 2; // Next instruction

    // Update timers
}

void updateTimers(struct Chip8* chip8) {

}

void setupGraphics() {

}

void setupInput() {

}

void drawGraphics(struct Chip8* chip8, unsigned short opcode) {
    unsigned short x = chip8 -> V[(opcode & 0x0F00) >> 8];
    unsigned short y = chip8 -> V[(opcode & 0x00F0) >> 4];
    unsigned short height = opcode & 0x000F;
    unsigned short pixel;

    chip8 -> V[0x000F] = 0;
    for (int yline = 0; yline < height; yline++) {
        pixel = chip8 -> memory[chip8 -> I + yline];
        for (int xline = 0; xline < 8; xline++) {
            if ((pixel & (0x0080 >> xline)) != 0) {
                if (chip8 -> display[(x + xline + ((y + yline) * 64))] == 1) {
                    chip8 -> V[0x000F] = 1; // Collision detected
                }
                chip8 -> display[x + xline + ((y + yline) * 64)] ^= 1; // XOR to draw pixel
            }
        }
    }
    chip8 -> drawFlag = true; // Set flag to refresh screen
}
