#include "IPiece.h"
#include "Grid.h"

using namespace blox;

/* The centre of the IPiece is the second block from the bottom. */

bool IPiece::renderTo(int xpos, int ypos, SDL_Renderer *renderer) {
  /* TODO: Can we take the srcrect elsewhere */
  SDL_Rect srcrect;
  SDL_Rect dstrect;
  srcrect.x = 0;
  srcrect.y = 0;
  srcrect.w = 40;
  srcrect.h = 40;
  dstrect.w = 40;
  dstrect.h = 40;
  if (!(_rotation % 2)) {
    dstrect.x = xpos;
    for (int y = ypos - 80, block = 0; block < 4; block++, y += 40) {
      if (y >= 70) {
        dstrect.y = y;
        SDL_RenderCopy(renderer, _pieceTexture, &srcrect, &dstrect);
      }
    }
  }

  return true;
}

bool IPiece::checkLeft(int xCandidate) {
  return true;
}

bool IPiece::checkRight(int xCandidate) {
  return true;
}

bool IPiece::hitsFloor(int yCandidate, Bottom *bottom) {
  if ((yCandidate + 2) >= Grid::GRID_HEIGHT) {
    return true;
  }
  return false;
}