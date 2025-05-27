#include <time.h>
#include <SDL3/SDL.h>
#include <stdbool.h>
#include "chip8.h"

#define CYCLES_PER_SECOND
#define TIMER_HZ 60

Chip8 myChip8;

void setupGraphics();
void setupInput();
void drawGraphics();

int main(int argc, char **argv) {
    // Set up render system and input
    // setupGraphics();
    // setupInput();

    // initialize system and load game into memory
    chip8_initialize(&myChip8);
    myChip8.loadGame();

    // emulation loop
    for (;;) {
        // emulate one cycle
        emulateCycle(&myChip8);

        // if draw flag set, update the screen
        if (myChip8.drawFlag) {
            drawGraphics(&myChip8); // Pass chip8 to drawGraphics
            myChip8.drawFlag = false; // Reset drawFlag after drawing
        }

        // Store key press state (press and release)
        myChip8.setKeys();
    }
    return 0;
}
