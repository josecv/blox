#ifndef BLOX_SPIECE_H
#define BLOX_SPIECE_H
#include "Piece.h"
#include <functional>

namespace blox {

/**
 * The S shaped piece.
 */
class SPiece : public Piece {
 protected:
  using Piece::Piece;
  PieceType getType();

  void pieceLoop(std::function<bool (int, int)> func, int xCandidate,
                 int yCandidate);
};

};

#endif /* BLOX_SPIECE_H */
