#include<string.h>
#include "Bottom.h"
#include <iostream>

using namespace blox;

Bottom::Bottom(Grid *grid) : _gridRenderer(grid) {
  memset(_grid, 0, sizeof(char) * Grid::GRID_HEIGHT * Grid::GRID_WIDTH);
}

bool Bottom::willCollide(int xgrid, int ygrid) {
  if (ygrid < 0) {
    return false;
  }
  return (_grid[ygrid][xgrid] & 0xF0) != 0;
}

void Bottom::place(int xgrid, int ygrid, PieceType piece) {
  _grid[ygrid][xgrid] = 0xF0 | piece;
}

bool Bottom::render(SDL_Renderer *renderer) {
  bool okay = true;
  for (int y = 0; y < Grid::GRID_HEIGHT; y++) {
    for (int x = 0; x < Grid::GRID_WIDTH; x++) {
      if (_grid[y][x] & 0xF0) {
        PieceType piece = static_cast<PieceType>(_grid[y][x] & 0x0F);
        _gridRenderer->renderBlock(x, y, renderer, piece);
      }
    }
  }
  return okay;
}

int Bottom::clearRows() {
  return 0;
}
