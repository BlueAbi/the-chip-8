#include <stdio.h>
#include "chip8.h"

int main()
{
    struct Chip8 chip;
    chip8_initialize(&chip);

    printf("CHIP-8 initialized. \n");
    printf("Program counter starts at: 0x%X\n", chip.pc);

    return 0;
}
