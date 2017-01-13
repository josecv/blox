#ifndef BLOX_WINDOW_H
#define BLOX_WINDOW_H
#include <SDL.h>
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
};
};
#endif /* BLOX_WINDOW_H */
