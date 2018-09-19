#ifndef __APP_H__
#define __APP_H__

#include "macros.h"
#include "cube.h"
#include "gradient.h"
#include "plane.h"
#include "point4d.h"
#include "random.h"
#include "rubiks_cube.h"
#include "visualizer.h"

typedef struct {
    gradient_t    gradient;
    cube_t        cube;
    rubiks_cube_t rubiks_cube;
    plane_t       plane;
    point4d_t     rotation_axis;
    volatile uint8_t  running;
} app_t;

extern app_t g_app;

int16_t
app_init( void );

int16_t
app_is_running( void );

int16_t
app_service( void );

void
app_cleanup( void );

#endif//__APP_H__
