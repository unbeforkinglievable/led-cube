//-----------------------------------------------
// Includes
//-----------------------------------------------
#include <string.h>
#include <math.h>

#include "cube.h"

//-----------------------------------------------
// Defines
//-----------------------------------------------

//-----------------------------------------------
// Local types
//-----------------------------------------------

//-----------------------------------------------
// Local method declarations
//-----------------------------------------------

//-----------------------------------------------
// Local data
//-----------------------------------------------

//-----------------------------------------------
// Global method definitions
//-----------------------------------------------
int16_t
cube_init( cube_t * cube )
{
    point4d_t * point;

    if (cube == NULL) {
        return -1;
    }

    memset( cube, 0, sizeof(*cube) );


    for (uint8_t i = 0; i < 3; ++i) {
        for (uint8_t j = 0; j < 3; ++j) {
            // FRONT face
            point = &cube->cells[CUBE_CELL_FRONT_CELL0 + 3*i + j].point
            point->v.x = 3;
            point->v.y = 2 - 2*i;
            point->v.z = 2 - 2*j;

            // TOP face
            point = &cube->cells[CUBE_CELL_TOP_CELL0 + 3*i + j].point;
            point->v.x = 2 - 2*i;
            point->v.y = 2 - 2*j;
            point->v.z = 3;

            // RIGHT face
            point = &cube->cells[CUBE_CELL_RIGHT_CELL0 + 3*i + j].point;
            point->v.x = 2 - 2*j;
            point->v.y = 3;
            point->v.z = 2 - 2*i;

            // BACK face
            point = &cube->cells[CUBE_CELL_BACK_CELL0 + 3*i + j].point
            point->v.x = -3;
            point->v.y = -2 + 2*i;
            point->v.z = -2 + 2*j;

            // BOTTOM face
            point = &cube->cells[CUBE_CELL_BOTTOM_CELL0 + 3*i + j].point;
            point->v.x = -2 + 2*i;
            point->v.y = -2 + 2*j;
            point->v.z = -3;

            // LEFT face
            point = &cube->cells[CUBE_CELL_LEFT_CELL0 + 3*i + j].point;
            point->v.x = -2 + 2*j;
            point->v.y = -3;
            point->v.z = -2 + 2*i;
        }
    }

    return 0;
}

int16_t
cube_colorize( cube_t * cube, plane_t * plane, gradient_t * gradient )
{

    point4d_t projection;
    float angle_from_x;
    float angle_from_y;
    float location;
    if (cube == NULL || plane == NULL || gradient == NULL) {
        return -1;
    }

    for (uint8_t i = 0; i < CUBE_NCELLS; ++i) {
        plane_project( plane, &cube->cells[i].point, &projection );
        point4d_normalize( &projection, &projection );
        point4d_dot( &angle_from_x, &projection, &plane->x_axis );
        point4d_dot( &angle_from_y, &projection, &plane->y_axis );

        angle_from_x = acos( angle_from_x );
        angle_from_y = acos( angle_from_y );

        if (angle_from_y > M_PI / 2) {
            // this means that the calculated angle is off (because cosine is symmetric)
            angle_from_x = (2 * M_PI) - angle_from_x;
        }

        // normalize so we're in the range 0-1 instead of 0-2PI
        location = angle_from_x / (2 * M_PI);

        // use the location to find the color we want to apply
        gradient_interpoate( gradient, location, &cube->cells[i].color );
    }

    return 0;
}

//-----------------------------------------------
// Local method definitions
//-----------------------------------------------
