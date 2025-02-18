#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include <random>

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 540

const double PI = 3.14159265359;



bool running = true;
double df = -0.1; 

void HandleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            running = false; 
        }if (event.type == SDL_KEYDOWN){
            if(event.key.keysym.sym == SDLK_SPACE){
                df *= -1;
            }
        }
    }
}

void DrawSpiral(SDL_Renderer* renderer, int radius, double a_factor, double rotation){
    
    float r_new = 0.1 * radius * pow(a_factor,0);
    float prev_x = (r_new * cos(rotation)) + SCREEN_WIDTH / 2;
    
    float prev_y = (r_new * sin(rotation)) + SCREEN_HEIGHT / 2;

    for(float angle = 0; angle < 12 * PI; angle += 0.1){
        HandleEvents();
        r_new = 0.1 * radius * pow(a_factor,angle);
        float x = (r_new * cos(angle + rotation)) + SCREEN_WIDTH / 2;
        float y = (r_new * sin(angle + rotation)) + SCREEN_HEIGHT / 2;
        SDL_RenderDrawLineF(renderer, x, y, prev_x, prev_y);
        prev_x = x; prev_y = y;
    }

}




int WinMain()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Error Initializing SDL2");
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Golden Spiral", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

    double rotation = 0; 
    

    while (running)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        

        
        DrawSpiral(renderer, 20, 1.17, rotation);

        rotation += df;

        SDL_RenderPresent(renderer);

        HandleEvents(); 
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
