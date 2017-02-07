#ifndef BLOX_PIECE_H
#define BLOX_PIECE_H
#include <functional>
#include "Object.h"
#include "Bottom.h"
#include "PieceType.h"
#include "Grid.h"

namespace blox {

/**
 * A tetris piece.
 */
class Piece : public Object {
 public:
  /**
   * CTOR; places the piece at the middle of the grid (to work with
   * the next piece preview).
   * @param gridRenderer the grid renderer
   * @param timeToFall how many ticks it takes to fall one position.
   */
  Piece(Grid *gridRenderer, Uint32 timeToFall);

  /**
   * Destructor.
   */
  virtual ~Piece() { }

  /**
   * Rotate the piece.
   */
  void rotate();

  /**
   * Push the piece to the left.
   */
  void pushLeft();

  /**
   * Push the piece to the right.
   */
  void pushRight();

  /**
   * Start a hard drop.
   */
  void hardDrop();

  /**
   * Increment the position of this piece based on the amount
   * of time that has passed since we last did so.
   *
   * @param bottom the bottom of the screen.
   * @return true if movement is to stop, else false.
   */
  bool fall(Bottom *bottom);

  /**
   * Reset the coordinates to the top of the play screen.
   */
  void resetCoordinates();

  /**
   * Set the grid renderer.
   * @param gridRenderer the grid renderer to set.
   */
  void setGridRenderer(Grid *gridRenderer);

  /**
   * Place the piece at its current location on the bottom given.
   * @param bottom the bottom
   */
  void place(Bottom *bottom);

  /**
   * Set the fall delay.
   * @param delay the new fall delay.
   */
  void setFallDelay(Uint32 delay) {
    _timeToFall = delay;
  }

  bool render(SDL_Renderer *renderer);

 protected:
  /**
   * The grid x position of the centre of the piece.
   */
  int _xpos;

  /**
   * The grid y position of the centre of the piece.
   */
  int _ypos;

  /**
   * The rotation of the piece.
   */
  int _rotation;

  /**
   * The grid renderer.
   */
  Grid *_gridRenderer;

  /**
   * Return this piece's type.
   * @return the piece type.
   */
  virtual PieceType getType() = 0;

  /**
   * Loop over every block in the piece, calling the function given on each
   * one of them.
   * @param func the function to call on the blocks, receives x, y pos of the
   *             block as argument.
   */
  void pieceLoop(std::function<bool (int, int)> func);

  /**
   * Loop over every block in the piece, calling the function given on each
   * one of them, and assuming that the centre of the piece is at the
   * xcandidate and ycandidate given.
   * @param func the function to call on the blocks, receives x, y pos of the
   *             block as argument. Should return true if we are to keep going
   *             else false.
   * @param xCandidate the x where we should assume the piece has been
   *                   placed
   * @param yCandidate the y where we should assume the piece has been
   *                   placed
   */
  virtual void pieceLoop(std::function<bool (int, int)> func, int xCandidate,
                         int yCandidate) = 0;

 private:
  /**
   * How quick should a side push (left or right) happen.
   */
  static const Uint32 SIDE_PUSH_VELOCITY = 140;

  /**
   * How many ticks does it take to fall one single position.
   */
  Uint32 _timeToFall;

  /**
   * Tick count as of our last fall.
   */
  Uint32 _timeLastFall;

  /**
   * Are we waiting for a left push.
   */
  bool _leftPush;

  /**
   * Are we waiting for a right push.
   */
  bool _rightPush;

  /**
   * Are we waiting to rotate.
   */
  bool _inRotation;

  /**
   * Are we waiting on a hard drop.
   */
  bool _hardDrop;

  /**
   * The tick counts at the time that the last rotation was requested.
   */
  Uint32 _timeRotation;

  /**
   * The tick count at the time that the last side push was requested.
   */
  Uint32 _timeSidePush;

  /**
   * The tick count at the time that the hard drop was requested.
   */
  Uint32 _timeHardDrop;

  /**
   * Return if placing the centre of the piece on the yCandidate
   * given will cause it to stop moving because it has either hit the
   * floor or hit one of the pieces on the floor.
   * @param yCandidate the candidate y position
   * @param bottom the bottom
   * @return true if it will cause it to stop moving
   */
  bool hitsFloor(int yCandidate, Bottom *bottom);

  /**
   * Check that the piece won't collide with the left wall if we move
   * the centre to xCandidate.
   * @param xCandidate the candidate centre x position.
   * @param bottom the bottom set of pieces
   * @return true if it will NOT collide, else false.
   */
  bool checkLeft(int xCandidate, Bottom *bottom);

  /**
   * Check that the piece won't collide with the right wall if we move
   * the centre to xCandidate.
   * @param xCandidate the candidate centre x position
   * @param bottom the bottom with pieces
   * @return true if it will NOT collide, else false.
   */
  bool checkRight(int xCandidate, Bottom *bottom);
};

};

#endif /* BLOX_PIECE_H */
