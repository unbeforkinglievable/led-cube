#ifndef __POINT4D_H__
#define __POINT4D_H__

//-----------------------------------------------
// Includes
//-----------------------------------------------
#include <stdint.h>

//-----------------------------------------------
// Defines
//-----------------------------------------------

//-----------------------------------------------
// Types
//-----------------------------------------------

/**
   @brief enumeration for indexing into a point4d's array representation
 */
typedef enum {
    POINT4D_X,
    POINT4D_Y,
    POINT4D_Z,
    POINT4D_W,
    POINT4D_NENTRIES
} point4d_entry_t;

/**
   @brief struct with fields for point4d's vector representation
 */
typedef struct {
    float x;
    float y;
    float z;
    float w;
} point4d_struct_t;

/**
   @brief a point4d can either be used as an array or as its structure form
 */
typedef union {
    float e[POINT4D_NENTRIES];
    point4d_struct_t v;
} point4d_t;

//-----------------------------------------------
// Includes
//-----------------------------------------------

/**
   @brief vector dot-product
 */
int16_t
point4d_dot( float * result, point4d_t const * const v1, point4d_t const * const v2 );

/**
   @brief vector cross product
 */
int16_t
point4d_cross( point4d_t * result, point4d_t const * const v1, point4d_t const * const v2 );

/**
   @brief vector addition (note: result CAN be one of the inputs (v1 or v2) if desired)
 */
int16_t
point4d_add( point4d_t * result, point4d_t const * const v1, point4d_t const * const v2 );

/**
   @brief vector scaling (note: result CAN be the input (v1) if desired)
 */
int16_t
point4d_scale( point4d_t * result, point4d_t const * const v1, float scale );

/**
   @brief vector normalization (note: result CAN be the input (v1) if desired)
 */
int16_t
point4d_normalize( point4d_t * result, point4d_t const * const v1 );

/**
   @brief calculate the magnitude (length) of a given vector
 */
int16_t
point4d_magnitude( float * result, point4d_t const * const v1 );

/**
   @brief calculate the magitude squared (length squared) of a given vector
   (square root is expensive and this can sometimes be used instead)
 */
int16_t
point4d_magnitude_squared( float * result, point4d_t const * const v1 );

#endif//__POINT4D_H__
