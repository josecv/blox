#ifndef BLOX_BLOX_H
#define BLOX_BLOX_H
#include "Window.h"
#include "Frame.h"
#include "Piece.h"
#include "NextPieceGrid.h"
#include "Score.h"
#include "Menu.h"

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
   * The current score.
   */
  Score _score;

  /**
   * The start menu.
   */
  Menu _menu;

  /**
   * The texture for the pieces.
   */
  SDL_Texture *_pieceTexture;

  /**
   * The piece we're currently playing with.
   */
  Piece *_currentPiece;

  /**
   * The next piece that's gonna come down the pipeline.
   */
  Piece *_nextPiece;

  /**
   * The grid renderer.
   */
  Grid _gridRenderer;

  /**
   * The bottom, containing the pieces that have fallen.
   */
  Bottom _bottom;

  /**
   * The renderer for the next piece.
   */
  NextPieceGrid _nextPieceRenderer;

  /**
   * Run the menu.
   * @return whether to keep going afterwards.
   */
  bool runMenu();

  /**
   * Run the actual game.
   * @return whether to keep going
   */
  bool runGame();

  /**
   * Handle a keypress from the user.
   * @param piece the current piece
   */
  void handleKeypress(Piece *piece);

  /**
   * Put the next piece into the playing field, get rid of the current one
   * and generate the one that's gonna come next.
   */
  void getNextPiece();

  /**
   * Generate a random piece.
   */
  Piece *getRandomPiece();
};
};

#endif /* BLOX_BLOX_H */
