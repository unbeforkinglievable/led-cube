//-----------------------------------------------
// Includes
//-----------------------------------------------
#include <unistd.h>
#include <math.h>
#include <string.h>

#include "app.h"

//-----------------------------------------------
// Defines
//-----------------------------------------------
#define APP_DFLT_ROTATION_STEP ((M_PI) / 14)
#define APP_SERVICE_PERIOD     500000

//-----------------------------------------------
// Local method declarations
//-----------------------------------------------
static int16_t
app_platform_init( void );

static int16_t
app_init_gradient( void );

//-----------------------------------------------
// Local data (but non-static and extern-ed,
// so really so global data)
//-----------------------------------------------
app_t g_app;

//-----------------------------------------------
// Global method definitions
//-----------------------------------------------
int16_t
app_init( void )
{
    // seed the random number generator
    random_seed( 0 );

    app_init_gradient();

    cube_init( &g_app.cube );

    rubiks_init( &g_app.rubiks_cube );
    rubiks_scramble( &g_app.rubiks_cube );

    plane_init( &g_app.plane );

    memset( &g_app.rotation_axis, 0, sizeof(g_app.rotation_axis) );
    g_app.rotation_axis.v.x = random_int( 1000 ) - 500; // FIXME: #define magic numbers
    g_app.rotation_axis.v.y = random_int( 1000 ) - 500;
    g_app.rotation_axis.v.z = random_int( 1000 ) - 500;
    point4d_normalize( &g_app.rotation_axis, &g_app.rotation_axis );

    visualizer_init();
    visualizer_visualize( &g_app.cube );

    app_platform_init();
    g_app.running = 1;

    return 0;
}

int16_t
app_is_running( void )
{
    return g_app.running;
}

void
app_cleanup( void )
{
    DBG( "closing the visualizer" );
    visualizer_close();
}

int16_t
app_service( void )
{
    static uint16_t counter = 0;

    plane_rotate( &g_app.plane, &g_app.rotation_axis, APP_DFLT_ROTATION_STEP );
    cube_colorize( &g_app.cube, &g_app.plane, &g_app.gradient );
    DBG( "requesting visualize" );
    visualizer_visualize( &g_app.cube );

    counter += 1;
    if (counter >= 4) {
        counter = 0;
        DBG( "v: (%1.2f, %1.2f, %1.2f) c: (%1.2f, %1.2f, %1.2f)",
             g_app.plane.x_axis.v.x, g_app.plane.x_axis.v.y, g_app.plane.x_axis.v.z,
             g_app.cube.cells[0].color.v.x, g_app.cube.cells[0].color.v.y, g_app.cube.cells[0].color.v.z );
    }

    usleep( APP_SERVICE_PERIOD );

    return 0;
}

//-----------------------------------------------
// Local method definitions
//-----------------------------------------------
static int16_t
app_init_gradient( void )
{
    gradient_entry_t entry;

    // create the gradient
    // 0.0000 - red
    // 0.1667 - magenta
    // 0.3333 - blue
    // 0.5000 - cyan
    // 0.6667 - green
    // 0.8333 - yellow
    // 1.0000 - red
    gradient_init( &g_app.gradient );
    // red
    entry.location = 0;
    entry.point.v.x = 1.0;
    entry.point.v.y = 0.0;
    entry.point.v.z = 0.0;
    gradient_add( &g_app.gradient, &entry );

    // magenta
    entry.location = 0.1667;
    entry.point.v.x = 1.0;
    entry.point.v.y = 0.0;
    entry.point.v.z = 1.0;
    gradient_add( &g_app.gradient, &entry );

    // blue
    entry.location = 0.3333;
    entry.point.v.x = 0.0;
    entry.point.v.y = 0.0;
    entry.point.v.z = 1.0;
    gradient_add( &g_app.gradient, &entry );

    // cyan
    entry.location = 0.5;
    entry.point.v.x = 0.0;
    entry.point.v.y = 1.0;
    entry.point.v.z = 1.0;
    gradient_add( &g_app.gradient, &entry );

    // green
    entry.location = 0.6667;
    entry.point.v.x = 0.0;
    entry.point.v.y = 1.0;
    entry.point.v.z = 0.0;
    gradient_add( &g_app.gradient, &entry );

    // yellow
    entry.location = 0.8333;
    entry.point.v.x = 1.0;
    entry.point.v.y = 1.0;
    entry.point.v.z = 0.0;
    gradient_add( &g_app.gradient, &entry );

    // red
    entry.location = 1;
    entry.point.v.x = 1.0;
    entry.point.v.y = 0.0;
    entry.point.v.z = 0.0;
    gradient_add( &g_app.gradient, &entry );

    return 0;
}

#if defined(__POSIX_TARGET__)
#include "app_posix.c"
#elif defined(__ARDUINO_TARGET__)
#include "app_arduino.c"
#else
#error unhandled target
#endif
