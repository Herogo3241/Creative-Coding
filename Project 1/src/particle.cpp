#include "particle.h"

Particle::Particle(int x, int y, int size, SDL_Color color) 
    : m_x(x), m_y(y), m_px(x), m_py(y), m_size(size), m_color(color) {
    srand(time(nullptr));  // This should ideally be done once in main(), not here
    randomizeVelocity();
}

void Particle::randomizeVelocity() {
    // Random velocity between -2 and 2
    m_vx = (rand() % 5) - 2; 
    m_vy = (rand() % 5) - 2;
}

void Particle::update() {
    // Store previous position
    m_px = m_x;
    m_py = m_y;

    // Update position
    m_x += m_vx;
    m_y += m_vy;

    randomizeVelocity();  // Update velocity

    // Keep within screen bounds (800x600 example)
    if (m_x - m_size < 0 || m_x + m_size > 800) {
        m_vx = -m_vx;
        m_x = std::max(m_size, std::min(m_x, 800 - m_size));  // Keep inside bounds
    }
    if (m_y - m_size < 0 || m_y + m_size > 600) {
        m_vy = -m_vy;
        m_y = std::max(m_size, std::min(m_y, 600 - m_size));  // Keep inside bounds
    }
}

void Particle::render(SDL_Renderer* renderer) {
    // Draw trail (line between previous and current position)
    // SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, 255);
    // SDL_RenderDrawLine(renderer, m_px, m_py, m_x, m_y);

    // Draw particle (circle)
    SDL_Circle particle(m_x, m_y, m_size, m_color);
    particle.draw(renderer);
}

