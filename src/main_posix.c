//-----------------------------------------------
// Includes
//-----------------------------------------------
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

#include <signal.h>

#include "app.h"

static int32_t g_window_id;
static volatile int32_t g_scroll_level = 0;
static volatile int32_t g_mouse_moving = 0;
static volatile int32_t g_mouse_x = 0;
static volatile int32_t g_mouse_y = 0;
static volatile uint8_t g_running;

static void
app_service_wrapper( void )
{
    if (!g_running) {
        glutDestroyWindow( g_window_id );
    }
    app_service();
}

static void
app_mouse_handler( int button, int state, int x, int y )
{
    // handle zooming
    switch (button) {
    case 3: //GLUT_SCROLL_UP:
        if (state == GLUT_DOWN) {
            g_scroll_level++;
        }
        break;

    case 4: //GLUT_SCROLL_DOWN:
        if (state == GLUT_DOWN) {
            g_scroll_level--;
        }
        break;

    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN) {
            g_mouse_x = x;
            g_mouse_y = y;
            g_mouse_moving = 1;
        }
        else if (state == GLUT_UP) {
            g_mouse_moving = 0;
        }
        break;

    default:
        return;
    }

    glutPostRedisplay();
}

static void
app_interrupt_handler( int code )
{
    DBG( "caught ctrl-c.  setting flag to stop the app" );
    g_running = 0;
}

static void
visualizer_visualize_wrapper( void )
{
    visualizer_visualize( &g_app.cube );
}

static void
app_keyboard_handler( unsigned char key, int x, int y )
{
    // FIXME: I think this should actually be a method in the app
    // so that we can call it and the app can handle the inactivity timeout
    // that kicks us into screensaver mode
    DBG( "you pressed %d, %d, %d", key, x, y );
    switch (key) {
    case 'T':
        // top ccw
        if (g_app.rubiks_mode) {
            DBG( "top ccw" );
            rubiks_rotate( &g_app.rubiks_cube, RUBIKS_ROTATION_TOP_CCW );
        }
        break;

    case 't':
        // top cw
        if (g_app.rubiks_mode) {
            DBG( "top cw" );
            rubiks_rotate( &g_app.rubiks_cube, RUBIKS_ROTATION_TOP_CW );
        }
        break;

    case 'F':
        // front ccw
        if (g_app.rubiks_mode) {
            DBG( "front ccw" );
            rubiks_rotate( &g_app.rubiks_cube, RUBIKS_ROTATION_FRONT_CCW );
        }
        break;

    case 'f':
        // front cw
        if (g_app.rubiks_mode) {
            DBG( "front cw" );
            rubiks_rotate( &g_app.rubiks_cube, RUBIKS_ROTATION_FRONT_CW );
        }
        break;

    case 'R':
        // right ccw
        if (g_app.rubiks_mode) {
            DBG( "right cw" );
            rubiks_rotate( &g_app.rubiks_cube, RUBIKS_ROTATION_RIGHT_CCW );
        }
        break;

    case 'r':
        // right cw
        if (g_app.rubiks_mode) {
            DBG( "right ccw" );
            rubiks_rotate( &g_app.rubiks_cube, RUBIKS_ROTATION_RIGHT_CW );
        }
        break;

    case ' ':
        // flip
        if (g_app.rubiks_mode) {
            DBG( "flipping cube" );
            rubiks_rotate( &g_app.rubiks_cube, RUBIKS_ROTATION_FLIP );
        }
        break;

    case 's':
        // scramble
        if (g_app.rubiks_mode) {
            DBG( "scrambling cube" );
            rubiks_scramble( &g_app.rubiks_cube );
        }
        break;

    case 'm':
        // change to rubiks mode
        g_app.rubiks_mode = (g_app.rubiks_mode) ? 0 : 1;
        DBG( "Toggling rubiks mode %s", (g_app.rubiks_mode) ? "ON" : "OFF" );
        break;

    default:
        ERR( "unhandled keyboard key %d", key );
        return;
    }
    glutPostRedisplay();
}

int
main( int argc, char ** argv )
{

    DBG( "Initializing the app" );
    signal( SIGINT, app_interrupt_handler );
    app_init();

    DBG( "Initializing GL" );
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_SINGLE );
    glutInitWindowSize( 300, 300 );
    glutInitWindowPosition( 100, 100 );
    g_window_id = glutCreateWindow( "cube" );

    glEnable( GL_DEPTH_TEST );
    glutDisplayFunc( visualizer_visualize_wrapper );
    glutKeyboardFunc( app_keyboard_handler );
    glutMouseFunc( app_mouse_handler );

    // FIXME: use a timer instead so we get a fixed framerate
    glutIdleFunc( app_service_wrapper );

    glutSetOption( GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION );

    DBG( "Starting app mainloop" );
    g_running = 1;
    glutMainLoop();

    DBG( "Goodbye!" );
    return 0;
}
