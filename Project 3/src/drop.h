#ifndef DROP_H
#define DROP_H

#include <SDL2/SDL.h>
#include <random>

struct Particle {
    int x, y;
    int vx, vy;
    int life;
};

class Drop {
private:
    int m_size;
    int m_x, m_y, m_speed, m_life;

    std::vector<Particle> particles;

    void m_splatter();
    void m_initialize();

    bool m_splattered= false;

public:
    Drop();
    void update();
    void render(SDL_Renderer* renderer);
};

#endif
