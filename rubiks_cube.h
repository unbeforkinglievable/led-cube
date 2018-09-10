#ifndef __RUBIKS_CUBE_H__
#define __RUBIKS_CUBE_H__

#include "cube.h"

typedef enum {
    RUBIKS_COLOR_WHITE,
    RUBIKS_COLOR_RED,
    RUBIKS_COLOR_GREEN,
    RUBIKS_COLOR_YELLOW,
    RUBIKS_COLOR_ORANGE,
    RUBIKS_COLOR_BLUE,
    RUBIKS_NCOLORS
} rubiks_color_t;

typedef enum {
    RUBIKS_ROTATION_FRONT_CC,
    RUBIKS_ROTATION_FRONT_CCW,
    RUBIKS_ROTATION_RIGHT_CC,
    RUBIKS_ROTATION_RIGHT_CCW,
    RUBIKS_ROTATION_TOP_CC,
    RUBIKS_ROTATION_TOP_CCW,
    RUBIKS_ROTATION_FLIP,
    RUBIKS_NROTATIONS
} rubiks_rotation_t;

typedef struct {
    rubiks_color_t state[CUBE_NCELLS];
} rubiks_cube_t;

/**
   @brief initialize the cube to the default solved state
   @param cube - cube to initialize
   @return 0 on success, -1 on error
 */
int16_t
rubiks_init( rubiks_cube_t * cube );

/**
   @brief perform a trnsformation on the cube
   @param cube - cube to initialize
   @param rotation - transformation to perform
   @return 0 on success, -1 on error
 */
int16_t
rubiks_rotate( rubiks_cube_t * cube, rubiks_rotation_t rotation );

/**
   @brief scramble a cube randomly
   @param cube - cube to scramble
   @return 0 on success, -1 on error
 */
int16_t
rubiks_scramble( rubiks_cube_t * cube );

#endif // __RUBIKS_CUBE_H__
