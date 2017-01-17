#include "Blox.h"
#include "Logger.h"

using namespace blox;

Blox::Blox() : _window(SCREEN_WIDTH, SCREEN_HEIGHT) {
  Logger::init("blox.log");
}

Blox::~Blox() {

}

void Blox::run() {
  if (!_window.init()) {
    return;
  }
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
