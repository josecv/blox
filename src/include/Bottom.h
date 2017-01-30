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
   * The way this is implemented is by holding a grid of all the various
   * pieces that have fallen. We keep an extra 4 ghost rows at the top to know
   * if the player runs the risk of dying; if any are populated at the time
   * that hitsTop() gets called, we will return true.
   */
  /**
   * CTOR.
   * @param pieceTexture the texture for the blocks.
   */
  Bottom(Grid *grid);

  /**
   * Return whether the x, y position contains a block.
   * @param xgrid the x grid position
   * @param ygrid the y grid position
   * @return whether there's already a block there
   */
  bool collides(int xgrid, int ygrid);

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

  /**
   * Return true iff there's a piece at the very top (thus losing the game).
   */
  bool hitsTop();

  bool render(SDL_Renderer *renderer);

 private:
  /**
   * How many ghost rows are we keeping.
   */
  const static int NUMBER_GHOST = 4;

  /**
   * The height of the internal grid, counting all 4 ghost rows.
   */
  const static int INTERNAL_HEIGHT = Grid::GRID_HEIGHT + NUMBER_GHOST;

  /**
   * The renderer for the grid.
   */
  Grid *_gridRenderer;

  /**
   * The grid containing all the block data.
   * The most significant halfbyte is turned on if there's a block,
   * the least significant halfbyte indicates its colour.
   */
  Uint8 _grid[INTERNAL_HEIGHT][Grid::GRID_WIDTH];
};

};

#endif /* BLOX_BOTTOM_H */
