#ifndef BLOX_BOTTOM_H
#define BLOX_BOTTOM_H
#include "Object.h"

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

  bool render(SDL_Renderer *renderer);
};

};

#endif /* BLOX_BOTTOM_H */
