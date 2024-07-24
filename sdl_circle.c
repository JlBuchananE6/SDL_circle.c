#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

// Function to draw a circle
void draw_circle(SDL_Renderer *renderer, int x, int y, int radius) {
    // This function is defined to draw a circle. It takes an SDL renderer, the circle's center coordinates (x, y), and the circle's radius as parameters.

    int offsetX, offsetY, d;
    int status;

    offsetX = 0;
    offsetY = radius;
    d = radius - 1;
    status = 0;

    // offsetX and offsetY: These variables will help calculate the points of the circle.
    // d: This is a decision parameter to control the drawing of the circle.
    // status: This variable will track if there was an error in drawing points.

    while (offsetY >= offsetX) {
        // This loop draws the points of the circle using the midpoint circle algorithm.

        status += SDL_RenderDrawPoint(renderer, x + offsetX, y + offsetY);
        status += SDL_RenderDrawPoint(renderer, x + offsetY, y + offsetX);
        status += SDL_RenderDrawPoint(renderer, x - offsetX, y + offsetY);
        status += SDL_RenderDrawPoint(renderer, x - offsetY, y + offsetX);
        status += SDL_RenderDrawPoint(renderer, x + offsetX, y - offsetY);
        status += SDL_RenderDrawPoint(renderer, x + offsetY, y - offsetX);
        status += SDL_RenderDrawPoint(renderer, x - offsetX, y - offsetY);
        status += SDL_RenderDrawPoint(renderer, x - offsetY, y - offsetX);

        // These lines draw 8 symmetrical points around the circle’s center.

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2 * offsetX) {
            d -= 2 * offsetX + 1;
            offsetX += 1;
        } else if (d < 2 * (radius - offsetY)) {
            d += 2 * offsetY - 1;
            offsetY -= 1;
        } else {
            d += 2 * (offsetY - offsetX - 1);
            offsetY -= 1;
            offsetX += 1;
        }

        // These lines decide the next point to draw based on the midpoint circle algorithm.
    }
}

int main() {
    // This is the entry point of the program.

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // Initializes the SDL library for video functions.

    SDL_Window *window = SDL_CreateWindow("SDL Circle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Creates a window with the title "SDL Circle", centered on the screen, with a size of 800x600 pixels.

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Creates a renderer for the window, which will handle drawing.

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    // Sets the drawing color to white (RGBA: 255, 255, 255, 255) and clears the window with this color.
    
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    draw_circle(renderer, 400, 300, 100);
    // Sets the drawing color to red (RGBA: 255, 0, 0, 255) and calls the draw_circle function to draw a circle with a center at (400, 300) and a radius of 100 pixels.

    SDL_RenderPresent(renderer);
    // Updates the window with the drawn content.

    SDL_Delay(5000);
    // Pauses the program for 10000 milliseconds (5 seconds) so you can see the window.

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    // Cleans up by destroying the renderer, destroying the window, and quitting SDL.

    return 0;
    // Returns 0 to indicate that the program ended successfully.
}

