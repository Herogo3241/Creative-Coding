#ifndef CELL_H
#define CELL_H

#include <SDL2/SDL.h>

class Cell {
    public:
        int m_x, m_y, m_size;
        bool isFilled = false;
    
        Cell(int x, int y, int size);
    
        void DrawOutline(SDL_Renderer* renderer);
        void DrawFilled(SDL_Renderer* renderer);
    
        bool Contains(int mouseX, int mouseY) {
            return (mouseX >= m_x && mouseX < m_x + m_size && 
                    mouseY >= m_y && mouseY < m_y + m_size);
        }
    };
    

#endif // CELL_H
