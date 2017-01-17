#ifndef BLOX_WINDOW_H
#define BLOX_WINDOW_H
#include <SDL.h>
#include <vector>
#include "Object.h"

namespace blox {
/**
 * The top-level window.
 * Ultimately owns all top level sdl resources.
 */
class Window {
 public:
  /**
   * Create a new window with the dimensions given.
   * @param width the width
   * @param height the height
   */
  Window(int width, int height);

  /**
   * Destroy the window.
   */
  ~Window();

  /**
   * Initialize the window.
   * @return whether it worked.
   */
  bool init();

  /**
   * Add the object given to the list of objects that render to this window.
   * @param o the object to add.
   */
  void addObject(Object* o);

  /**
   * Render out the window with all containing objects.
   * @return did it work
   */
  bool render();
 private:
  /**
   * The SDL window.
   */
  SDL_Window *_window;

  /**
   * The window surface.
   */
  SDL_Surface *_screenSurface;

  /**
   * The renderer.
   */
  SDL_Renderer *_renderer;

  /**
   * The window width.
   */
  int _width;

  /**
   * The window height.
   */
  int _height;

  /**
   * Whether we managed to start sdl.
   */
  bool _sdlInitialized;

  /**
   * The objects that render here.
   */
  std::vector<Object*> _objects;
};
};
#endif /* BLOX_WINDOW_H */
