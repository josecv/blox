#ifndef BLOX_UTIL_H
#define BLOX_UTIL_H
#include "PieceType.h"

namespace blox {

/**
 * A class with some utility functions for managing the grid.
 */
class Grid {
 public:
  /**
   * The width of the grid.
   */
  static const int GRID_WIDTH = 10;

  /**
   * The height of the grid.
   */
  static const int GRID_HEIGHT = 20;

  /**
   * Convert the x grid position given to a pixel position.
   * @param xpos the x position
   * @return the pixel position
   */
  static int xGridToPixel(int xpos);
  /**
   * Convert the y grid position given to a pixel position.
   * @param ypos the y position
   * @return the pixel position
   */
  static int yGridToPixel(int ypos);

  /**
   * Render a block to the location given.
   * @param xgrid the x grid location.
   * @param ygrid the y grid location
   * @param renderer the renderer
   * @param type the piece type.
   * @return whether it succeeded
   */
  static bool renderBlock(int xgrid, int ygrid, SDL_Renderer *renderer,
                          PieceType type, SDL_Texture *pieceTexture);
};

};

#endif /* BLOX_UTIL_H */
