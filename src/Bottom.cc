#include<string.h>
#include "Bottom.h"
#include <iostream>

using namespace blox;


Bottom::Bottom(Grid *grid) : _gridRenderer(grid), _paused(false) {
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
    if (shouldRenderRow(y)) {
      for (int x = 0; x < Grid::GRID_WIDTH; x++) {
        if (_grid[y][x] & 0xF0) {
          PieceType piece = static_cast<PieceType>(_grid[y][x] & 0x0F);
          _gridRenderer->renderBlock(x, y - NUMBER_GHOST, renderer, piece);
        }
      }
    }
  }
  return okay;
}

int Bottom::clearRows() {
  _rowClear.cleared = 0;
  _rowClear.step = 0;
  _rowClear.timeLastStep = SDL_GetTicks();
  for (int y = NUMBER_GHOST; y < INTERNAL_HEIGHT; y++) {
    bool clear = true;
    for (int x = 0; x < Grid::GRID_WIDTH; x++) {
      if (!(_grid[y][x] & 0xF0)) {
        clear = false;
        break;
      }
    }
    if (clear) {
      _rowClear.rows[_rowClear.cleared] = y;
      _rowClear.cleared++;
    }
  }
  _paused = (_rowClear.cleared > 0);
  return _rowClear.cleared;
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

void Bottom::removeClearedRows() {
  for (int i = 0; i < _rowClear.cleared; i++) {
    int row = _rowClear.rows[i];
    for (int y = row - 1; y >= 0; y--) {
      memcpy(_grid[y + 1], _grid[y], sizeof(char) * Grid::GRID_WIDTH);
      memset(_grid[y], 0, sizeof(char) * Grid::GRID_WIDTH);
    }
  }
  _paused = false;
}

bool Bottom::shouldRenderRow(int row) {
  if (!_paused) {
    return true;
  }
  Uint32 ticks = SDL_GetTicks();
  if ((ticks - _rowClear.timeLastStep) >= ANIMATION_DELAY) {
    _rowClear.timeLastStep = ticks;
    _rowClear.step++;
    if (_rowClear.step >= ANIMATION_STEPS) {
      removeClearedRows();
      return true;
    }
  }
  if (_rowClear.step % 2) {
    return true;
  }
  return !(_rowClear.rows[0] == row
        || _rowClear.rows[1] == row
        || _rowClear.rows[2] == row
        || _rowClear.rows[3] == row);
}
