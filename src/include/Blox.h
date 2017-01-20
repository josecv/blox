#ifndef BLOX_BLOX_H
#define BLOX_BLOX_H
#include "Window.h"
#include "Frame.h"
#include "Piece.h"

namespace blox {
class Blox {
 public:
  /**
   * The width of the screen.
   */
  static const int SCREEN_WIDTH = 650;

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

  /**
   * The playing frame.
   */
  Frame _frame;

  /**
   * The texture for the pieces.
   */
  SDL_Texture *_pieceTexture;

  /**
   * Handle a keypress from the user.
   * @param piece the current piece
   */
  void handleKeypress(Piece *piece);
};
};

#endif /* BLOX_BLOX_H */
