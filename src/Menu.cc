#include <cmath>
#include "Menu.h"

using namespace blox;

Menu::Menu() : _timeLastMovement(SDL_GetTicks()),
               _cursorMovement(CURSOR_NOTHING),
               _selected(OPTION_START) {

}

bool Menu::render(SDL_Renderer *renderer) {
  incrementCursor();
  bool okay = true;
  std::string startGame = "Start Game";
  std::string quit = "Quit";
  if (_selected == OPTION_START) {
    startGame = "-> " + startGame;
  } else if (_selected == OPTION_QUIT) {
    quit = "-> " + quit;
  }
  okay = okay && renderString(startGame, OPTION_START, renderer, MENU_X,
                              MENU_Y);
  okay = okay && renderString(quit, OPTION_START, renderer, MENU_X,
                              MENU_Y + (FONT_SIZE * 2));
  return okay;
}

bool Menu::handleKeypress(MenuOption *option) {
  const Uint8 *keyStates = SDL_GetKeyboardState(NULL);
  if (keyStates[SDL_SCANCODE_UP]) {
    cursorUp();
  } else if (keyStates[SDL_SCANCODE_DOWN]) {
    cursorDown();
  } else if (keyStates[SDL_SCANCODE_RETURN]) {
    *option = _selected;
    return true;
  }
  return false;
}

void Menu::incrementCursor() {
  Uint32 ticks = SDL_GetTicks();
  if (_cursorMovement != CURSOR_NOTHING
      && ((ticks - _timeLastMovement) >= CURSOR_VELOCITY)) {
    _selected = (MenuOption) (abs((_selected + _cursorMovement) % OPTION_MAX));
    _cursorMovement = CURSOR_NOTHING;
    _timeLastMovement = ticks;
  }
}

void Menu::cursorUp() {
  if (_cursorMovement == CURSOR_NOTHING) {
    _cursorMovement = CURSOR_UP;
    _timeLastMovement = SDL_GetTicks();
  }
}

void Menu::cursorDown() {
  if (_cursorMovement == CURSOR_NOTHING) {
    _cursorMovement = CURSOR_DOWN;
    _timeLastMovement = SDL_GetTicks();
  }
}
