#ifndef __GRADIENT_H__
#define __GRADIENT_H__

#include "point4d.h"

#define GRADIENT_MAX_NENTRIES 32

typedef struct {
    float location;
    point4d_t point;
} gradient_entry_t;

typedef struct {
    uint8_t num_entries;
    gradient_entry_t entries[GRADIENT_MAX_NENTRIES];
} gradient_t;

/**
   @brief initialize a gradient object

   @param graident - input - gradient object to initialize

   @return 0 on success; error code otherwise
 */
int16_t
gradient_init( gradient_t * gradient );

/**
   @brief add a gradient entry

   @param gradient - input - gradient object to update
   @param gradient_entry_t - input - entry to add

   @return 0 on success; error code otherwise
 */
int16_t
gradient_add( gradient_t * gradient, gradient_entry_t const * const entry );

/**
   @brief linearly interpolate between the two closest entries in the gradient based on
   the input location and the location of each of the entries.

   @param gradient - input -
   @param location - input -
   @param point - output -

   @return 0 on success; error code otherwise
 */
int16_t
gradient_interpolate( gradient_t const * const gradient, float location, point4d_t * point );


#endif//__GRADIENT_H__
