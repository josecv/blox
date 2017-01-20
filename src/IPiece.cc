#include "IPiece.h"
#include "Grid.h"
#include "Frame.h"
#include "PieceType.h"

using namespace blox;

/* The centre of the IPiece is the second block from the bottom. */

bool IPiece::render(SDL_Renderer *renderer) {
  bool okay = true;
  if (!(_rotation % 2)) {
    for (int y = _ypos - 2, block = 0; block < 4; block++, y++) {
      okay = okay && renderBlock(_xpos, y, renderer, PIECE_I);
    }
  }

  return okay;
}

bool IPiece::checkLeft(int xCandidate) {
  return true;
}

bool IPiece::checkRight(int xCandidate) {
  return true;
}

bool IPiece::hitsFloor(int yCandidate, Bottom *bottom) {
  if ((yCandidate + 2) >= Grid::GRID_HEIGHT) {
    return true;
  }
  return false;
}
