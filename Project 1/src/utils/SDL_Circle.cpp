#include "SDL_Circle.h"

SDL_Circle::SDL_Circle(int x, int y, int radius, SDL_Color color)
    : m_x(x), m_y(y), m_radius(radius), m_color(color) {}

void SDL_Circle::draw(SDL_Renderer* renderer) {
    if (renderer == nullptr) return;

    SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);

    int x = m_radius;
    int y = 0;
    int p = 1 - m_radius;

    while (x >= y) {
        // Draw horizontal lines to fill the circle
        SDL_RenderDrawLine(renderer, m_x - x, m_y + y, m_x + x, m_y + y);
        SDL_RenderDrawLine(renderer, m_x - x, m_y - y, m_x + x, m_y - y);
        SDL_RenderDrawLine(renderer, m_x - y, m_y + x, m_x + y, m_y + x);
        SDL_RenderDrawLine(renderer, m_x - y, m_y - x, m_x + y, m_y - x);

        y++;
        if (p <= 0) {
            p += 2 * y + 1;
        } else {
            x--;
            p += 2 * (y - x) + 1;
        }
    }
}
