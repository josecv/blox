#include "Grid.h"
#include "Frame.h"

using namespace blox;

int Grid::xGridToPixel(int xpos) {
  return (xpos * 40) + Frame::LEFT_WIDTH;
}

int Grid::yGridToPixel(int ypos) {
  return (ypos * 40) + Frame::TOP_HEIGHT;
}
