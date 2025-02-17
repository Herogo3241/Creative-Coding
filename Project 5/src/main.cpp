#include <iostream>
#include <SDL2/SDL.h>
#include "grid.h"

const int width =  960;
const int height = 540;

int WinMain() {
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;

        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if(window == nullptr) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;

        SDL_Quit();

        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == nullptr) {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;

        SDL_DestroyWindow(window);
        SDL_Quit();

        return 1;
    }

    SDL_Event event;
    bool quit = false;

    Grid grid(width, height);
    bool start = false;

    while(!quit) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                quit = true;
            }else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX = event.button.x;
                int mouseY = event.button.y;
                grid.HandleClick(mouseX, mouseY);
            }else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_SPACE) { 
                    // grid.Update();
                    start = !start;
                }
            }
        }
        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(renderer);

        if(start){
            grid.Update();
        }

        grid.Draw(renderer);

        
        SDL_RenderPresent(renderer);
        SDL_Delay(8);
    }

    return 0;
}