#include "LPiece.h"
#include "Grid.h"
#include "Frame.h"
#include "PieceType.h"

using namespace blox;

/* The centre of the LPiece is the intersection */

void LPiece::pieceLoop(std::function<bool (int, int)> func, int xCandidate,
                       int yCandidate) {
  if (!func(xCandidate, yCandidate)) {
    return;
  }
  switch (_rotation) {
    case 0:
      if (!func(xCandidate + 1, yCandidate)) {
        return;
      } else if (!func(xCandidate, yCandidate - 1)) {
        return;
      }
      func(xCandidate, yCandidate - 2);
      break;
    case 1:
      if (!func(xCandidate, yCandidate + 1)) {
        return;
      } else if (!func(xCandidate + 1, yCandidate)) {
        return;
      }
      func(xCandidate + 2, yCandidate);
      break;
    case 2:
      if (!func(xCandidate - 1, yCandidate)) {
        return;
      } else if (!func(xCandidate, yCandidate + 1)) {
        return;
      }
      func(xCandidate, yCandidate + 2);
      break;
    case 3:
      if (!func(xCandidate, yCandidate - 1)) {
        return;
      } else if (!func(xCandidate - 1, yCandidate)) {
        return;
      }
      func(xCandidate - 2, yCandidate);
      break;
  }
}

PieceType LPiece::getType() {
  return PIECE_L;
}
