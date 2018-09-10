#include "random.h"

void
random_seed( uint16_t seed )
{
    randomSeed( seed );
}

uint16_t
random_int( uint16_t upper_bound )
{
    return random( upper_bound );
}
