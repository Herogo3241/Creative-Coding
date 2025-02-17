#ifndef GRID_H
#define GRID_H

#include <vector>
#include "cell.h"

class Grid {
public:
    Grid(int width, int height);
    void Draw(SDL_Renderer* renderer);

    void HandleClick(int mouseX, int mouseY);

    

    void Update();

private:
    int m_width, m_height, m_cellSize = 20;
    std::vector<Cell> m_cells;

    int CountLiveNeighbors(Cell &cell);
    Cell *GetCell(int x, int y);
};

#endif // GRID_H
