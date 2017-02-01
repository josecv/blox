#include <assert.h>
#include "Text.h"
#include "Logger.h"

using namespace blox;

Text::Text() {
  _font = TTF_OpenFont("assets/GentiumPlus-I.ttf", FONT_SIZE);
}

Text::~Text() {
  for (int i = 0; i < MAX_TEXT; i++) {
    closeTexture(i);
  }
  TTF_CloseFont(_font);
}

bool Text::renderString(std::string text, int id, SDL_Renderer *renderer,
                        int x, int y) {
  assert(id < MAX_TEXT);
  if (_strings[id].texture == NULL) {
    openTexture(text, id, renderer);
  } else if (_strings[id].text != text) {
    /* The text has changed, so we need to recreate everything. */
    closeTexture(id);
    openTexture(text, id, renderer);
  }
  SDL_Rect dest = { x, y, _strings[id].width, _strings[id].height };
  return SDL_RenderCopy(renderer, _strings[id].texture, NULL, &dest) == 0;
}

SDL_Color Text::getColor(int id) {
  SDL_Color color;
  /* It's just a plain white. */
  color.r = 0xFF;
  color.g = 0xFF;
  color.b = 0xFF;
  color.a = 0xFF;
  return color;
}

void Text::openTexture(std::string text, int id, SDL_Renderer *renderer) {
  SDL_Color color = getColor(id);
  SDL_Surface *surface = TTF_RenderText_Solid(_font, text.c_str(), color);
  if (surface == NULL) {
    Logger::error(TTF_GetError(), "Text::openTexture 1");
    throw TextException(text);
  }
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (texture == NULL) {
    Logger::error(SDL_GetError(), "Text::openTexture 2");
    SDL_FreeSurface(surface);
    throw TextException(text);
  }
  _strings[id].text = text;
  _strings[id].texture = texture;
  _strings[id].width = surface->w;
  _strings[id].height = surface->h;
  SDL_FreeSurface(surface);
}

void Text::closeTexture(int id) {
  if (_strings[id].texture != NULL) {
    SDL_DestroyTexture(_strings[id].texture);
    _strings[id].texture = NULL;
  }
}
