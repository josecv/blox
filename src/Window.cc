#include "Window.h"
#include "Logger.h"

using namespace blox;

Window::Window(int width, int height) {
  _window = NULL;
  _screenSurface = NULL;
  _width = width;
  _height = height;
  _sdlInitialized = false;
}

Window::~Window() {
  if (_window) {
    SDL_DestroyWindow(_window);
  }
  if (_sdlInitialized) {
    SDL_Quit();
  }
}

bool Window::init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    Logger::error(SDL_GetError(), "Window::init");
    return false;
  }
  _sdlInitialized = true;
  _window = SDL_CreateWindow("Tutorial", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, _width,
                            _height, SDL_WINDOW_SHOWN);
  if (_window == NULL) {
    Logger::error(SDL_GetError(), "Window::init");
    return false;
  }
  _screenSurface = SDL_GetWindowSurface(_window);
  return true;
}
