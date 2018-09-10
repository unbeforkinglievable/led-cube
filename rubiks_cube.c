#include <string.h>
#include <stdlib.h>

#include "rubiks_cube.h"

static int16_t
rubiks_rotate_front_cc( rubiks_cube_t * cube );

static int16_t
rubiks_rotate_right_cc( rubiks_cube_t * cube );

static int16_t
rubiks_rotate_top_cc( rubiks_cube_t * cube );

static int16_t
rubiks_flip( rubiks_cube_t * cube );

int16_t
rubiks_init( rubiks_cube_t * cube )
{
    if (cube == NULL) {
        return -1;
    }
    memset( cube, 0, sizeof(*cube) );

    for (uint8 i = CUBE_CELL_FRONT_CELL0; i <= CUBE_CELL_FRONT_CELL8; ++i) {
        cube->state[i] = RUBIKS_COLOR_WHITE;
    }
    for (uint8 i = CUBE_CELL_BACK_CELL0; i <= CUBE_CELL_BACK_CELL8; ++i) {
        cube->state[i] = RUBIKS_COLOR_YELLOW;
    }
    for (uint8 i = CUBE_CELL_RIGHT_CELL0; i <= CUBE_CELL_RIGHT_CELL8; ++i) {
        cube->state[i] = RUBIKS_COLOR_BLUE;
    }
    for (uint8 i = CUBE_CELL_LEFT_CELL0; i <= CUBE_CELL_LEFT_CELL8; ++i) {
        cube->state[i] = RUBIKS_COLOR_GREEN;
    }
    for (uint8 i = CUBE_CELL_TOP_CELL0; i <= CUBE_CELL_TOP_CELL8; ++i) {
        cube->state[i] = RUBIKS_COLOR_ORANGE;
    }
    for (uint8 i = CUBE_CELL_BOTTOM_CELL0; i <= CUBE_CELL_BOTTOM_CELL8; ++i) {
        cube->state[i] = RUBIKS_COLOR_RED;
    }

    // FIXME: we should probably seed the rng in a parent application instead
    srand( 0 );

    return 0;
}

int16_t
rubiks_rotate( rubiks_cube_t * cube, rubiks_rotation_t rotation )
{
    int16_t status;

    if (cube == NULL) {
        return -1;
    }

    switch (rotation) {
    case RUBIKS_ROTATION_FRONT_CC:
        // front cc
        status = rubiks_rotate_front_cc( cube );
        break;

    case RUBIKS_ROTATION_FRONT_CCW:
        // front ccw is 3 cc rotations
        for (uint8 i = 0; i < 3; ++i) {
            status = rubiks_rotation_front_cc( cube );
            if (status != 0) {
                break;
            }
        }
        break;

    case RUBIKS_ROTATION_RIGHT_CC:
        // right cc
        status = rubiks_rotation_right_cc( cube );
        break;

    case RUBIKS_ROTATION_RIGHT_CCW:
        // right ccw is 3 cc rotations
        for (uint8 i = 0; i < 3; ++i) {
            status = rubiks_rotation_right_cc( cube );
            if (status != 0) {
                break;
            }
        }
        break;

    case RUBIKS_ROTATION_TOP_CC:
        // top cc
        status = rubiks_rotation_top_cc( cube );
        break;

    case RUBIKS_ROTATION_TOP_CCW:
        // top ccw is 3 cc rotations
        for (uint8 i = 0; i < 3; ++i) {
            status = rubiks_rotation_top_cc( cube );
            if (status != 0) {
                break;
            }
        }
        break;

    case RUBIKS_ROTATION_FLIP:
        // flip!
        status = rubiks_flip( cube );
        break;

    default:
        // out of bounds;
        status = -1;
    }

    return status;
}

int16_t
rubiks_scramble( rubiks_cube_t * cube )
{
    for (uint8_t i = 0; i < 12 + (rand() % 12); ++i) {
        for (uint8_t j = 0; j < 3 + (rand() % 3); ++j) {
            // do something other than a flip
            rubiks_rotate( cube, random_get_int( 0, RUBIKS_ROTATION_FLIP - 1 ) );
        }
        // move to the back side
        rubiks_rotate( cube, RUBIKS_ROTATION_FLIP );
    }

    return 0;
}

static int16_t
rubiks_rotate_front_cc( rubiks_cube_t * cube )
{
    int16_t tmp;

    // swap the corners on the rotated face
    tmp = cube->state[CUBE_CELL_FRONT_CELL0];
    cube->state[CUBE_CELL_FRONT_CELL0] = cube->state[CUBE_CELL_FRONT_CELL6];
    cube->state[CUBE_CELL_FRONT_CELL6] = cube->state[CUBE_CELL_FRONT_CELL8];
    cube->state[CUBE_CELL_FRONT_CELL8] = cube->state[CUBE_CELL_FRONT_CELL2];
    cube->state[CUBE_CELL_FRONT_CELL2] = tmp;

    // swap the sides on the rotated face
    tmp = cube->state[CUBE_CELL_FRONT_CELL1];
    cube->state[CUBE_CELL_FRONT_CELL1] = cube->state[CUBE_CELL_FRONT_CELL3];
    cube->state[CUBE_CELL_FRONT_CELL3] = cube->state[CUBE_CELL_FRONT_CELL7];
    cube->state[CUBE_CELL_FRONT_CELL7] = cube->state[CUBE_CELL_FRONT_CELL5];
    cube->state[CUBE_CELL_FRONT_CELL5] = tmp;

    // swap the other faces that get translated as part of the rotation
    tmp = cube->state[CUBE_CELL_RIGHT_CELL0];
    cube->state[CUBE_CELL_RIGHT_CELL0] = cube->state[CUBE_CELL_TOP_CELL2];
    cube->state[CUBE_CELL_TOP_CELL2] = cube->state[CUBE_CELL_LEFT_CELL6];
    cube->state[CUBE_CELL_LEFT_CELL6] = cube->state[CUBE_CELL_BOTTOM_CELL8];
    cube->state[CUBE_CELL_BOTTOM_CELL8] = tmp;

    tmp = cube->state[CUBE_CELL_RIGHT_CELL3];
    cube->state[CUBE_CELL_RIGHT_CELL3] = cube->state[CUBE_CELL_TOP_CELL1];
    cube->state[CUBE_CELL_TOP_CELL1] = cube->state[CUBE_CELL_LEFT_CELL7];
    cube->state[CUBE_CELL_LEFT_CELL7] = cube->state[CUBE_CELL_BOTTOM_CELL5];
    cube->state[CUBE_CELL_BOTTOM_CELL5] = tmp;

    tmp = cube->state[CUBE_CELL_RIGHT_CELL6];
    cube->state[CUBE_CELL_RIGHT_CELL6] = cube->state[CUBE_CELL_TOP_CELL0];
    cube->state[CUBE_CELL_TOP_CELL0] = cube->state[CUBE_CELL_LEFT_CELL8];
    cube->state[CUBE_CELL_LEFT_CELL8] = cube->state[CUBE_CELL_BOTTOM_CELL2];
    cube->state[CUBE_CELL_BOTTOM_CELL2] = tmp;

    return 0;
}

static int16_t
rubiks_rotate_right_cc( rubiks_cube_t * cube )
{
    int16_t tmp;

    // swap the corners
    tmp = cube->state[CUBE_CELL_RIGHT_CELL0];
    cube->state[CUBE_CELL_RIGHT_CELL0] = cube->state[CUBE_CELL_RIGHT_CELL6];
    cube->state[CUBE_CELL_RIGHT_CELL6] = cube->state[CUBE_CELL_RIGHT_CELL8];
    cube->state[CUBE_CELL_RIGHT_CELL8] = cube->state[CUBE_CELL_RIGHT_CELL2];
    cube->state[CUBE_CELL_RIGHT_CELL2] = tmp;

    // swap the sides
    tmp = cube->state[CUBE_CELL_RIGHT_CELL1];
    cube->state[CUBE_CELL_RIGHT_CELL1] = cube->state[CUBE_CELL_RIGHT_CELL3];
    cube->state[CUBE_CELL_RIGHT_CELL3] = cube->state[CUBE_CELL_RIGHT_CELL7];
    cube->state[CUBE_CELL_RIGHT_CELL7] = cube->state[CUBE_CELL_RIGHT_CELL5];
    cube->state[CUBE_CELL_RIGHT_CELL5] = tmp;

    // swap the other faces that get translated as part of the rotation
    tmp = cube->state[CUBE_CELL_TOP_CELL0];
    cube->state[CUBE_CELL_TOP_CELL0] = cube->state[CUBE_CELL_FRONT_CELL2];
    cube->state[CUBE_CELL_FRONT_CELL2] = cube->state[CUBE_CELL_BOTTOM_CELL6];
    cube->state[CUBE_CELL_BOTTOM_CELL6] = cube->state[CUBE_CELL_BACK_CELL8];
    cube->state[CUBE_CELL_BACK_CELL8] = tmp;

    tmp = cube->state[CUBE_CELL_TOP_CELL3];
    cube->state[CUBE_CELL_TOP_CELL3] = cube->state[CUBE_CELL_FRONT_CELL1];
    cube->state[CUBE_CELL_FRONT_CELL1] = cube->state[CUBE_CELL_BOTTOM_CELL7];
    cube->state[CUBE_CELL_BOTTOM_CELL7] = cube->state[CUBE_CELL_BACK_CELL5];
    cube->state[CUBE_CELL_BACK_CELL5] = tmp;

    tmp = cube->state[CUBE_CELL_TOP_CELL6];
    cube->state[CUBE_CELL_TOP_CELL6] = cube->state[CUBE_CELL_FRONT_CELL0];
    cube->state[CUBE_CELL_FRONT_CELL0] = cube->state[CUBE_CELL_BOTTOM_CELL8];
    cube->state[CUBE_CELL_BOTTOM_CELL8] = cube->state[CUBE_CELL_BACK_CELL2];
    cube->state[CUBE_CELL_BACK_CELL2] = tmp;

    return 0;
}

static int16_t
rubiks_rotate_top_cc( rubiks_cube_t * cube )
{
    int16_t tmp;

    // swap the corners
    tmp = cube->state[CUBE_CELL_TOP_CELL0];
    cube->state[CUBE_CELL_TOP_CELL0] = cube->state[CUBE_CELL_TOP_CELL6];
    cube->state[CUBE_CELL_TOP_CELL6] = cube->state[CUBE_CELL_TOP_CELL8];
    cube->state[CUBE_CELL_TOP_CELL8] = cube->state[CUBE_CELL_TOP_CELL2];
    cube->state[CUBE_CELL_TOP_CELL2] = tmp;

    // swap the sides
    tmp = cube->state[CUBE_CELL_TOP_CELL1];
    cube->state[CUBE_CELL_TOP_CELL1] = cube->state[CUBE_CELL_TOP_CELL3];
    cube->state[CUBE_CELL_TOP_CELL3] = cube->state[CUBE_CELL_TOP_CELL7];
    cube->state[CUBE_CELL_TOP_CELL7] = cube->state[CUBE_CELL_TOP_CELL5];
    cube->state[CUBE_CELL_TOP_CELL5] = tmp;

    // swap the other faces that get translated as part of the rotation
    tmp = cube->state[CUBE_CELL_FRONT_CELL0];
    cube->state[CUBE_CELL_FRONT_CELL0] = cube->state[CUBE_CELL_RIGHT_CELL2];
    cube->state[CUBE_CELL_RIGHT_CELL2] = cube->state[CUBE_CELL_BACK_CELL6];
    cube->state[CUBE_CELL_BACK_CELL6] = cube->state[CUBE_CELL_LEFT_CELL8];
    cube->state[CUBE_CELL_LEFT_CELL8] = tmp;

    tmp = cube->state[CUBE_CELL_FRONT_CELL3];
    cube->state[CUBE_CELL_FRONT_CELL3] = cube->state[CUBE_CELL_RIGHT_CELL1];
    cube->state[CUBE_CELL_RIGHT_CELL1] = cube->state[CUBE_CELL_BACK_CELL7];
    cube->state[CUBE_CELL_BACK_CELL7] = cube->state[CUBE_CELL_LEFT_CELL5];
    cube->state[CUBE_CELL_LEFT_CELL5] = tmp;

    tmp = cube->state[CUBE_CELL_FRONT_CELL6];
    cube->state[CUBE_CELL_FRONT_CELL6] = cube->state[CUBE_CELL_RIGHT_CELL0];
    cube->state[CUBE_CELL_RIGHT_CELL0] = cube->state[CUBE_CELL_BACK_CELL8];
    cube->state[CUBE_CELL_BACK_CELL8] = cube->state[CUBE_CELL_LEFT_CELL2];
    cube->state[CUBE_CELL_LEFT_CELL2] = tmp;

    return 0;
}

static int16_t
rubiks_flip( rubiks_cube_t * cube )
{
    int16_t tmp;
    for (uint8_t i = CUBE_CELL_FRONT_CELL0; i < CUBE_CELL_BACK_CELL0; ++i) {
        tmp = cube->state[i];
        cube->state[i] = cube->state[i + CUBE_CELL_BACK_CELL0];
        cube->state[i + CUBE_CELL_LEFT_CELL0] = tmp;
    }

    return 0;
}
