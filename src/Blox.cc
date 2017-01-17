#include "Blox.h"

using namespace blox;

Blox::Blox() : _window(SCREEN_WIDTH, SCREEN_HEIGHT), _frame(_window.getRenderer()) {
  _window.addObject(&_frame);
}

Blox::~Blox() {

}

void Blox::run() {
  bool quit = false;
  SDL_Event e;
  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }
    _window.render();
  }
}
