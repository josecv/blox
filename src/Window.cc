#include "Window.h"
#include "Logger.h"
#include "InitializationException.h"
#include <iostream>
#include <SDL_image.h>

using namespace blox;

Window::Window(int width, int height) : _window(NULL), _renderer(NULL),
                                        _screenSurface(NULL), _width(width),
                                        _height(height), _sdlInitialized(false),
                                        _imgInitialized(false) {
  if (!init()) {
    throw InitializationException("Window");
  }
}

Window::~Window() {
  if (_renderer) {
    SDL_DestroyRenderer(_renderer);
  }
  if (_window) {
    SDL_DestroyWindow(_window);
  }
  if (_imgInitialized) {
    IMG_Quit();
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
  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    Logger::error(IMG_GetError(), "Window::init");
    return false;
  }
  _imgInitialized = true;
  _window = SDL_CreateWindow("Blox", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, _width,
                             _height, SDL_WINDOW_SHOWN);
  if (_window == NULL) {
    Logger::error(SDL_GetError(), "Window::init");
    return false;
  }
  _renderer = SDL_CreateRenderer(_window, -1,
      SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (_renderer == NULL) {
    Logger::error(SDL_GetError(), "Window::init");
    return false;
  }
  _screenSurface = SDL_GetWindowSurface(_window);
  return true;
}

void Window::addObject(Object *o) {
  _objects.push_back(o);
}

bool Window::render() {
  SDL_RenderClear(_renderer);
  for (auto o : _objects) {
    o->render(_renderer);
  }
  SDL_RenderPresent(_renderer);
  return true;
}

SDL_Renderer *Window::getRenderer() {
  return _renderer;
}
