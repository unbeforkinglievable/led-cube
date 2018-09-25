#if defined(__ARDUINO_TARGET__)
#include "main_arduino.c"
#elif defined(__POSIX_TARGET__)
#include "main_posix.c"
#else
#error unhandled target
#endif
