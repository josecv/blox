#ifndef BLOX_LPIECE_H
#define BLOX_LPIECE_H
#include "Piece.h"
#include <functional>

namespace blox {

/**
 * The I shaped piece (the long one).
 */
class IPiece : public Piece {
 protected:
  using Piece::Piece;
  PieceType getType();

  void pieceLoop(std::function<bool (int, int)> func, int xCandidate,
                 int yCandidate);

 private:
  /**
   * Return true if this is oriented vertically, else false.
   * @return true if vertical.
   */
  bool isVertical();
};

};

#endif /* BLOX_LPIECE_H */
