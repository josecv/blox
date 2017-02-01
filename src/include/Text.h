#ifndef BLOX_TEXT_H
#define BLOX_TEXT_H
#include <exception>
#include <SDL.h>
#include "Object.h"
#include <string>
#include <SDL_ttf.h>

namespace blox {

/**
 * A string to be rendered.
 */
typedef struct _StringRenderable {
  /**
   * The string.
   */
  std::string text;

  /**
   * The texture.
   */
  SDL_Texture *texture = NULL;

  /**
   * The width of the text.
   */
  int width;

  /**
   * The height of the text.
   */
  int height;
} StringRenderable;

/**
 * An exception thrown when opening text fails.
 */
class TextException : public std::exception {
 public:
  /**
   * CTOR.
   * @param msg the text that could not be initialized
   */
  TextException(std::string msg) : _msg(msg) { }

  /**
   * Return the message.
   */
  virtual const char* what() const throw() {
    return ("Could not initialize a text texture: " + _msg).c_str();
  }
 private:
  /**
   * The message to append to the what().
   */
  std::string _msg;
};

/**
 * A base mixin class for any object that needs to render text.
 * Has logic to decide whether a new object surface must be allocated, depends
 * on a one to one mapping between a numeric id and the text to render.
 * This allows the strings to change between renders while they keep the same
 * id (say to update a score counter).
 */
class Text : Object {
 public:
  /**
   * The maximum number of pieces of text supported for rendering.
   */
  static const int MAX_TEXT = 256;

  /**
   * The size of the font that we render.
   */
  static const int FONT_SIZE = 14;

  /**
   * CTOR.
   */
  Text();

  /**
   * Destructor.
   */
  virtual ~Text();

 protected:

  /**
   * Render a string to the dest rectangle given.
   * @param text the string to render
   * @param id the id of the text
   * @param renderer the renderer
   * @param x the x location to render
   * @param y the y location to render
   */
  bool renderString(std::string text, int id, SDL_Renderer *renderer,
                    int x, int y);

 private:

  /**
   * The strings.
   */
  StringRenderable _strings[MAX_TEXT];

  /**
   * The font.
   */
  TTF_Font *_font;

  /**
   * Open a texture for the text given, place it in the table.
   * @param text the text
   * @param id the id of the text
   * @param renderer the renderer
   */
  void openTexture(std::string text, int id, SDL_Renderer *renderer);

  /**
   * Close the texture with id given.
   */
  void closeTexture(int id);
};

};

#endif /* BLOX_TEXT_H */
