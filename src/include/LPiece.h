#ifndef BLOX_LPIECE_H
#define BLOX_LPIECE_H
#include "Piece.h"
#include <functional>

namespace blox {

/**
 * The L shaped piece.
 */
class LPiece : public Piece {
 protected:
  using Piece::Piece;
  PieceType getType();

  void pieceLoop(std::function<bool (int, int)> func, int xCandidate,
                 int yCandidate);
};

};

#endif /* BLOX_LPIECE_H */
