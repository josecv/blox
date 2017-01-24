#ifndef BLOX_NEXT_PIECE_GRID_H
#define BLOX_NEXT_PIECE_GRID_H
#include "Grid.h"

namespace blox {

/**
 * The grid for rendering to the "next piece" preview.
 */
class NextPieceGrid : public Grid {
 public:
  virtual bool renderBlock(int xgrid, int ygrid, SDL_Renderer *renderer,
                           PieceType type);
};

};

#endif /* BLOX_NEXT_PIECE_GRID_H */
