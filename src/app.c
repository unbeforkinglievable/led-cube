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

    memset( &g_app, 0, sizeof(g_app) );

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

    return 0;
}

int16_t
app_service( void )
{
    static uint16_t counter = 0;

    if (g_app.rubiks_mode) {
        // FIXME: we should run an inactivity timer that gets
        // kicked when we do rubiks cube rotations

        // we want to colorize the cube based on the rubiks cube
        for (uint8_t i = 0; i < CUBE_NCELLS; ++i) {
            switch (g_app.rubiks_cube.state[i]) {
            case RUBIKS_COLOR_WHITE:
                g_app.cube.cells[i].color.v.x = 0;
                g_app.cube.cells[i].color.v.y = 0;
                g_app.cube.cells[i].color.v.z = 0;
                break;
            case RUBIKS_COLOR_RED:
                g_app.cube.cells[i].color.v.x = 1;
                g_app.cube.cells[i].color.v.y = 0;
                g_app.cube.cells[i].color.v.z = 0;
                break;
            case RUBIKS_COLOR_GREEN:
                g_app.cube.cells[i].color.v.x = 0;
                g_app.cube.cells[i].color.v.y = 1;
                g_app.cube.cells[i].color.v.z = 0;
                break;
            case RUBIKS_COLOR_YELLOW:
                g_app.cube.cells[i].color.v.x = 1;
                g_app.cube.cells[i].color.v.y = 1;
                g_app.cube.cells[i].color.v.z = 0;
                break;
            case RUBIKS_COLOR_ORANGE:
                g_app.cube.cells[i].color.v.x = 1;
                g_app.cube.cells[i].color.v.y = 0.67;
                g_app.cube.cells[i].color.v.z = 0;
                break;
            case RUBIKS_COLOR_BLUE:
                g_app.cube.cells[i].color.v.x = 0;
                g_app.cube.cells[i].color.v.y = 0;
                g_app.cube.cells[i].color.v.z = 1;
                break;
            default:
                // why did you do this to me?
                break;
            }
        }
    }
    else {
        plane_rotate( &g_app.plane, &g_app.rotation_axis, APP_DFLT_ROTATION_STEP );
        cube_colorize( &g_app.cube, &g_app.plane, &g_app.gradient );
    }
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
