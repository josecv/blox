#include <SDL_image.h>
#include <ctime>
#include <cstdlib>
#include "Blox.h"
#include "IPiece.h"
#include "Logger.h"
#include "InitializationException.h"

using namespace blox;

Blox::Blox() : _window(SCREEN_WIDTH, SCREEN_HEIGHT),
               _frame(_window.getRenderer()), _pieceTexture(NULL),
               _currentPiece(NULL), _nextPiece(NULL) {
  _window.addObject(&_frame);
  _window.addObject(&_score);

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
  bool quit = false;
  SDL_Event e;

  Bottom bottom(&_gridRenderer);
  _window.addObject(&bottom);
  getNextPiece(&bottom);

  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }
    handleKeypress(_currentPiece);
    if (_currentPiece->fall(&bottom)) {
      getNextPiece(&bottom);
      int clear = bottom.clearRows();
      if (clear > 0) {
        _score.clearLines(clear);
      }
      if (bottom.hitsTop()) {
        printf("Game over!\n");
        quit = true;
      }
    }
    _window.render();
  }
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

void Blox::getNextPiece(Bottom *bottom) {
  if (_currentPiece == NULL) {
    /* Are we starting up? */
    _currentPiece = getRandomPiece();
    _window.addObject(_currentPiece);
  } else {
    _currentPiece->place(bottom);
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
      return new IPiece(&_gridRenderer, _score.getFallDealy());
    default:
      Logger::error("Wrong piece " + std::to_string(type), "Blox::getRandomPiece");
  }
  return NULL;
}
