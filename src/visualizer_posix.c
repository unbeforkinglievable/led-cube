//-----------------------------------------------
// Includes
//-----------------------------------------------
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

#include <pthread.h>
#include <stdbool.h>
#include <string.h>

#include "app.h"

//-----------------------------------------------
// Local method declarations
//-----------------------------------------------
static void *
visualizer_opengl_thread( void * data );

static void
visualizer_display_callback( void );

static void
visualizer_special_key_callback( int key, int x, int y );

//-----------------------------------------------
// Local data
//-----------------------------------------------
static pthread_t g_opengl_thread;
static int32_t   g_window_id;
static int32_t   g_running;
static bool      g_has_cube;
static cube_t    g_cube;
static pthread_mutex_t g_lock;

//-----------------------------------------------
// "global"-er method definitions
//-----------------------------------------------
static int16_t
visualizer_platform_init( void )
{
    DBG( "initializing color buffer" );

    g_running = true;
    g_has_cube = false;
    pthread_mutex_init( &g_lock, NULL );
    pthread_create( &g_opengl_thread, NULL, visualizer_opengl_thread, NULL );

    return 0;
}

static int16_t
visualizer_platform_visualize( cube_t * cube )
{
    DBG( "requesting redisplay" );

    pthread_mutex_lock( &g_lock );
    memcpy( &g_cube, cube, sizeof(*cube) );
    g_has_cube = true;
    pthread_mutex_unlock( &g_lock );

    return 0;
}

static int16_t
visualizer_platform_close( void )
{
    DBG( "setting flag to stop GL thread" );
    g_running = false;
    DBG( "waiting for GL thread to stop" );
    pthread_join( g_opengl_thread, NULL );
    DBG( "GL thread stopped" );

    return 0;
}

//-----------------------------------------------
// Local method definitions
//-----------------------------------------------
static void *
visualizer_opengl_thread( void * data )
{
    (void) data;

    char *argv[1] = {"Visualizer"};
    int argc=1;
    glutInit( &argc, argv );

    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

    g_window_id = glutCreateWindow( "cube" );

    glEnable( GL_DEPTH_TEST );
    glutDisplayFunc( visualizer_display_callback );
    glutSpecialFunc( visualizer_special_key_callback );
    glutIdleFunc( visualizer_display_callback );

    glutSetOption( GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION );
    glutMainLoop();

    g_app.running = false;
    return NULL;
}

static void
visualizer_display_callback( void )
{
    // check if the user is trying to quit...
    if (!g_running) {
        glutDestroyWindow( g_window_id );
    }

    // check if we have data to display
    if (!g_has_cube) {
        return;
    }

    // check if user is trying to update data
    if (pthread_mutex_trylock( &g_lock ) != 0) {
        return;
    }

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // FIXME: actually draw each cell
    (void)g_cube;

    // FIXME: this is placeholder code
    glBegin( GL_POLYGON );
    glVertex3f( -1, -1, -1 );
    glVertex3f( -1, 1, -1 );
    glVertex3f( 1, 1, -1 );
    glVertex3f( 1, -1, -1 );
    glEnd();

    pthread_mutex_unlock( &g_lock );
}

static void
visualizer_special_key_callback( int key, int x, int y )
{
    DBG( "you pressed %d, %d, %d", key, x, y );
    switch (key) {
    case 'T':
        // top ccw
        break;
    case 't':
        // top cw
        break;
    case 'F':
        // front ccw
        break;
    case 'f':
        // front cw
        break;
    case 'r':
        // right ccw
        break;
    case 'R':
        // right cw
        break;
    case ' ':
        // flip
        break;
    default:
        break;
    }
}
