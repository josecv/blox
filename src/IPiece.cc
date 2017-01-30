#include "IPiece.h"
#include "Grid.h"
#include "Frame.h"
#include "PieceType.h"
#include <iostream>

using namespace blox;

/* The centre of the IPiece is the second block from the bottom. */

bool IPiece::isVertical() {
  return (!(_rotation % 2));
}

void IPiece::pieceLoop(std::function<bool (int, int)> func, int xCandidate,
                       int yCandidate) {
  if (isVertical()) {
    for (int y = yCandidate - 2; y <= yCandidate + 1; y++) {
      if (!func(xCandidate, y)) {
        return;
      }
    }
  } else {
    for (int x = xCandidate - 2; x <= xCandidate + 1; x++) {
      if (!func(x, yCandidate)) {
        return;
      }
    }
  }
}

PieceType IPiece::getType() {
  return PIECE_I;
}
