#include "visualizer.h"

static int16_t
visualizer_platform_init( void );

static int16_t
visualizer_platform_visualize( cube_t * cube );

int16_t
visualizer_init( void )
{
    return visualizer_platform_init();
}

int16_t
visualizer_visualize( cube_t * cube )
{
    return visualizer_platform_visualize( cube );
}


#if defined(__POSIX_TARGET__)
#include "visualizer_posix.c"
#elif defined(__ARDUINO_TARGET__)
#include "visualizer_arduino.c"
#else
#error unhandled target
#endif
