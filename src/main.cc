#include <SDL.h>
#include <stdio.h>
#include "Logger.h"
#include "Blox.h"

#ifndef __WIN32
#include <unistd.h>
#endif

#ifndef GAME_HOME
  #define GAME_HOME "."
#endif /* GAME_HOME */

using namespace blox;

static void chdir_to_home() {
  chdir(GAME_HOME);
  printf("%s\n", GAME_HOME);
}

int main(int argc, char **argv) {
  chdir_to_home();
  Logger::init("blox.log");
  Blox blox;
  blox.run();
  return 0;
}
