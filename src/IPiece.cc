#include "IPiece.h"
#include "Grid.h"
#include "Frame.h"
#include "PieceType.h"
#include <iostream>

using namespace blox;

/* The centre of the IPiece is the second block from the bottom. */

bool IPiece::render(SDL_Renderer *renderer) {
  bool okay = true;
  if (isVertical()) {
    for (int y = _ypos - 2, block = 0; block < 4; block++, y++) {
      okay = okay && _gridRenderer->renderBlock(_xpos, y, renderer, PIECE_I);
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
  if (isVertical()) {
    if ((yCandidate + 2) >= Grid::GRID_HEIGHT) {
      return true;
    }
    for (int y = yCandidate - 2, block = 0; block < 4; block++, y++) {
      if (bottom->willCollide(_xpos, y)) {
        return true;
      }
    }
  }
  return false;
}

void IPiece::place(Bottom *bottom) {
  if (isVertical()) {
    for (int y = _ypos - 2, block = 0; block < 4; block++, y++) {
      bottom->place(_xpos, y, PIECE_I);
    }
  }
}

bool IPiece::isVertical() {
  return (!(_rotation % 2));
}

