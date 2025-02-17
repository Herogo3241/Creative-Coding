#ifndef WAVE_H
#define WAVE_H

#include <SDL2/SDL.h>
#include <random>

class Wave {
private:
    int m_width;
    int m_height;
    int m_waveHeight = 100;
    std::vector<int> m_permutation;
public:
    Wave(int width, int height);
    void render(SDL_Renderer* renderer);
};

#endif