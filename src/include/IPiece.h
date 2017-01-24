#ifndef BLOX_LPIECE_H
#define BLOX_LPIECE_H
#include "Piece.h"

namespace blox {

/**
 * The I shaped piece (the long one).
 */
class IPiece : public Piece {
 protected:
  using Piece::Piece;

  bool render(SDL_Renderer *renderer);

  bool checkLeft(int xCandidate);

  bool checkRight(int xCandidate);

  bool hitsFloor(int yCandidate, Bottom *bottom);

  void place(Bottom *bottom);

 private:
  /**
   * Return true if this is oriented vertically, else false.
   * @return true if vertical.
   */
  bool isVertical();
};

};

#endif
