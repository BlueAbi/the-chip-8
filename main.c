#include "chip8.h"

Chip8 myChip8;

int main(int argc, char **argv) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* texture = NULL;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <CHIP-8 ROM>\n", argv[0]);
        return 1;
    }

    // Set up render system and input with SDL. Initialize SDL's event handling system
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        // Outputs error if SDL fails to Initialize
        fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
        exit(1); // Exit program
    }

    setupGraphics(window, renderer, texture);

    // initialize system and load game into memory
    chip8_initialize(&myChip8);
    loadGame(argv[1], &myChip8);

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
        setKeys(&myChip8);
    }
    // Clean up SDL resources and exit
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();  // Quit SDL subsystems
    return 0;
}
