#include "Blox.h"

using namespace blox;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


Blox::Blox() : _window(SCREEN_WIDTH, SCREEN_HEIGHT) {

}

Blox::~Blox() {

}

void Blox::run() {
  if (!_window.init()) {
    return;
  }
}
