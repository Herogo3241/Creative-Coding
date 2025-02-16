#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include <random>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

const double PI = 3.14159265359;

std::random_device rd;
std::mt19937 gen(rd()); // Random number generator
std::uniform_int_distribution<int> colorDist(150, 255);

bool running = true; // Global flag to track if the program is running

void HandleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            running = false; // Stop drawing immediately if the user closes the window
        }
    }
}

void DrawFractal(SDL_Renderer *renderer, int x, int y, double angle, int length, int depth)
{
    if (!running || depth == 0 || length < 2) // Stop drawing if the user exits
        return;

    int n_x = x + static_cast<int>(length * cos(angle));
    int n_y = y + static_cast<int>(length * sin(angle));

    SDL_SetRenderDrawColor(renderer, static_cast<Uint8>(colorDist(gen)),
                           static_cast<Uint8>(colorDist(gen)),
                           static_cast<Uint8>(colorDist(gen)),
                           255);

    SDL_RenderDrawLine(renderer, x, y, n_x, n_y);
    SDL_RenderPresent(renderer);

    SDL_Delay(0.001); 

    HandleEvents(); // Process user input between drawing steps

    DrawFractal(renderer, n_x, n_y, angle - PI / 6, length * 0.75, depth - 1);
    DrawFractal(renderer, n_x, n_y, angle + PI / 6, length * 0.75, depth - 1);
}

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Error Initializing SDL2");
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Fractal - Recursive", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        SDL_Log("Error initializing window");
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        SDL_Log("Error initializing renderer");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    while (running)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        DrawFractal(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT, -PI / 2, 150, 10);

        SDL_RenderPresent(renderer);

        HandleEvents(); // Keep processing events while drawing
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
