#include "IPiece.h"
#include "Grid.h"
#include "Frame.h"
#include "PieceType.h"

using namespace blox;

/* The centre of the IPiece is the second block from the bottom. */

bool IPiece::render(SDL_Renderer *renderer) {
  bool okay = true;
  if (isVertical()) {
    for (int y = _ypos - 2, block = 0; block < 4; block++, y++) {
      okay = okay && Grid::renderBlock(_xpos, y, renderer, PIECE_I, _pieceTexture);
    }
  } else {
    /* XXX */
  }

  return okay;
}

bool IPiece::checkLeft(int xCandidate) {
  if (isVertical()) {
    return xCandidate >= 0;
  }
  /* XXX */
  return true;
}

bool IPiece::checkRight(int xCandidate) {
  if (isVertical()) {
    return xCandidate < Grid::GRID_WIDTH;
  }
  return true;
}

bool IPiece::hitsFloor(int yCandidate, Bottom *bottom) {
  if ((yCandidate + 2) >= Grid::GRID_HEIGHT) {
    return true;
  }
  return false;
}

bool IPiece::isVertical() {
  return (!(_rotation % 2));
}
