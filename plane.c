#include <string.h>
#include <math.h>

#include "plane.h"

int16_t
plane_init( plane_t * plane )
{
    if (plane == NULL) {
        return -1;
    }

    memset( plane, 0, sizeof(*plane) );
    plane->x_axis.e[POINT4D_X] = 1.0;
    plane->y_axis.e[POINT4D_Y] = 1.0;
    plane->normal.e[POINT4D_Z] = 1.0;
    return 0;
}

int16_t
plane_project( plane_t const * const plane, point4d_t const * const point, point4d_t * projection )
{
    float origin_distance;
    float perpendicular_distance;
    point4d_t perpendicular_translation;
    if (plane == NULL || point == NULL || projection == NULL) {
        return -1;
    }

    point4d_dot( &origin_distance, &plane->normal, &plane->translation );

    point4d_dot( &perpendicular_distance, &plane->normal, point );
    perpendicular_distance -= origin_distance;

    point4d_scale( &perpendicular_translation, &plane->normal, -perpendicular_distance );
    point4d_add( projection, point, &perpendicular_translation );

    return 0;
}

int16_t
plane_translate( plane_t * plane, point4d_t const * const translation )
{
    if (plane == NULL || translation == NULL) {
        return -1;
    }

    point4d_add( &plane->translation, translation, &plane->translation );

    return 0;
}

int16_t
plane_rotate( plane_t * plane, point4d_t const * const rotation_axis, float rotation_angle )
{
    point4d_t part1;
    point4d_t part2;
    point4d_t part3;
    float cos_angle;
    float sin_angle;
    float dot_product;

    if (plane == NULL || rotation_axis == NULL) {
        return -1;
    }

    if (ABS(rotation_angle) > (2 * M_PI)) {
        return -2;
    }

    // precompute the sin/cos so we don't have to do this more than necessary
    cos_angle = cos( rotation_angle );
    sin_angle = sin( rotation_angle );

    // Rogrigues formula
    // https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula
    point4d_scale( &part1, &plane->x_axis, cos_angle );
    point4d_cross( &part2, &plane->x_axis, rotation_axis );
    point4d_scale( &part2, &part2, sin_angle );
    point4d_dot( &dot_product, rotation_axis, &plane->x_axis );
    point4d_scale( &part3, rotation_axis, dot_product * (1 - cos_angle) );

    point4d_add( &part1, &part1, &part2 );
    point4d_add( &plane->x_axis, &part1, &part3 );

    // Rogrigues formula
    // https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula
    point4d_scale( &part1, &plane->y_axis, cos_angle );
    point4d_cross( &part2, &plane->y_axis, rotation_axis );
    point4d_scale( &part2, &part2, sin_angle );
    point4d_dot( &dot_product, rotation_axis, &plane->y_axis );
    point4d_scale( &part3, rotation_axis, dot_product * (1 - cos_angle) );

    point4d_add( &part1, &part1, &part2 );
    point4d_add( &plane->y_axis, &part1, &part3 );

    // re-derive the normal...or we could just apply the Rodrigues formula again...
    point4d_cross( &plane->normal, &plane->x_axis, &plane->y_axis );

    return 0;
}
