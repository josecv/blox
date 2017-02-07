#ifndef BLOX_OPIECE_H
#define BLOX_OPIECE_H
#include "Piece.h"
#include <functional>

namespace blox {

/**
 * The O shaped piece.
 */
class OPiece : public Piece {
 protected:
  using Piece::Piece;
  PieceType getType();

  void pieceLoop(std::function<bool (int, int)> func, int xCandidate,
                 int yCandidate);
};

};

#endif /* BLOX_OPIECE_H */
