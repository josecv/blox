#include "Piece.h"

using namespace blox;

Piece::Piece(Grid *gridRenderer, Uint32 timeToFall) : _gridRenderer(gridRenderer),
                                                      _timeToFall(timeToFall),
                                                      _xpos(2), _ypos(2), _rotation(0),
                                                      _timeLastFall(SDL_GetTicks()),
                                                      _leftPush(false), _rightPush(false),
                                                      _inRotation(false),
                                                      _timeRotation(SDL_GetTicks()) {

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
  /* We'll reuse the side movement velocity for the rotation velocity. */
  if (_inRotation && ((ticks - _timeRotation) >= SIDE_PUSH_VELOCITY)) {
    _rotation = (_rotation + 1) % 4;
    _inRotation = false;
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

void Piece::rotate() {
  if (!_inRotation) {
    _inRotation = true;
    _timeRotation = SDL_GetTicks();
  }
}

void Piece::resetCoordinates() {
  _xpos = 5;
  _ypos = 0;
}

void Piece::setGridRenderer(Grid *gridRenderer) {
  _gridRenderer = gridRenderer;
}
