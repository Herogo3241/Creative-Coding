#include "grid.h"

Grid::Grid(int width, int height)
    : m_width(width), m_height(height) {
    
    // Create cells for the grid
    for (int x = 0; x < width; x += m_cellSize) {
        for (int y = 0; y < height; y += m_cellSize) {
            m_cells.emplace_back(x, y, m_cellSize);
        }
    }
}

// Draw the grid
void Grid::Draw(SDL_Renderer* renderer) {
    for (auto& cell : m_cells) {
        if (cell.isFilled)
            cell.DrawFilled(renderer); // Draw filled cells
        else
            cell.DrawOutline(renderer); // Draw empty cell outlines
    }
}

// Handle mouse click and toggle cell state
void Grid::HandleClick(int mouseX, int mouseY) {
    for (auto& cell : m_cells) {
        if (cell.Contains(mouseX, mouseY)) {  
            cell.isFilled = !cell.isFilled;  // Toggle cell state
            break;
        }
    }
}

// Get cell at specific coordinates
Cell* Grid::GetCell(int x, int y) {
    for (auto& cell : m_cells) {
        if (cell.m_x == x && cell.m_y == y) {
            return &cell;
        }
    }
    return nullptr;
}

// Count live neighbors for a given cell
int Grid::CountLiveNeighbors(Cell& cell) {
    int liveCount = 0;
    int offsets[] = {-m_cellSize, 0, m_cellSize};

    for (int dx : offsets) {
        for (int dy : offsets) {
            if (dx == 0 && dy == 0) continue;  // Skip the current cell

            Cell* neighbor = GetCell(cell.m_x + dx, cell.m_y + dy);
            if (neighbor && neighbor->isFilled) {
                liveCount++;
            }
        }
    }
    return liveCount;
}

// Update the grid based on Game of Life rules
void Grid::Update() {
    std::vector<bool> nextState(m_cells.size(), false);

    for (size_t i = 0; i < m_cells.size(); i++) {
        int liveNeighbors = CountLiveNeighbors(m_cells[i]);

        if (m_cells[i].isFilled) {
            nextState[i] = (liveNeighbors == 2 || liveNeighbors == 3); // Survives
        } else {
            nextState[i] = (liveNeighbors == 3); // Becomes alive
        }
    }

    // Apply the new state
    for (size_t i = 0; i < m_cells.size(); i++) {
        m_cells[i].isFilled = nextState[i];
    }
}
