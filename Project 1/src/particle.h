#ifndef PARTICLE_H
#define PARTICLE_H


#include <SDL2/SDL.h>
#include <iostream>
#include "utils/SDL_Circle.h"


class Particle {
private:
    int m_size;
    int m_x, m_y;
    int m_vx, m_vy;
    SDL_Color m_color;
    int m_px, m_py;

    void randomizeVelocity();




public:
    Particle(int x, int y, int size, SDL_Color color);
    
    int getX() { return m_x; }
    int getY() { return m_y; }
    void setPos(int x, int y) { m_x = x; m_y = y;}

    void update();
    void render(SDL_Renderer* renderer);
};

#endif
