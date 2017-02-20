#include <algorithm>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Window.h"
#include "Logger.h"
#include "InitializationException.h"

using namespace blox;

Window::Window(int width, int height) : _window(NULL), _renderer(NULL),
                                        _screenSurface(NULL), _width(width),
                                        _height(height), _sdlInitialized(false),
                                        _imgInitialized(false), _ttfInitialized(false) {
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
  if (_ttfInitialized) {
    TTF_Quit();
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
  if (TTF_Init() == -1) {
    Logger::error(TTF_GetError(), "Window::init");
    return false;
  }
  _ttfInitialized = true;
  _window = SDL_CreateWindow("Blox", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, 577,
                             800, SDL_WINDOW_SHOWN);
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
  if (SDL_RenderSetLogicalSize(_renderer, _width, _height) < 0) {
    Logger::error(SDL_GetError(), "Window::init");
    return false;
  }
  _screenSurface = SDL_GetWindowSurface(_window);
  return true;
}

void Window::addObject(Object *o) {
  _objects.push_back(o);
}

void Window::removeObject(Object *o) {
  _objects.erase(std::remove(_objects.begin(), _objects.end(), o),
                 _objects.end());
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
