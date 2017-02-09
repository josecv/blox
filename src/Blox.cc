#include <SDL_image.h>
#include <ctime>
#include <cstdlib>
#include "Blox.h"
#include "Logger.h"
#include "InitializationException.h"
#include "IPiece.h"
#include "JPiece.h"
#include "LPiece.h"
#include "OPiece.h"
#include "SPiece.h"

using namespace blox;

Blox::Blox() : _window(SCREEN_WIDTH, SCREEN_HEIGHT),
               _frame(_window.getRenderer()), _pieceTexture(NULL),
               _currentPiece(NULL), _nextPiece(NULL),
               _bottom(&_gridRenderer) {
  _window.addObject(&_frame);
  _window.addObject(&_score);
  _window.addObject(&_bottom);

  SDL_Surface *surface = IMG_Load("assets/blox_sprite.png");
  if (surface == NULL) {
    Logger::error(IMG_GetError(), "Blox::Blox");
    throw InitializationException("Blox 1");
  }
  SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0));
  _pieceTexture = SDL_CreateTextureFromSurface(_window.getRenderer(), surface);
  SDL_FreeSurface(surface);
  if (_pieceTexture == NULL) {
    Logger::error(SDL_GetError(), "Blox::Blox");
    throw InitializationException("Blox 2");
  }
  _gridRenderer.setPieceTexture(_pieceTexture);
  _nextPieceRenderer.setPieceTexture(_pieceTexture);
  srand(time(NULL));
}

Blox::~Blox() {
  if (_currentPiece != NULL) {
    delete _currentPiece;
  }
  SDL_DestroyTexture(_pieceTexture);
}

void Blox::run() {
  bool keepGoing = true;
  while (keepGoing) {
    keepGoing = runMenu();
    keepGoing = keepGoing && runGame();
  }
}

bool Blox::runMenu() {
  bool retval = true;
  bool keepGoing = true;
  SDL_Event e;
  _window.addObject(&_menu);
  while (keepGoing) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        keepGoing = false;
        retval = false;
      }
    }
    MenuOption option;
    if (_menu.handleKeypress(&option)) {
      keepGoing = false;
      if (option == OPTION_START) {
        retval = true;
      } else if (option == OPTION_QUIT) {
        retval = false;
      }
    }
    _window.render();
  }
  _window.removeObject(&_menu);
  return retval;
}

bool Blox::runGame() {
  bool keepGoing = true;
  bool retval = true;
  SDL_Event e;
  _score.reset();

  getNextPiece();

  while (keepGoing) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        keepGoing = false;
        retval = false;
      }
    }
    keepGoing = keepGoing && gameStep();
    _window.render();
  }
  _bottom.reset();
  if (_currentPiece != NULL) {
    _window.removeObject(_currentPiece);
    delete _currentPiece;
    _currentPiece = NULL;
  }
  if (_nextPiece != NULL) {
    _window.removeObject(_nextPiece);
    delete _nextPiece;
    _nextPiece = NULL;
  }
  return retval;
}

bool Blox::gameStep() {
  bool retval = true;
  handleKeypress(_currentPiece);
  if (_currentPiece->fall(&_bottom)) {
    getNextPiece();
    int clear = _bottom.clearRows();
    if (clear > 0) {
      _score.clearLines(clear);
      /* We might have changed level, so make sure the upcoming piece
       * has the right piece */
      _currentPiece->setFallDelay(_score.getFallDelay());
      _nextPiece->setFallDelay(_score.getFallDelay());
    }
    if (_bottom.hitsTop()) {
      retval = false;
    }
  }
  return retval;
}

void Blox::handleKeypress(Piece *piece) {
  const Uint8 *keyStates = SDL_GetKeyboardState(NULL);
  if (keyStates[SDL_SCANCODE_LEFT]) {
    piece->pushLeft();
  } else if (keyStates[SDL_SCANCODE_RIGHT]) {
    piece->pushRight();
  }
  if (keyStates[SDL_SCANCODE_UP]) {
    piece->rotate();
  }
  if (keyStates[SDL_SCANCODE_DOWN]) {
    piece->hardDrop();
  }
}

void Blox::getNextPiece() {
  if (_currentPiece == NULL) {
    /* Are we starting up? */
    _currentPiece = getRandomPiece();
    _window.addObject(_currentPiece);
  } else {
    _currentPiece->place(&_bottom);
    _window.removeObject(_currentPiece);
    delete _currentPiece;
    _currentPiece = _nextPiece;
  }
  _currentPiece->resetCoordinates();
  _nextPiece = getRandomPiece();
  _nextPiece->setGridRenderer(&_nextPieceRenderer);
  _currentPiece->setGridRenderer(&_gridRenderer);
  _window.addObject(_nextPiece);
}

Piece* Blox::getRandomPiece() {
  PieceType type = (PieceType) (rand() % PIECE_LAST);
  switch (type) {
    case PIECE_I:
      return new IPiece(&_gridRenderer, _score.getFallDelay());
    case PIECE_J:
      return new JPiece(&_gridRenderer, _score.getFallDelay());
    case PIECE_L:
      return new LPiece(&_gridRenderer, _score.getFallDelay());
    case PIECE_O:
      return new OPiece(&_gridRenderer, _score.getFallDelay());
    case PIECE_S:
      return new SPiece(&_gridRenderer, _score.getFallDelay());
    default:
      Logger::error("Wrong piece " + std::to_string(type), "Blox::getRandomPiece");
  }
  return NULL;
}
