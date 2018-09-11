#ifndef __PLANE_H__
#define __PLANE_H__

//-----------------------------------------------
// Includes
//-----------------------------------------------
#include "point4d.h"

//-----------------------------------------------
// Defines
//-----------------------------------------------

//-----------------------------------------------
// Types
//-----------------------------------------------

/**
   @brief a plane needs 3 points to define it.

   I'm chosing to represent the three points as:
   1) a translation from the global origin 0,0,0
   2) a unit vector away from the translation point indicating the "X" axis
   3) a unit vector away from the translation point indication the "Y" axis, perpendicular to "X"

   The normal (x cross y) is also stored here so we have it as it's used in projection
   computations and is quite useful.

   The x, y, z (normal) and translation are really then a coordinate frame and might make sense
   to represent as a translation vector and a rotation matrix.  This representation
   might change in the future, but it meets my needs for now.
 */
typedef struct {
    point4d_t x_axis;
    point4d_t y_axis;
    point4d_t normal;
    point4d_t translation;
} plane_t;

//-----------------------------------------------
// Global method declarations
//-----------------------------------------------

/**
   @brief
 */
int16_t
plane_init( plane_t * plane );

/**
   @brief project point into plane
   @param plane - input - plane object into which we project the point
   @param point - input - point to project
   @param projection - output - resulting projection

   @return 0 on success; error code otherwise
 */
int16_t
plane_project( plane_t const * const plane, point4d_t const * const point, point4d_t * projection );

/**
   @brief translate the plane along some vector
   @param plane - input - plane object to translate
   @param translation - input - vector along which to translate the plane

   @return 0 on success; error code otherwise
 */
int16_t
plane_tranlate( plane_t * plane, point4d_t const * const translation );

/**
   @brief rotate the plane about the given rotation_axis for the given rotation_angle
   @param plane - input - plane object to rotate
   @param rotation_axis - input - NORMALIZED axis about which we want to rotate
   @param rotation_angle - input - RADIANS angle to rotate (must be in range [-2pi, 2pi])

   @return 0 on success; error code otherwise
 */
int16_t
plane_rotate( plane_t * plane, point4d_t const * const rotation_axis, float rotation_angle );

#endif//__PLANE_H__
