#ifndef __CUBE_H__
#define __CUBE_H__

#include "point4d.h"
#include "plane.h"
#include "rubiks_cube.h"

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
} cube_cell_t;


typedef struct {
    point4d_t point;
    point4d_t color;
} cubie_t;

typedef struct {
    cubie_t cubies[CUBE_NCELLS];
} cube_t;

int16_t
cube_init( cube_t * cube );

int16_t
cube_colorize( cube_t * cube, plane_t * plane, gradient_t * gradient );


#endif//__CUBE_H__
