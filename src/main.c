//-----------------------------------------------
// Includes
//-----------------------------------------------
#include <string.h>
#include <unistd.h>
#include <math.h>

#include "macros.h"
#include "cube.h"
#include "gradient.h"
#include "plane.h"
#include "point4d.h"
#include "random.h"
#include "rubiks_cube.h"

//-----------------------------------------------
// Defines
//-----------------------------------------------
#define APP_DFLT_ROTATION_STEP ((M_PI) / 12)

//-----------------------------------------------
// Types
//-----------------------------------------------
typedef struct {
    gradient_t    gradient;
    cube_t        cube;
    rubiks_cube_t rubiks_cube;
    plane_t       plane;
    point4d_t     rotation_axis;
} app_t;

//-----------------------------------------------
// Local method declarations
//-----------------------------------------------
static
int16_t app_init( void );

static
int16_t app_init_gradient( void );

//-----------------------------------------------
// Local data
//-----------------------------------------------
static app_t g_app;


//-----------------------------------------------
// Main
//-----------------------------------------------
int
main( int argc, char ** argv )
{

    uint16_t counter = 0;

    DBG( "initializing app" );
    app_init();

    DBG( "Starting mainloop" );
    while (1) {
        // infinite loop
        plane_rotate( &g_app.plane, &g_app.rotation_axis, APP_DFLT_ROTATION_STEP );
        cube_colorize( &g_app.cube, &g_app.plane, &g_app.gradient );
        usleep( 500000 );
        counter += 1;

        if (counter >= 4) {
            counter = 0;
            DBG( "v: (%1.2f, %1.2f, %1.2f) c: (%1.2f, %1.2f, %1.2f)",
                 g_app.plane.x_axis.v.x, g_app.plane.x_axis.v.y, g_app.plane.x_axis.v.z,
                 g_app.cube.cells[0].color.v.x, g_app.cube.cells[0].color.v.y, g_app.cube.cells[0].color.v.z );
        }
    }

    return 0;
}

//-----------------------------------------------
// Local method definitions
//-----------------------------------------------
static
int16_t app_init( void )
{

    // seed the random number generator
    random_seed( 0 );

    app_init_gradient();

    cube_init( &g_app.cube );

    rubiks_init( &g_app.rubiks_cube );
    rubiks_scramble( &g_app.rubiks_cube );

    plane_init( &g_app.plane );

    memset( &g_app.rotation_axis, 0, sizeof(g_app.rotation_axis) );
    g_app.rotation_axis.v.x = 1.0;
    g_app.rotation_axis.v.y = 1.0;
    g_app.rotation_axis.v.z = 1.0;
    point4d_normalize( &g_app.rotation_axis, &g_app.rotation_axis );

    return 0;
}

int16_t
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
