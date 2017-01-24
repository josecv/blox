#include <SDL.h>
#include "Grid.h"
#include "Frame.h"

using namespace blox;

bool Grid::renderBlock(int xgrid, int ygrid, SDL_Renderer *renderer,
                       PieceType type) {
  /* The only place where there isn't any bounds checking is when the
   * piece is only starting to fall off the top. In that case, the centre
   * may be lower than the highest point of the piece, so just don't
   * render any of that */
  if (ygrid < 0) {
    return true;
  }
  /* TODO: Can we take the srcrect elsewhere */
  SDL_Rect srcrect;
  SDL_Rect dstrect;
  srcrect.x = type * 40;
  srcrect.y = 0;
  srcrect.w = 40;
  srcrect.h = 40;
  dstrect.w = 40;
  dstrect.h = 40;
  dstrect.x = Grid::xGridToPixel(xgrid);
  dstrect.y = Grid::yGridToPixel(ygrid);
  return (SDL_RenderCopy(renderer, _pieceTexture, &srcrect, &dstrect) == 0);
}

void Grid::setPieceTexture(SDL_Texture *pieceTexture) {
  _pieceTexture = pieceTexture;
}

int Grid::xGridToPixel(int xpos) {
  return (xpos * 40) + Frame::LEFT_WIDTH;
}

int Grid::yGridToPixel(int ypos) {
  return (ypos * 40) + Frame::TOP_HEIGHT;
}
