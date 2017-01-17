#ifndef BLOX_INITIALIZATION_EXCEPTION_H
#define BLOX_INITIALIZATION_EXCEPTION_H
#include <exception>
#include <string>

namespace blox {
/**
 * An exception thrown when some kind of blox initialization goes wrong.
 */
class InitializationException : public std::exception {
 public:
  /**
   * CTOR.
   * @param o the name of the object that failed initialization.
   */
  InitializationException(string msg) : _msg(msg) { }

  /**
   * Return the message.
   */
  virtual const char* what() const throw() {
    return ("Could not initialize an object: " + _msg).c_str();
  }
 private:
  /**
   * The message to append to the what().
   */
  std::string _msg;
};
};
#endif /* BLOX_INITIALIZATION_EXCEPTION_H */
