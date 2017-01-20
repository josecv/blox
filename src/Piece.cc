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

