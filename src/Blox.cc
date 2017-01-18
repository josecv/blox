#include "Blox.h"
#include "IPiece.h"

#include <SDL_image.h>
#include "Logger.h"
#include "InitializationException.h"

using namespace blox;

Blox::Blox() : _window(SCREEN_WIDTH, SCREEN_HEIGHT),
               _frame(_window.getRenderer()), _pieceTexture(NULL) {
  _window.addObject(&_frame);

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
}

Blox::~Blox() {

}

void Blox::run() {
  bool quit = false;
  SDL_Event e;

  IPiece piece(_pieceTexture, 1000);
  Bottom bottom;
  _window.addObject(&piece);

  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }
    _window.render();
    if (piece.fall(&bottom)) {
      quit = true;
    }
  }
}
