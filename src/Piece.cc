#include "Piece.h"
#include "Grid.h"

using namespace blox;

Piece::Piece(SDL_Texture *pieceTexture, Uint32 timeToFall) : _pieceTexture(pieceTexture),
                                                             _timeToFall(timeToFall),
                                                             _xpos(5), _ypos(0), _rotation(0),
                                                             _timeLastFall(SDL_GetTicks()) {

}

bool Piece::fall(Bottom *bottom) {
  Uint32 ticks = SDL_GetTicks();
  if ((ticks - _timeLastFall) >= _timeToFall) {
    _timeLastFall = ticks;
    _ypos++;
    return hitsFloor(_ypos, bottom);
  }
  return false;
}

bool Piece::renderBlock(int xgrid, int ygrid, SDL_Renderer *renderer,
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
