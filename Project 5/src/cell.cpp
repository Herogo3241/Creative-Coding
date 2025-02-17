#include "cell.h"

Cell::Cell(int x, int y, int size)
    : m_x(x), m_y(y), m_size(size) {}

void Cell::DrawOutline(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 200, 120, 120, 255);  
    SDL_RenderDrawLine(renderer, m_x, m_y, m_x + m_size, m_y); 
    SDL_RenderDrawLine(renderer, m_x, m_y, m_x, m_y + m_size); 
    SDL_RenderDrawLine(renderer, m_x + m_size, m_y, m_x + m_size, m_y + m_size); 
    SDL_RenderDrawLine(renderer, m_x, m_y + m_size, m_x + m_size, m_y + m_size); 
}

void Cell::DrawFilled(SDL_Renderer* renderer) {
    SDL_Rect rect = { m_x, m_y, m_size, m_size };
    SDL_SetRenderDrawColor(renderer, 180, 75, 60, 255);  
    SDL_RenderFillRect(renderer, &rect);
}
