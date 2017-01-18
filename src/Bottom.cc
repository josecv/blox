#include "Bottom.h"

using namespace blox;

bool Bottom::willCollide(int xgrid, int ygrid) {
  return false;
}

bool Bottom::render(SDL_Renderer *renderer) {
  return true;
}
