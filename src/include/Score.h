#ifndef BLOX_SCORE_H
#define BLOX_SCORE_H
#include <SDL.h>
#include "Text.h"

namespace blox {

/**
 * A score tracker and displayer.
 */
class Score : public Text {
 public:
  /**
   * Get the current score.
   * @return the score
   */
  int getScore() {
    return _score;
  }

  /**
   * Get the current level
   * @return the level
   */
  int getLevel() {
    return _level;
  }

  /**
   * Clear the number of lines given.
   * @param lines the lines to clear
   */
  void clearLines(int lines);

  /**
   * Get the delay, in ticks, between consecutive piece drops at the current
   * level.
   * @return the delay.
   */
  int getFallDealy();

  bool render(SDL_Renderer *renderer);

 protected:
  SDL_Color getColor(int id);

 private:
  /**
   * The x position of the counters
   */
  const static int COUNTER_X = 36;

  /**
   * The y position of the score counter.
   */
  const static int SCORE_Y = 335;

  /**
   * The y position of the level counter.
   */
  const static int LEVEL_Y = 650;

  /**
   * The current score.
   */
  int _score = 0;

  /**
   * The current level.
   */
  int _level = 0;

  /**
   * How many lines have been cleared.
   */
  int _lines = 0;
};

};

#endif
