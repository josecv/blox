#ifndef BLOX_TPIECE_H
#define BLOX_TPIECE_H
#include <functional>
#include "Piece.h"

namespace blox {

/**
 * The T shaped piece.
 */
class TPiece : public Piece {
 protected:
  using Piece::Piece;
  PieceType getType();

  void pieceLoop(std::function<bool (int, int)> func, int xCandidate,
                 int yCandidate);
};

};

#endif
