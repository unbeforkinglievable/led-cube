#ifndef __VISUALIZER_H__
#define __VISUALIZER_H__

#include "cube.h"

int16_t
visualizer_init( void );

int16_t
visualizer_visualize( cube_t * cube );

int16_t
visualizer_close( void );

#endif//__VISUALIZER_H__
