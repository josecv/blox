#include "ZPiece.h"
#include "Grid.h"
#include "Frame.h"
#include "PieceType.h"

using namespace blox;

/* The centre of the ZPiece is the top right. */

void ZPiece::pieceLoop(std::function<bool (int, int)> func, int xCandidate,
                       int yCandidate) {
  if (!func(xCandidate, yCandidate)) {
    return;
  }
  if (!(_rotation % 2)) {
    if (!func(xCandidate - 1, yCandidate)) {
      return;
    } else if (!func(xCandidate, yCandidate + 1)) {
      return;
    }
    func(xCandidate + 1, yCandidate + 1);
  } else {
    if (!func(xCandidate, yCandidate - 1)) {
      return;
    } else if (!func(xCandidate - 1, yCandidate)) {
      return;
    }
    func(xCandidate - 1, yCandidate + 1);
  }
}

PieceType ZPiece::getType() {
  return PIECE_Z;
}
