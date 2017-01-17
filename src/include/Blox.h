#ifndef BLOX_BLOX_H
#define BLOX_BLOX_H
#include "Window.h"

namespace blox {
class Blox {
 public:
  /**
   * The width of the screen.
   */
  static const int SCREEN_WIDTH = 850;

  /**
   * The height of the screen.
   */
  static const int SCREEN_HEIGHT = 900;

  /**
   * CTOR.
   */
  Blox();

  /**
   * Destructor.
   */
  ~Blox();

  /**
   * Run the game.
   */
  void run();
 private:
  /**
   * The window.
   */
  Window _window;
};
};

#endif /* BLOX_BLOX_H */
