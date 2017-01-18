#ifndef BLOX_FRAME_H
#define BLOX_FRAME_H
#include "Object.h"

namespace blox {
/**
 * The frame for the game (the box that the blocks fall into)
 */
class Frame : public Object {
 public:
  /*
   * The frame image has a 180x180 hole cut into it at pos 10, 120
   * The left part is 200 pixels wide
   * The top part is 70 pixels tall
   * The bottom part is 30 pixels tall
   * The right part is 50 pixels wide
   * Transparency is pure yellow (0xFF, 0xFF, 0)
   */

  /**
   * Pixel width of the left part of the frame.
   */
  static const int LEFT_WIDTH = 200;

  /**
   * Pixel width of the right part of the frame.
   */
  static const int RIGHT_WIDTH = 50;

  /**
   * Pixel height of the top part of the frame.
   */
  static const int TOP_HEIGHT = 200;

  /**
   * Pixel height of the bottom part of the frame.
   */
  static const int BOTTOM_HEIGHT = 30;

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
