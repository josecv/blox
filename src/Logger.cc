#include "Logger.h"
#include <string>
#include <fstream>
using namespace blox;

Logger Logger::instance;

void Logger::init(string dest) {
  instance._dest = dest;
}

void Logger::error(string msg, string caller) {
  ofstream fout;
  fout.open(instance._dest, std::ofstream::out | std::ofstream::app);
  fout << "ERROR: " << msg << " (" << caller << ")\n";
  fout.close();
}

void Logger::info(string msg, string caller) {
  ofstream fout;
  fout.open(instance._dest, std::ofstream::out | std::ofstream::app);
  fout << "INFO: " << msg << " (" << caller << ")\n";
  fout.close();
}
