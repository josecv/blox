#include<string.h>
#include "Bottom.h"

using namespace blox;

Bottom::Bottom(SDL_Texture *pieceTexture) : _pieceTexture(pieceTexture) {
  memset(_grid, 0, sizeof(char) * Grid::GRID_HEIGHT * Grid::GRID_WIDTH);
}

bool Bottom::willCollide(int xgrid, int ygrid) {
  return (_grid[ygrid][xgrid] & 0xF0) == 0;
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
        Grid::renderBlock(x, y, renderer, piece, _pieceTexture);
      }
    }
  }
  return okay;
}
