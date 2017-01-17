#ifndef BLOX_FRAME_H
#define BLOX_FRAME_H
#include "Object.h"

namespace blox {
/**
 * The frame for the game (the box that the blocks fall into)
 */
class Frame : public Object {
 public:
  /**
   * Construct a new frame.
   */
  Frame();
  /**
   * Render the frame.
   * @param renderer the renderer to render into.
   */
  virtual bool render(SDL_Renderer *renderer);
};
};

#endif /* BLOX_FRAME_H */
