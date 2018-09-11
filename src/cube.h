#ifndef __CUBE_H__
#define __CUBE_H__

//-----------------------------------------------
// Includes
//-----------------------------------------------
#include "point4d.h"
#include "plane.h"
#include "rubiks_cube.h"

//-----------------------------------------------
// Defines
//-----------------------------------------------

//-----------------------------------------------
// Types
//-----------------------------------------------

/**
   @brief enumeration of cube cells

   Our cube has the geometry of a 3x3x3 rubiks cube, but we don't necessarily want to always
   use it as a rubiks cube, so this file exists so we can use it for other things as well.

   A note on cell numbering:

          TOP               T/|
          ------------      / |
         / 8 / 7 / 6 /    H/ 2/
         ------------     /| /|
        / 5 / 4 / 3 /   G/ |/ |
        ------------    / 1/ 5/
       / 2 / 1 / 0 /  I/| /| /|
       ------------   / |/ |/ |
       FRONT        R/ 0/ 4/ 8/
       ------------- | /| /| /
       | 6 | 3 | 0 | |/ |/ |/
       ------------- / 3/ 7/
       | 7 | 4 | 1 | | /| /
       ------------- |/ |/
       | 8 | 5 | 2 | / 6/
       ------------- | /
                     |/
                     /


   And the numbering on the BOTTOM, LEFT, and BACK faces match such that a flip from the
   TOP FRONT RIGHT (0, 0 ,0) to the BOTTOM LEFT RIGHT (0, 0, 0) has all the cell numbers
   line up properly.

 */
typedef enum {
    CUBE_CELL_FRONT_CELL0,
    CUBE_CELL_FRONT_CELL1,
    CUBE_CELL_FRONT_CELL2,
    CUBE_CELL_FRONT_CELL3,
    CUBE_CELL_FRONT_CELL4,
    CUBE_CELL_FRONT_CELL5,
    CUBE_CELL_FRONT_CELL6,
    CUBE_CELL_FRONT_CELL7,
    CUBE_CELL_FRONT_CELL8,
    CUBE_CELL_RIGHT_CELL0,
    CUBE_CELL_RIGHT_CELL1,
    CUBE_CELL_RIGHT_CELL2,
    CUBE_CELL_RIGHT_CELL3,
    CUBE_CELL_RIGHT_CELL4,
    CUBE_CELL_RIGHT_CELL5,
    CUBE_CELL_RIGHT_CELL6,
    CUBE_CELL_RIGHT_CELL7,
    CUBE_CELL_RIGHT_CELL8,
    CUBE_CELL_TOP_CELL0,
    CUBE_CELL_TOP_CELL1,
    CUBE_CELL_TOP_CELL2,
    CUBE_CELL_TOP_CELL3,
    CUBE_CELL_TOP_CELL4,
    CUBE_CELL_TOP_CELL5,
    CUBE_CELL_TOP_CELL6,
    CUBE_CELL_TOP_CELL7,
    CUBE_CELL_TOP_CELL8,
    CUBE_CELL_BACK_CELL0,
    CUBE_CELL_BACK_CELL1,
    CUBE_CELL_BACK_CELL2,
    CUBE_CELL_BACK_CELL3,
    CUBE_CELL_BACK_CELL4,
    CUBE_CELL_BACK_CELL5,
    CUBE_CELL_BACK_CELL6,
    CUBE_CELL_BACK_CELL7,
    CUBE_CELL_BACK_CELL8,
    CUBE_CELL_LEFT_CELL0,
    CUBE_CELL_LEFT_CELL1,
    CUBE_CELL_LEFT_CELL2,
    CUBE_CELL_LEFT_CELL3,
    CUBE_CELL_LEFT_CELL4,
    CUBE_CELL_LEFT_CELL5,
    CUBE_CELL_LEFT_CELL6,
    CUBE_CELL_LEFT_CELL7,
    CUBE_CELL_LEFT_CELL8,
    CUBE_CELL_BOTTOM_CELL0,
    CUBE_CELL_BOTTOM_CELL1,
    CUBE_CELL_BOTTOM_CELL2,
    CUBE_CELL_BOTTOM_CELL3,
    CUBE_CELL_BOTTOM_CELL4,
    CUBE_CELL_BOTTOM_CELL5,
    CUBE_CELL_BOTTOM_CELL6,
    CUBE_CELL_BOTTOM_CELL7,
    CUBE_CELL_BOTTOM_CELL8,
    CUBE_NCELLS
} cube_cell_index_t;


/**
   @brief a cube cell is a point, indicating the location of the cell,
          and a color, indicating the color of the face
 */
typedef struct {
    point4d_t point;
    point4d_t color;
} cube_cell_t;

/**
   @brief a cube is just a collection of cells
 */
typedef struct {
    cube_cell_t cells[CUBE_NCELLS];
} cube_t;

//-----------------------------------------------
// Global method declarations
//-----------------------------------------------

/**
   @brief initialize a cube object

   Zeroize all color information and set the points for each cell according to the
   appropriate geometry of that cell

   We're going to put the origin at the center of the cube.
   I'm going to put the FRONT face on the x axis, the RIGHT face on the y axis,
   and the TOP face on the z axis.  so everything should make sense based on that...

   I'm counting each cell-half as '1' to make the math easier, so the corners of the cube
   will be at (+-3, +-3, +-3).  But the centers of the faces will have one value at 3 and the
   other values some number of half-cell steps away from +-3.  That should explain the
   start points of (3, 2, 2) e.g.
 */

int16_t
cube_init( cube_t * cube );

/**
   @brief project cube points into plane and colorize based on angle to plane's x-axis

   This is the fun one.
   We project our cube points into the plane.  We then determine the angle from
   the projected point to the X-axis of that plane.  We then normalize that angle
   so we can use it as a lookup into the gradient to determine how to colorize that point.
   And we do all that for each point in the cube.

   Also note: normalization is a safe operation to do in-place, so the source/destination
   being the same in the point4d_normalize() calls is safe.

   @param cube - input - cube to colorize
   @param plane - input - plane in which to project the cube
   @param gradient - input - gradient with which to colorize the cube
 */
int16_t
cube_colorize( cube_t * cube, plane_t const * const plane, gradient_t const * const gradient );


#endif//__CUBE_H__
