#ifndef SDL_CIRCLE_H
#define SDL_CIRCLE_H


#include <SDL2/SDL.h>

class SDL_Circle{
private:
    int m_x, m_y;
    int m_radius;
    SDL_Color m_color;

public:
    SDL_Circle(int x, int y, int radius, SDL_Color color);
    void draw(SDL_Renderer* renderer);

};

#endif
