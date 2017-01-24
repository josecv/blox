#include "NextPieceGrid.h"
#include "Frame.h"

using namespace blox;

bool NextPieceGrid::renderBlock(int xgrid, int ygrid, SDL_Renderer *renderer,
                                PieceType type) {
  SDL_Rect srcrect;
  SDL_Rect dstrect;
  srcrect.x = type * 40;
  srcrect.y = 0;
  srcrect.w = 40;
  srcrect.h = 40;
  dstrect.w = 40;
  dstrect.h = 40;
  dstrect.x = (xgrid * 40) + 10 + Frame::PREVIEW_X;
  dstrect.y = (ygrid * 40) + 10 + Frame::PREVIEW_Y;
  return (SDL_RenderCopy(renderer, _pieceTexture, &srcrect, &dstrect) == 0);
}
