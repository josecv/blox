#ifndef BLOX_OBJECT_H
#define BLOX_OBJECT_H
#include <SDL.h>

namespace blox {
class Object {
 public:
  /**
   * Render to the renderer given.
   * @param renderer the renderer to render to.
   * @return whether it worked.
   */
  virtual bool render(SDL_Renderer *renderer) = 0;
};
};

#endif /* BLOX_OBJECT_H */
