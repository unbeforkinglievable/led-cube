#ifndef __POINT4D_H__
#define __POINT4D_H__

#include <stdint.h>

typedef enum {
    POINT4D_X,
    POINT4D_Y,
    POINT4D_Z,
    POINT4D_W,
    POINT4D_NENTRIES
} point4d_entry_t;

typedef struct {
    float x;
    float y;
    float z;
    float w;
} point4d_struct_t;

typedef union {
    float e[POINT4D_NENTRIES];
    point4d_struct_t v;
} point4d_t;

int16_t
point4d_dot( float * result, point4d_t const * const v1, point4d_t const * const v2 );

int16_t
point4d_cross( point4d_t * result, point4d_t const * const v1, point4d_t const * const v2 );

int16_t
point4d_add( point4d_t * result, point4d_t const * const v1, point4d_t const * const v2 );

int16_t
point4d_scale( point4d_t * result, point4d_t const * const v1, float scale );

int16_t
point4d_normalize( point4d_t * result, point4d_t const * const v1 );

int16_t
point4d_magnitude( float * result, point4d_t const * const v1 );

int16_t
point4d_magnitude_squared( float * result, point4d_t const * const v1 );

#endif//__POINT4D_H__
