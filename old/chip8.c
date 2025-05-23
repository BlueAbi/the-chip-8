// chip8.c
#include "chip8.h"
#include <string.h>

void chip8_initialize(struct Chip8 *chip) {
    memset(chip, 0, sizeof(struct Chip8));
    chip->pc = 0x200;  // Programs start at memory location 0x200
}
