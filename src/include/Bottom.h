#ifndef BLOX_BOTTOM_H
#define BLOX_BOTTOM_H
#include "Object.h"
#include "PieceType.h"

namespace blox {

/**
 * The bottom of the playing field, containing the pieces that
 * have fallen there.
 */
class Bottom : public Object {
 public:
  /**
   * Return whether the x, y position is hitting a piece on the bottom.
   * @param xgrid the x grid position
   * @param ygrid the y grid position
   * @return whether there's a collision
   */
  bool willCollide(int xgrid, int ygrid);

  /**
   * Place a block of the piecetype given at the location given.
   * @param xgrid the x grid position
   * @param ygrid the y grid position
   * @return whether there's a collision.
   */
  void place(int xgrid, int ygrid, PieceType piece);

  bool render(SDL_Renderer *renderer);
};

};

#endif /* BLOX_BOTTOM_H */
