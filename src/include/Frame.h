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
   * @param renderer the renderer that the texture will belong to.
   */
  Frame(SDL_Renderer *renderer);

  /**
   * Destroy the frame.
   */
  ~Frame();

  /**
   * Render the frame.
   * @param renderer the renderer to render into.
   */
  virtual bool render(SDL_Renderer *renderer);

 private:
  /**
   * The texture of the frame.
   */
  SDL_Texture *_texture;
};
};

#endif /* BLOX_FRAME_H */
