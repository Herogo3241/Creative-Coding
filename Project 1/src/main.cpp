#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <random>
#include "Particle.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int NUM_PARTICLES = 100;

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "Error Initializing SDL2" << std::endl;
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Brownian Motion",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cerr << "Error Creating Window" << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cerr << "Error Creating Renderer" << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    std::random_device rd;
    std::mt19937 gen(rd()); // Random number generator
    std::uniform_int_distribution<int> xDist(0, SCREEN_WIDTH - 1);
    std::uniform_int_distribution<int> yDist(0, SCREEN_HEIGHT - 1);
    std::uniform_int_distribution<int> colorDist(150, 255); // Random color range

    std::vector<Particle> particles;
    for (int i = 0; i < NUM_PARTICLES; i++)
    {
        int x = xDist(gen); // Random X
        int y = yDist(gen); // Random Y

        // Generate random RGB color
        SDL_Color color = {static_cast<Uint8>(colorDist(gen)),
                           static_cast<Uint8>(colorDist(gen)),
                           static_cast<Uint8>(colorDist(gen)),
                           255}; // Full opacity

        particles.emplace_back(x, y, 1, color);
    }

    bool running = true;
    SDL_Event event;
    bool showPath = false;
    while (running)
    {
        // Event handling
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN){
                switch(event.key.keysym.sym){
                    case SDLK_p:
                        showPath = !showPath;
                        break;
                }
            }
        }

        // Update particles
        for (auto &particle : particles)
        {
            particle.update();
        }

        if(!showPath){
            // Clear screen
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
            SDL_RenderClear(renderer);
        }
        // Render particles
        for (auto &particle : particles)
        {
            particle.render(renderer);
        }

        // Present the updated frame
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // Delay for ~60 FPS
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
