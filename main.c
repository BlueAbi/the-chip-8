#include "chip8.h"

chip8 myChip8;

void setupGraphics();
void setupInput();
void drawGraphics();

int main(int argc, char **argv) {
    // Set up render system and input
    // setupGraphics();
    // setupInput();

    // initialize system and load game int memory
    myChip8.initialize();
    myChip8.loadGame();

    // emulation loop
    for (;;) {
        // emulate one cycle
        myChip8.emulateCycle();

        // if draw flag set, update the screen
        if (myChip8.drawFlag) {
            drawGraphics();
        }

        // Store key press state (press and release)
        myChip8.setKeys();
    }
    return 0;
}
