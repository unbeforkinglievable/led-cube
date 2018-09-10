#include <string.h>
#include <math.h>

#include "cube.h"

/**
   we're going to put the origin at the center of the cube.
   there's probably a good way to do this in a loop, but meh
   I'm going to put the FRONT face on the x axis, the RIGHT face on the y axis,
   and the TOP face on the z axis.  so everything should make sense based on that i think...

   I'm counting each cell-half as '1' to make the math easier, so the corners of the cube
   will be at (+-3, +-3, +-3).  But the centers of the faces will have one value at 3 and the
   other values some number of half-cell steps away from +-3.  That should explain the
   start points of (3, 2, 2) e.g.
 */
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
            point = &cube->cubies[CUBE_CELL_FRONT_CELL0 + 3*i + j].point
            point->e[POINT4D_X] = 3;
            point->e[POINT4D_Y] = 2 - 2*i;
            point->e[POINT4D_Z] = 2 - 2*j;

            // TOP face
            point = &cube->cubies[CUBE_CELL_TOP_CELL0 + 3*i + j].point;
            point->e[POINT4D_X] = 2 - 2*i;
            point->e[POINT4D_Y] = 2 - 2*j;
            point->e[POINT4D_Z] = 3;

            // RIGHT face
            point = &cube->cubies[CUBE_CELL_RIGHT_CELL0 + 3*i + j].point;
            point->e[POINT4D_X] = 2 - 2*j;
            point->e[POINT4D_Y] = 3;
            point->e[POINT4D_Z] = 2 - 2*i;

            // BACK face
            point = &cube->cubies[CUBE_CELL_BACK_CELL0 + 3*i + j].point
            point->e[POINT4D_X] = -3;
            point->e[POINT4D_Y] = -2 + 2*i;
            point->e[POINT4D_Z] = -2 + 2*j;

            // BOTTOM face
            point = &cube->cubies[CUBE_CELL_BOTTOM_CELL0 + 3*i + j].point;
            point->e[POINT4D_X] = -2 + 2*i;
            point->e[POINT4D_Y] = -2 + 2*j;
            point->e[POINT4D_Z] = -3;

            // LEFT face
            point = &cube->cubies[CUBE_CELL_LEFT_CELL0 + 3*i + j].point;
            point->e[POINT4D_X] = -2 + 2*j;
            point->e[POINT4D_Y] = -3;
            point->e[POINT4D_Z] = -2 + 2*i;
        }
    }

    return 0;
}

/**
   This is the fun one.
   We have ou

   Also note: normalization is a safe operation to do in-place, so the source/destination
   being the same in the point4d_normalize() calls is safe.
 */
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
        plane_project( plane, &cube->cubies[i].point, &projection );
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
        gradient_interpoate( gradient, location, &cube->cubies[i].color );
    }

    return 0;
}
