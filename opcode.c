#include "opcode.h"
#include <stdio.h>
#include <stdlib.h>

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
        chip8 -> pc = opcode & 0x0FFF;
        break;

    case 0x2000:
        // calls subroutine at 0x2NNN
        chip8 -> stack[chip8 -> sp] = chip8 -> pc;
        chip8 -> sp++;
        chip8 -> pc = opcode & 0x0FFF;
        break;

    case 0x3000: // 0x3XNN
        // skips next instruction if VX equals NN (usually the next instruction is a jump to skip a code block)
        if (chip8 -> V[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF)) {
            chip8 -> pc += 2;
        }
        break;

    case 0x4000: // 0x4XNN
        // skips next instruction if VX does not equal NN
        if (chip8 -> V[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF)) {
            chip8 -> pc += 2;
        }
        break;

    case 0x5000: // 0x5XY0
        // Skips next instruction if VX equals VY
        if (chip8->V[((opcode & 0x0F00) >> 8)] == chip8->V[((opcode & 0x00F0) >> 4)]) {
            chip8->pc += 2;  // Skip next instruction
        }
        break;

    case 0x6000: // 0x6XNN
        // sets VX to NN
        chip8 -> V[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
        break;

    case 0x7000: // 0x7XNN
        // adds NN to VX (carry flag is not changed)
        chip8 -> V[(opcode & 0x0F00) >> 8] += opcode & 0x00FF;
        break;

    case 0x8000: // 0x8XYN
        switch (opcode & 0x000F) {
        // enter cases for 0x0001-0x0007, 0x000E
        case 0x0000:
            // set Vx to the value of Vy, Vx = Vy
            chip8 -> V[(opcode & 0x0F00) >> 8] = chip8 -> V[(opcode & 0x00F0) >> 4];
            break;

        case 0x0001:
            // sets Vx to Vx OR Vy, Vx |= Vy
            chip8 -> V[(opcode & 0x0F00) >> 8] |= chip8 -> V[(opcode & 0x00F0) >> 4];
            break;

        case 0x0002:
            // sets Vx to Vx AND Vy, Vx &= Vy
            chip8 -> V[(opcode & 0x0F00) >> 8] &= chip8 -> V[(opcode & 0x00F0) >> 4];
            break;

        case 0x0003:
            // sets Vx to Vx XOR Vy, Vx ^= Vy
            chip8 -> V[(opcode & 0x0F00) >> 8] ^= chip8 -> V[(opcode & 0x00F0) >> 4];
            break;

        case 0x0004:
            // adds Vy to Vx, Vx += Vy
            uint16_t sum = chip8 -> V[(opcode & 0x0F00) >> 8] + chip8 -> V[(opcode & 0x00F0) >> 4];
            chip8 -> V[0x000F] = sum > 0x00FF;
            chip8 -> V[(opcode & 0x0F00) >> 8] = sum & 0x00FF;
            break;

        case 0x0005:
            // Vx -= Vy, set V[F] to 1 if there was no borrow, 0 if there was a borrow
            if (chip8 -> V[(opcode & 0x0F00) >> 8] > chip8 -> V[(opcode & 0x00F0) >> 4]) {
                chip8 -> V[0x000F] = 1;  // No borrow
            } else {
                chip8 -> V[0x000F] = 0;  // Borrow occurred
            }
            chip8 -> V[(opcode & 0x0F00) >> 8] -= chip8 -> V[(opcode & 0x00F0) >> 4];
            break;

        case 0x0006:
            // Shifts VX to the right by 1, stores the least significant bit (LSB) of VX prior to the shift into VF
            // Vx >>= 1
            chip8 -> V[0x000F] = chip8 -> V[(opcode & 0x0F00) >> 8] & 0x01;  // Extract LSB of VX and store it in VF
            chip8 -> V[(opcode & 0x0F00) >> 8] >>= 1;  // Shift VX to the right
            break;

        case 0x0007:
            // Vx = Vy - Vx
            // VF is set to 1 if Vy >= Vx, 0 if Vy < Vx (underflow)
            if (chip8 -> V[(opcode & 0x00F0) >> 4] >= chip8 -> V[(opcode & 0x0F00) >> 8]) {
                chip8 -> V[0x000F] = 1;  // No underflow
            } else {
                chip8 -> V[0x000F] = 0;  // Underflow
            }
            chip8 -> V[(opcode & 0x0F00) >> 8] = chip8 -> V[(opcode & 0x00F0) >> 4] - chip8 -> V[(opcode & 0x0F00) >> 8];
            break;

        case 0x000E:
            // Shifts VX to the left by 1, then stores the MSB of VX into VF
            // Vx <<= 1
            // Check if the most significant bit (MSB) of VX is set before the shift
            chip8 -> V[0x000F] = (chip8 -> V[(opcode & 0x0F00) >> 8] & 0x0080) >> 7;  // MSB of VX before shift
            chip8 -> V[(opcode & 0x0F00) >> 8] <<= 1;  // Perform the left shift on VX
            break;

        }
        break;

    case 0x9000: // 0x9XY0
        // skips next instruction is VX does not equal VY
        if ((opcode & 0x0F00) != (opcode & 0x00F0)) {
            chip8 -> pc += 2;
        }
        break;

    case 0xA000: // 0xANNN
        // sets I to the address NNN
        chip8 -> I = opcode & 0x0FFF;
        break;

    case 0xB000: // 0xBNNN
        // jumps to the address NNN plus V0, PC = V0 + NNN
        chip8 -> pc = chip8 -> V[0] + (opcode & 0x0FFF);
        break;

    case 0xC000: // 0xCXNN
        // sets VX to the result of a bitwise AND operation on a random number (Typically: 0 to 255) and NN
        // Vx = rand() & NN
        chip8 -> V[(opcode & 0x0F00) >> 8] = (rand() % 256) & (opcode & 0x0F00); // ensures value is between 0x00 and 0xFF
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

    case 0xF000: // 0xFXNN
        switch (opcode & 0x00FF) {
        case 0x0007:
            // sets Vx to value of delay timer
            chip8 -> V[(opcode & 0x0F00) >> 8] = chip8 -> delay_timer;
            break;

        case 0x000A:
            // sets Vx to keypress
            break;

        case 0x0015:
            // set delay timer to Vx
            chip8 -> delay_timer = chip8 -> V[(opcode & 0x0F00) >> 8];
            break;

        case 0x0018:
            // set sound timer to Vx
            chip8 -> sound_timer = chip8 -> V[(opcode & 0x0F00) >> 8];
            break;

        case 0x001E:
            // adds Vx to I
            chip8 -> I = chip8 -> V[(opcode & 0x0F00) >> 8];
                break;

        case 0x0029:
            // sets I to the location of the sprite for the character in Vx, characters 0-F in 4x4 font
            // I = sprite_addr[Vx]
            break;

        case 0x0033:
            // Stores the binary-coded decimal representation of VX, with the hundreds digit in memory at location in I, the tens digit at location I+1, and the ones digit at location I+2
            break;

        case 0x0055:
            // Stores from V0 to VX (including VX) in memory, starting at address I
            // The offset from I is increased by 1 for each value written, but I itself is left unmodified
            break;

        case 0x0065:
            // Fills from V0 to VX (including VX) with values from memory, starting at address I
            // The offset from I is increased by 1 for each value read, but I itself is left unmodified
            break;
        }

        break;

    default:
        printf("Unknown opcode: 0x%04X\n", opcode);
        break;
    }
}
