#include "point4d.h"

int16_t
point4d_dot( float * result, point4d_t const * const v1, point4d_t const * const v2 )
{
    if (result == NULL || v1 == NULL || v2 == NULL) {
        return -1;
    }

    *result = 0.0;
    for (uint8_t i = 0; i < POINT4D_NENTRIES; ++i) {
        *result += v1->e[i] * v2->e[i];
    }

    return 0;
}

int16_t
point4d_cross( point4d_t * result, point4d_t const * const v1, point4d_t const * const v2 )
{
    if (result == NULL || v1 == NULL || v2 == NULL) {
        return -1;
    }

    result->e[POINT4D_X] = ((v1->e[POINT4D_Y] * v2->e[POINT4D_Z]) -
                            (v1->e[POINT4D_Z] * v2->e[POINT4D_Y]));
    result->e[POINT4D_Y] = ((v1->e[POINT4D_Z] * v2->e[POINT4D_X]) -
                            (v1->e[POINT4D_X] * v2->e[POINT4D_Z]));
    result->e[POINT4D_Z] = ((v1->e[POINT4D_X] * v2->e[POINT4D_Y]) -
                            (v1->e[POINT4D_Y] * v2->e[POINT4D_Z]));
    result->e[POINT4D_W] = 0;

    return 0;
}

int16_t
point4d_add( point4d_t * result, point4d_t const * const v1, point4d_t const * const v2 )
{
    for (uint8_t i = 0; i < POINT4D_NENTRIES; ++i) {
        result->e[i] = v1->e[i] + v2->e[i];
    }

    return 0;
}

int16_t
point4d_scale( point4d_t * result, point4d_t const * const v1, float scale )
{
    for (uint8_t i = 0; i < POINT4D_NENTRIES; ++i) {
        result->e[i] = v1->e[i] * scale;
    }

    return 0;
}

int16_t
point4d_magnitude_squared( float * result, point4d_t const * const v1 )
{
    *result = 0.0;
    for (uint8_t i = 0; i < POINT4D_NENTRIES; ++i) {
        *result += v1->e[i] * v1->e[i];
    }

    return 0;
}

int16_t
point4d_magnitude( float * result, point4d_t const * const v1 )
{
    point4d_magnitude_squared( result, v1 );
    *result = sqrt( *result );

    return 0;
}

int16_t
point4d_normalize( point4d_t * result, point4d_t const * const v1 )
{
    float magnitude;
    point4d_magnitude( &magnitude, v1 );
    point4d_scale( result, v1, 1.0 / magnitude );

    return 0;
}
