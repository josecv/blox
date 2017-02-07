#include "Piece.h"

using namespace blox;

Piece::Piece(Grid *gridRenderer, Uint32 timeToFall) : _gridRenderer(gridRenderer),
                                                      _timeToFall(timeToFall),
                                                      _xpos(2), _ypos(2), _rotation(0),
                                                      _timeLastFall(SDL_GetTicks()),
                                                      _leftPush(false), _rightPush(false),
                                                      _inRotation(false), _hardDrop(false),
                                                      _timeRotation(SDL_GetTicks()),
                                                      _timeHardDrop(SDL_GetTicks()) {

}

bool Piece::fall(Bottom *bottom) {
  Uint32 ticks = SDL_GetTicks();
  /* Deal with a side movement first */
  if ((_leftPush || _rightPush) &&
      ((ticks - _timeSidePush) >= SIDE_PUSH_VELOCITY)) {
    if (_leftPush && checkLeft(_xpos - 1, bottom)) {
      _xpos--;
    } else if (_rightPush && checkRight(_xpos + 1, bottom)) {
      _xpos++;
    }
    _leftPush = false;
    _rightPush = false;
  }
  /* We'll reuse the side movement velocity for the rotation velocity. */
  if (_inRotation && ((ticks - _timeRotation) >= SIDE_PUSH_VELOCITY)) {
    int oldRotation = _rotation;
    _rotation = (_rotation + 1) % 4;
    /* Make sure the rotation is sound. If it isn't revert it */
    if (!(checkLeft(_xpos, bottom) &&
          checkRight(_xpos, bottom) &&
          !hitsFloor(_ypos, bottom))) {
      _rotation = oldRotation;
    }
    _inRotation = false;
  }
  if (_hardDrop && ((ticks - _timeHardDrop) >= SIDE_PUSH_VELOCITY)) {
    /* Time for the hard drop bby */
    while (!hitsFloor(_ypos, bottom)) {
      _ypos++;
    }
    return true;
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

void Piece::hardDrop() {
  if (!_hardDrop) {
    _hardDrop = true;
    _timeHardDrop = SDL_GetTicks();
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

bool Piece::render(SDL_Renderer *renderer) {
  bool okay = true;
  pieceLoop([&] (int x, int y) {
    okay = okay && _gridRenderer->renderBlock(x, y, renderer, getType());
    return true;
  });

  return okay;
}

void Piece::pieceLoop(std::function<bool (int, int)> func) {
  pieceLoop(func, _xpos, _ypos);
}

bool Piece::hitsFloor(int yCandidate, Bottom *bottom) {
  bool willHit = false;
  pieceLoop([&] (int x, int y) {
    if ((y + 1 >= Grid::GRID_HEIGHT) ||
        bottom->collides(x, y + 1)) {
      willHit = true;
      return false;
    }
    return true;
  }, _xpos, yCandidate);
  return willHit;
}

void Piece::place(Bottom *bottom) {
  pieceLoop([&] (int x, int y) {
    bottom->place(x, y, getType());
    return true;
  });
}

bool Piece::checkLeft(int xCandidate, Bottom *bottom) {
  bool okay = true;
  pieceLoop([&] (int x, int y) {
    if (x < 0 || bottom->collides(x, y)) {
      okay = false;
      return false;
    }
    return true;
  }, xCandidate, _ypos);
  return okay;
}

bool Piece::checkRight(int xCandidate, Bottom *bottom) {
  bool okay = true;
  pieceLoop([&] (int x, int y) {
    if (x >= Grid::GRID_WIDTH || bottom->collides(x, y)) {
      okay = false;
      return false;
    }
    return true;
  }, xCandidate, _ypos);
  return okay;
}
