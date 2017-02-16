#include "TPiece.h"
#include "PieceType.h"

using namespace blox;

/* The centre of the T piece is the intersection */
void TPiece::pieceLoop(std::function<bool (int, int)> func, int xCandidate,
                       int yCandidate) {
  if (!func(xCandidate, yCandidate)) {
    return;
  }
  if (!(_rotation % 2)) {
    if (!func(xCandidate - 1, yCandidate)) {
      return;
    } else if (!func(xCandidate + 1, yCandidate)) {
      return;
    }
    func(xCandidate, yCandidate + ((_rotation ? 1 : -1)));
  } else {
    if (!func(xCandidate, yCandidate - 1)) {
      return;
    } else if (!func(xCandidate, yCandidate + 1)) {
      return;
    }
    func(xCandidate + ((_rotation == 1) ? 1 : -1), yCandidate);
  }
}

PieceType TPiece::getType() {
  return PIECE_T;
}
