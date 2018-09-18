#ifndef __MACROS_H__
#define __MACROS_H__

#ifndef ABS
#define ABS(x) (((x) < 0) ? (-(x)) : (x))
#endif

#ifndef MAX
#define MAX(x,y) (((x) > (y)) ? (x) : (y))
#endif

#ifndef MIN
#define MIN(x,y) (((x) > (y)) ? (y) : (x))
#endif

#ifndef DEBUGGING
#define DEBUGGING 0
#endif

#if DEBUGGING
#if defined(__POSIX_TARGET__)
#include <stdio.h>
#define PRINTF(f,fmt,...) do { fprintf( f, fmt, ##__VA_ARGS__ ); fflush( f ); } while(0)
#define OUT(fmt,...) PRINTF( stdout, fmt, ##__VA_ARGS__ )
#define DBG(fmt,...) OUT( "[%s:%d:%s] "fmt"\r\n", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__ )
#define ERR(fmt,...) PRINTF( stderr, "***ERR [%s:%d:%s] "fmt"\r\n", \
                             __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__ )
#elif defined(__ARDUINO_TARGET__)
#define OUT(fmt,...) do { Serial.write(fmt,##__VA_ARGS__); } while(0)
#define DBG(fmt,...) OUT("[%s:%d:%s] "fmt"\r\n", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__ )
#define ERR(fmt,...) OUT("***ERR [%s:%d:%s] "fmt"\r\n", \
                         __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__ )
#else
#error unhandled target
#endif
#else
#define OUT(...)
#define DBG(...)
#define ERR(...)
#endif

#endif//__MACROS_H__
