#include <SDL2/SDL.h>
#include "drop.h"


const int DROP_COUNT = 30;


// for linux use main instead
int WinMain(int argc, char* argv[]){
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        SDL_Log("Error  Initialzing SDL2");
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Rain", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if(window == nullptr){
        SDL_Log("Window initializing Error");
        SDL_Quit();
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == nullptr){
        SDL_Log("Renderer initializing Error");
        SDL_DestroyWindow(window);
    }

    std::vector<Drop> drops(DROP_COUNT);


    SDL_Event event;
    bool running = true;
    
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }
    
        // Clear screen with black color
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    
        // Update and render the drop
        for(Drop& drop : drops){
            drop.update();
            drop.render(renderer);
        }
        
    
        // Present the renderer
        SDL_RenderPresent(renderer);
    
        // Delay for 16ms to cap the frame rate (approx. 60 FPS)
        SDL_Delay(16);
    }
    

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}