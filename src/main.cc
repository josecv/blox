#include <SDL.h>
#include <stdio.h>
#include "Logger.h"
#include "Blox.h"

using namespace blox;

int main(int argc, char **argv) {
  Logger::init("blox.log");
  Blox blox;
  blox.run();
  return 0;
}
