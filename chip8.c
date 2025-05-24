#include "chip8.h"
#include "opcode.h"
#include <stdio.h>

void initialize(struct Chip8* chip8) {
    // Initialize registers and memory once
}

void emulateCycle(struct Chip8* chip8) {
    // Fetch Opcode
    //memory[pc];     // first byte of opcode
    //memory[pc + 1]; // second byte of opcode  (opcodes are two bytes)
    unsigned short opcode = (chip8 -> memory[chip8 -> pc] << 8) | chip8 -> memory[chip8 -> pc + 1]; // grabs the opcode

    // Decode Opcode & Execute Opcode
    decodeOpcode(chip8, opcode);

    chip8 -> pc += 2; // Next instruction

    // Update timers
}

void updateTimers(struct Chip8* chip8) {

}
