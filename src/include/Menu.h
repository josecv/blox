#ifndef BLOX_MENU_H
#define BLOX_MENU_H
#include <SDL.h>
#include <string>
#include "Text.h"

namespace blox {

/**
 * The menu option.
 */
typedef enum _MenuOption {
  OPTION_START = 0,
  OPTION_QUIT,
  OPTION_MAX
} MenuOption;

/**
 * The main menu.
 */
class Menu : public Text {
 public:
  /**
   * CTOR.
   */
  Menu();

  /**
   * Handle the current key status.
   * @param option the return parameter for the option (if true is returned).
   * @return true iff there's been a selection
   */
  bool handleKeypress(MenuOption *option);

  bool render(SDL_Renderer *renderer);

 private:
  /**
   * The delay between one cursor movement and the next.
   */
  static const Uint32 CURSOR_VELOCITY = 150;

  /**
   * The X of the top left corner of the start of the menu.
   */
  static const int MENU_X = 270;

  /**
   * The Y of the top left corner of the start of the menu.
   */
  static const int MENU_Y = 190;

  /**
   * Move the cursor up.
   */
  void cursorUp();

  /**
   * Move the cursor down.
   */
  void cursorDown();


  /**
   * The time as of the last cursor movement.
   */
  Uint32 _timeLastMovement;

  /**
   * Where the cursor is moving.
   */
  enum {
    CURSOR_UP = -1,
    CURSOR_NOTHING = 0,
    CURSOR_DOWN = 1
  } _cursorMovement;

  /**
   * The currently selected option.
   */
  MenuOption _selected;

  /**
   * Push the cursor forward, if necessary.
   */
  void incrementCursor();
};

};


#endif /* BLOX_MENU_H */
