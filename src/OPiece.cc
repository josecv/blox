#include "OPiece.h"
#include "Grid.h"
#include "Frame.h"
#include "PieceType.h"

using namespace blox;

/* The centre of the OPiece is its top right */

void OPiece::pieceLoop(std::function<bool (int, int)> func, int xCandidate,
                       int yCandidate) {
  for (int x = xCandidate; x < xCandidate + 2; x++) {
    for (int y = yCandidate; y < yCandidate + 2; y++) {
      if (!func(x, y)) {
        return;
      }
    }
  }
}

PieceType OPiece::getType() {
  return PIECE_O;
}
