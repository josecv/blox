#ifndef BLOX_PIECE_H
#define BLOX_PIECE_H
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
   * @return how many lines got cleared by doing this.
   */
  virtual void place(Bottom *bottom) = 0;

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
   * Check that the piece won't collide with the left wall if we move
   * the centre to xCandidate.
   * @param xCandidate the candidate centre x position.
   * @return true if it will NOT collide, else false.
   */
  virtual bool checkLeft(int xCandidate) = 0;

  /**
   * Check that the piece won't collide with the right wall if we move
   * the centre to xCandidate.
   * @param xCandidate the candidate centre x position
   * @return true if it will NOT collide, else false.
   */
  virtual bool checkRight(int xCandidate) = 0;

  /**
   * Return if placing the centre of the piece on the yCandidate
   * given will cause it to stop moving because it has either hit the
   * floor or hit one of the pieces on the floor.
   * @param yCandidate the candidate y position
   * @param bottom the bottom
   * @return true if it will cause it to stop moving
   */
  virtual bool hitsFloor(int yCandidate, Bottom *bottom) = 0;

 private:
  /**
   * How quick should a side push (left or right) happen.
   */
  static const Uint32 SIDE_PUSH_VELOCITY = 95;

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
   * The tick count at the time that the last side push was requested.
   */
  Uint32 _timeSidePush;
};

};

#endif /* BLOX_PIECE_H */
