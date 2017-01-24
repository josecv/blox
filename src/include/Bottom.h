#ifndef BLOX_BOTTOM_H
#define BLOX_BOTTOM_H
#include "Object.h"
#include "PieceType.h"
#include "Grid.h"

namespace blox {

/**
 * The bottom of the playing field, containing the pieces that
 * have fallen there.
 */
class Bottom : public Object {
 public:
  /**
   * CTOR.
   * @param pieceTexture the texture for the blocks.
   */
  Bottom(Grid *grid);

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

  /**
   * Clear any rows that have been filled, and drop everything down
   * accordingly.
   * @return the number of cleared rows.
   */
  int clearRows();

  bool render(SDL_Renderer *renderer);

 private:
  /**
   * The renderer for the grid.
   */
  Grid *_gridRenderer;

  /**
   * The grid containing all the block data.
   * The most significant halfbyte is turned on if there's a block,
   * the least significant halfbyte indicates its colour.
   */
  Uint8 _grid[Grid::GRID_HEIGHT][Grid::GRID_WIDTH];
};

};

#endif /* BLOX_BOTTOM_H */
