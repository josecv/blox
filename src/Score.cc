#include <string>
#include "Score.h"
#include <iostream>

using namespace blox;

/**
 * An enum to hold ids for the pieces of text.
 */
typedef enum _scoreID {
  SCORE_ID_SCORE_TITLE = 0,
  SCORE_ID_SCORE_NUMBER,
  SCORE_ID_LEVEL_TITLE,
  SCORE_ID_LEVEL_NUMBER
} scoreID;

void Score::clearLines(int lines) {
  _lines += lines;
  if (_lines >= ((_level + 1) * LINES_PER_LEVEL)) {
    _level++;
  }
  int scoreDelta = 0;
  switch (lines) {
    case 1:
      scoreDelta = 40;
      break;
    case 2:
      scoreDelta = 100;
      break;
    case 3:
      scoreDelta = 300;
      break;
    case 4:
      scoreDelta = 1200;
      break;
  }
  _score += scoreDelta * (_level + 1);
}

int Score::getFallDelay() {
  int candidate = 1000 - (_level * DELAY_DECREMENT);
  if (candidate < MIN_FALL_DELAY) {
    return MIN_FALL_DELAY;
  }
  return candidate;
}

bool Score::render(SDL_Renderer *renderer) {
  bool okay = true;
  okay = okay && renderString("Score: ", SCORE_ID_SCORE_TITLE, renderer,
      COUNTER_X, SCORE_Y);
  okay = okay && renderString(std::to_string(_score), SCORE_ID_SCORE_NUMBER,
      renderer, COUNTER_X, SCORE_Y + (FONT_SIZE * 2));
  okay = okay && renderString("Level: ", SCORE_ID_LEVEL_TITLE, renderer,
      COUNTER_X, LEVEL_Y);
  okay = okay && renderString(std::to_string(_level), SCORE_ID_LEVEL_NUMBER,
      renderer, COUNTER_X, LEVEL_Y + (FONT_SIZE * 2));
  return okay;
}

SDL_Color Score::getColor(int id) {
  SDL_Color color;
  color.r = 0x00;
  color.g = 0x00;
  color.b = 0x00;
  color.a = 0xFF;
  return color;
}
