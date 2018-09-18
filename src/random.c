#include "random.h"

#if defined(__POSIX_TARGET__)
#include "random_posix.c"
#elif defined(__ARDUINO_TARGET__)
#include "random_arduino.c"
#else
#error unhandled target
#endif
