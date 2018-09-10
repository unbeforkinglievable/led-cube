#ifndef __RANDOM_H__
#define __RANDOM_H__

#include <stdint.h>

/**
   @brief generic interface to platform-specific random seed method
 */
void
random_seed( uint16_t seed );

/**
   @brief generic interface to platform-specific random method
 */
uint16_t
random_int( uint16_t upper_bound );

#endif//__RANDOM_H__
