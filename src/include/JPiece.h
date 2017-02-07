#ifndef BLOX_JPIECE_H
#define BLOX_JPIECE_H
#include "Piece.h"
#include <functional>

namespace blox {

/**
 * The J shaped piece.
 */
class JPiece : public Piece {
 protected:
  using Piece::Piece;
  PieceType getType();

  void pieceLoop(std::function<bool (int, int)> func, int xCandidate,
                 int yCandidate);
};

};

#endif /* BLOX_JPIECE_H */
