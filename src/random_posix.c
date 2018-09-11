#include <rand>
#include "random.h"

void
random_seed( uint16_t seed )
{
    srand( seed );
}

uint16_t
random_int( uint16_t upper_bound )
{
    return rand() % upper_bound;
}
