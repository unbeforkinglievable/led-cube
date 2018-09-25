//-----------------------------------------------
// Includes
//-----------------------------------------------
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

#include <string.h>

#include "cube.h"

#define XFER(_x) ((3 + (_x)) / 12.0)

//-----------------------------------------------
// "global"-er method definitions
//-----------------------------------------------
static int16_t
visualizer_platform_init( void )
{
    return 0;
}

static int16_t
visualizer_platform_visualize( cube_t * cube )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    point4d_t * point;
    uint8_t face_axis;
    uint8_t other_axis[2];
    point4d_t square_corner;
    point4d_t * color;

    for (uint8_t i = 0; i < CUBE_NCELLS; ++i) {
        point = &cube->cells[i].point;
        color = &cube->cells[i].color;
        memcpy( &square_corner, point, sizeof(square_corner) );

        if (ABS( ABS( point->v.x ) - 3.0 ) < 0.01) {
            face_axis = POINT4D_X;
            other_axis[0] = POINT4D_Y;
            other_axis[1] = POINT4D_Z;
        }
        else if (ABS( ABS( point->v.y ) - 3.0 ) < 0.01) {
            face_axis = POINT4D_Y;
            other_axis[0] = POINT4D_X;
            other_axis[1] = POINT4D_Z;
        }
        else {
            face_axis = POINT4D_Z;
            other_axis[0] = POINT4D_X;
            other_axis[1] = POINT4D_Y;
        }

        // Begin Square
        glBegin( GL_POLYGON );
        square_corner.e[face_axis] = point->e[face_axis];
        // point 0
        square_corner.e[other_axis[0]] = point->e[other_axis[0]] - 0.9;
        square_corner.e[other_axis[1]] = point->e[other_axis[1]] - 0.9;
        glColor3f( color->v.x, color->v.y, color->v.z );
        glVertex3f( XFER(square_corner.v.x), XFER(square_corner.v.y), XFER(square_corner.v.z) );

        // point 1
        square_corner.e[other_axis[0]] = point->e[other_axis[0]] - 0.9;
        square_corner.e[other_axis[1]] = point->e[other_axis[1]] + 0.9;
        glColor3f( color->v.x, color->v.y, color->v.z );
        glVertex3f( XFER(square_corner.v.x), XFER(square_corner.v.y), XFER(square_corner.v.z) );

        // point 2
        square_corner.e[other_axis[0]] = point->e[other_axis[0]] + 0.9;
        square_corner.e[other_axis[1]] = point->e[other_axis[1]] + 0.9;
        glColor3f( color->v.x, color->v.y, color->v.z );
        glVertex3f( XFER(square_corner.v.x), XFER(square_corner.v.y), XFER(square_corner.v.z) );

        // point 3
        square_corner.e[other_axis[0]] = point->e[other_axis[0]] + 0.9;
        square_corner.e[other_axis[1]] = point->e[other_axis[1]] - 0.9;
        glColor3f( color->v.x, color->v.y, color->v.z );
        glVertex3f( XFER(square_corner.v.x), XFER(square_corner.v.y), XFER(square_corner.v.z) );

        glEnd();
        // End Square
    }

    glFlush();

    return 0;
}
