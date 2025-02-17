#include "drop.h"
#include <algorithm>



std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dist_y(-100, -50);
std::uniform_int_distribution<int> dist_x(0, 800);
std::uniform_int_distribution<int> dist_life(100, 580);
std::uniform_int_distribution<int> dist_speed(4, 10);
std::uniform_int_distribution<int> dist_size(15, 20);
std::uniform_int_distribution<int> dist_particle_vx(-3, 3);
std::uniform_int_distribution<int> dist_particle_vy(-2, -1);
std::uniform_int_distribution<int> dist_particle_life(10, 15);

Drop::Drop()
{
    m_initialize();
}

void Drop::update() {
    if (!m_splattered) {
        m_y += m_speed;
        m_speed += 0.5;

        if (m_y > m_life) {
            m_splatter();
        }
    } else {
        // Update particles
        for (auto& p : particles) {
            p.x += p.vx;
            p.y += p.vy;
            p.life--;
        }

        // Remove dead particles
        particles.erase(std::remove_if(particles.begin(), particles.end(),
                                       [](const Particle& p) { return p.life <= 0; }),
                        particles.end());

        // Reset drop when particles disappear
        if (particles.empty()) {
            m_splattered = false;
            m_initialize();
        }
    }
}

void Drop::m_initialize()
{
    m_x = dist_x(gen);
    m_y = dist_y(gen);
    m_speed = dist_speed(gen);
    m_life = dist_life(gen);
    m_size = dist_size(gen);
}

void Drop::m_splatter() {
    m_splattered = true;
    particles.clear();

    for (int i = 0; i < 3; i++) {  
        Particle p;
        p.x = m_x;
        p.y = m_life;
        p.vx = dist_particle_vx(gen);
        p.vy = dist_particle_vy(gen);
        p.life = dist_particle_life(gen);
        particles.push_back(p);
    }
}

void Drop::render(SDL_Renderer* renderer) {
    if (!m_splattered) {
        SDL_Rect rect = { m_x, m_y, 1, m_size };
        SDL_SetRenderDrawColor(renderer, 0, 120, 255, 255); // Deep water blue
        SDL_RenderFillRect(renderer, &rect);
    } else {
        // SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); 
        for (const auto& p : particles) {
            SDL_Rect particleRect = { p.x, p.y, 1, 2 }; 
            SDL_RenderFillRect(renderer, &particleRect);
        }
    }
}
