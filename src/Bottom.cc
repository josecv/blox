#include<string.h>
#include "Bottom.h"
#include <iostream>

using namespace blox;


Bottom::Bottom(Grid *grid) : _gridRenderer(grid) {
  memset(_grid, 0, sizeof(char) * INTERNAL_HEIGHT * Grid::GRID_WIDTH);
}

bool Bottom::collides(int xgrid, int ygrid) {
  ygrid = ygrid + NUMBER_GHOST;
  if (ygrid < 0) {
    return false;
  }
  return (_grid[ygrid][xgrid] & 0xF0) != 0;
}

void Bottom::place(int xgrid, int ygrid, PieceType piece) {
  ygrid = ygrid + NUMBER_GHOST;
  if (ygrid >= 0 && xgrid >= 0 && ygrid < INTERNAL_HEIGHT &&
      xgrid < Grid::GRID_WIDTH) {
    _grid[ygrid][xgrid] = 0xF0 | piece;
  }
}

bool Bottom::render(SDL_Renderer *renderer) {
  bool okay = true;
  for (int y = NUMBER_GHOST; y < INTERNAL_HEIGHT; y++) {
    for (int x = 0; x < Grid::GRID_WIDTH; x++) {
      if (_grid[y][x] & 0xF0) {
        PieceType piece = static_cast<PieceType>(_grid[y][x] & 0x0F);
        _gridRenderer->renderBlock(x, y - NUMBER_GHOST, renderer, piece);
      }
    }
  }
  return okay;
}

int Bottom::clearRows() {
  int cleared = 0;
  /* Won't ever clear more than 4 anyway. */
  int rows[4];
  for (int y = NUMBER_GHOST; y < INTERNAL_HEIGHT; y++) {
    bool clear = true;
    for (int x = 0; x < Grid::GRID_WIDTH; x++) {
      if (!(_grid[y][x] & 0xF0)) {
        clear = false;
        break;
      }
    }
    if (clear) {
      rows[cleared] = y;
      cleared++;
    }
  }
  /* Now time to push everything down */
  for (int i = 0; i < cleared; i++) {
    int row = rows[i];
    for (int y = row - 1; y >= 0; y--) {
      memcpy(_grid[y + 1], _grid[y], sizeof(char) * Grid::GRID_WIDTH);
      memset(_grid[y], 0, sizeof(char) * Grid::GRID_WIDTH);
    }
  }
  return cleared;
}

bool Bottom::hitsTop() {
  for (int y = 0; y < NUMBER_GHOST; y++) {
    for (int x = 0; x < Grid::GRID_WIDTH; x++) {
      if (_grid[y][x] & 0xF0) {
        return true;
      }
    }
  }
  return false;
}

void Bottom::reset() {
  memset(_grid, 0, sizeof(char) * INTERNAL_HEIGHT * Grid::GRID_WIDTH);
}
