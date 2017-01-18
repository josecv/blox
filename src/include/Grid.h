#ifndef BLOX_UTIL_H
#define BLOX_UTIL_H

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
};

};

#endif /* BLOX_UTIL_H */
