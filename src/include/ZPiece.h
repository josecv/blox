#ifndef BLOX_ZPIECE_H
#define BLOX_ZPIECE_H
#include "Piece.h"
#include <functional>

namespace blox {

/**
 * The Z shaped piece.
 */
class ZPiece : public Piece {
 protected:
  using Piece::Piece;
  PieceType getType();

  void pieceLoop(std::function<bool (int, int)> func, int xCandidate,
                 int yCandidate);
};

};

#endif /* BLOX_JPIECE_H */
