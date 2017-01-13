#ifndef BLOX_LOGGER_H
#define BLOX_LOGGER_H
#include <string>

using namespace std;

namespace blox {
/**
 * The logger.
 */
class Logger {
 public:
  /**
   * Initialize the logger in the destination given.
   */
  static void init(string dest);

  /**
   * Log an error.
   */
  static void error(string msg, string caller);

  /**
   * Log an info message.
   */
  static void info(string msg, string caller);

 private:
  /**
   * The instance.
   */
  static Logger instance;

  /**
   * The destination file to log to.
   */
  string _dest;
};
};
#endif
