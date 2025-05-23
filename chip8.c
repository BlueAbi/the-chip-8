#include "chip8.h"

void initialize(struct Chip8* chip8) {
    // Initialize registers and memory once
}

void emulateCycle(struct Chip8* chip8) {
    // Fetch Opcode
    //memory[pc];     // first byte of opcode
    //memory[pc + 1]; // second byte of opcode  (opcodes are two bytes)
    unsigned short opcode = (chip8->memory[chip8->pc] << 8) | chip8->memory[chip8->pc + 1]; // grabs the opcode

    // Decode Opcode


    // Execute Opcode

    pc += 2;

    // Update timers
}

void decodeOpcode(struct Chip8* chip8, unsigned short opcode) {
    switch (opcode & 0xF000) {
        case 0x0000:
            // Calls machine code routine (RCA 1802 for COSMAC VIP) at address NNN. Not necessary for most ROMs
            if (opcode == 0x00E0) {
                // clear the screen
            } else if (opcode == 0x00EE) {
                // return from a subroutine
            }
            break;

        case 0x1000:
            // jump to address 0x1NNN
            break;

        case 0x2000:
            // calls subroutine at 0x2NNN
            break;

        case 0x3000: // 0x3XNN
            // skips next instruction if VX equals NN (usually the next instruction is a jump to skip a code block)
            break;

        case 0x4000: // 0x4XNN
            // skips next instruction if VX does not equal NN
            break;

        case 0x5000: // 0x5XY0
            // skips next instruction if VX equals VY
            break;

        case 0x6000: // 0x6XNN
            // sets VX to NN
            break;

        case 0x7000: // 0x7XNN
            // adds NN to VX (carry flag is not changed)
            break;

        case 0x8000: // 0x8XYN
            switch (opcode & 0x000F) {
                // enter cases for 0x0001-0x0007, 0x000E
            }
            break;

        case 0x9000: // 0x9XY0
            // skips next instruction is VX does not equal VY
            break;

        case 0xA000: // 0xANNN
            // sets I to the address NNN
            break;

        case 0xB000: // 0xBNNN
            // jumps to the address NNN plus V0, PC = V0 + NNN
            break;

        case 0xC000: // 0xCXNN
            // sets VX to the result of a bitwise AND operation on a random number (Typically: 0 to 255) and NN
            // Vx = rand() & NN
            break;

        case 0xD000: // 0xDXYN
            // draws a sprite at coordinate (VX, VY) with a width of 8 pixel and heigh N pixels
            // draw(Vx, Vy, N)
            break;

        case 0xE000: // two cases, 0xEX9E and 0xEXA1
            if ((opcode & 0x00FF) == 0x009E) {
                // skips next instruction if the key stored in VX(only consider the lowest nibble) is pressed
                // if (key() == Vx)
            } else if ((opcode & 0x00FF) == 0x00A1) {
                // Skips the next instruction if the key stored in VX(only consider the lowest nibble) is not pressed
                // if (key() != Vx)
            }
            break;

        case 0xF000:
            switch (opcode & 0x00FF) {
                case 0x0007:
                    // sets VX to value of delay timer
                break;
            }

            break;

        default:
            printf("Unknown opcode: 0x%04X\n", opcode);
            break;
    }
}
