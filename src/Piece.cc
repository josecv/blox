#include "Piece.h"
#include "Grid.h"

using namespace blox;

Piece::Piece(SDL_Texture *pieceTexture, Uint32 timeToFall) : _pieceTexture(pieceTexture),
                                                             _timeToFall(timeToFall),
                                                             _xpos(5), _ypos(0), _rotation(0),
                                                             _timeLastFall(SDL_GetTicks()),
                                                             _leftPush(false), _rightPush(false) {

}

bool Piece::fall(Bottom *bottom) {
  Uint32 ticks = SDL_GetTicks();
  /* Deal with a side movement first */
  if ((_leftPush || _rightPush) &&
      ((ticks - _timeSidePush) >= SIDE_PUSH_VELOCITY)) {
    if (_leftPush && checkLeft(_xpos - 1)) {
      _xpos--;
    } else if (_rightPush && checkRight(_xpos + 1)) {
      _xpos++;
    }
    _leftPush = false;
    _rightPush = false;
  }
  if ((ticks - _timeLastFall) >= _timeToFall) {
    _timeLastFall = ticks;
    _ypos++;
    return hitsFloor(_ypos, bottom);
  }
  return false;
}

void Piece::pushLeft() {
  /* If we're already pushing, we're not gonna reset the counter
   * or the piece will go faster than its velocity */
  if (!_leftPush && !_rightPush) {
    _leftPush = true;
    _timeSidePush = SDL_GetTicks();
  }
}

void Piece::pushRight() {
  if (!_leftPush && !_rightPush) {
    _rightPush = true;
    _timeSidePush = SDL_GetTicks();
  }
}
