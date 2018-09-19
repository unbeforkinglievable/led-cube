#include "visualizer.h"
#include "macros.h"

static int16_t
visualizer_platform_init( void );

static int16_t
visualizer_platform_visualize( cube_t * cube );

static int16_t
visualizer_platform_close( void );

int16_t
visualizer_init( void )
{
    return visualizer_platform_init();
}

int16_t
visualizer_visualize( cube_t * cube )
{
    DBG( "platform-specific visualize" );
    return visualizer_platform_visualize( cube );
}

int16_t
visualizer_close( void )
{
    DBG( "platform-specific visualizer cleanup" );
    return visualizer_platform_close();
}


#if defined(__POSIX_TARGET__)
#include "visualizer_posix.c"
#elif defined(__ARDUINO_TARGET__)
#include "visualizer_arduino.c"
#else
#error unhandled target
#endif
