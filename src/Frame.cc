#include <SDL_image.h>
#include "Frame.h"
#include "Logger.h"
#include "InitializationException.h"
using namespace blox;

/*
 * The frame image has a 180x180 hole cut into it at pos 10, 120
 * The left part is 200 pixels wide
 * The top part is 70 pixels tall
 * The bottom part is 30 pixels tall
 * The right part is 50 pixels wide
 * Transparency is pure yellow (0xFF, 0xFF, 0)
 */

Frame::Frame(SDL_Renderer *renderer) : _texture(NULL) {
  SDL_Surface *surface = IMG_Load("assets/frame.png");
  if (surface == NULL) {
    Logger::error(IMG_GetError(), "Frame::Frame");
    throw InitializationException("Frame 1");
  }
  SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0));
  _texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
  if (_texture == NULL) {
    Logger::error(SDL_GetError(), "Frame::Frame");
    throw InitializationException("Frame 2");
  }
}

Frame::~Frame() {
  if (_texture) {
    SDL_DestroyTexture(_texture);
  }
}

bool Frame::render(SDL_Renderer *renderer) {
  return SDL_RenderCopy(renderer, _texture, NULL, NULL) == 0;
}
