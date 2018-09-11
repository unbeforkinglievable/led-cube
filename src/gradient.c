#include <string.h>

#include "gradient.h"

int16_t
gradient_init( gradient_t * gradient )
{
    // zero out the gradient object
    memset( gradient, 0, sizeof(*gradient) );
    return 0;
}

int16_t
gradient_add( gradient_t * gradient, gradient_entry_t const * const entry )
{
    // add an entry
    if (gradient->num_entries >= GRADIENT_MAX_NENTRIES) {
        return -1;
    }

    // make sure the location is sane
    if ((entry->location < 0) || (entry->location > 1)) {
        return -2;
    }

    // if the gradient is empty, just put it at the beginning
    if (gradient->num_entries == 0) {
        memcpy( &gradient->entries[0], entry, sizeof(*entry) );
        gradient->num_entries += 1;
        return 0;
    }

    // if the location indicates it is in the middle, insert it appropriately
    for (uint8_t i = 0; i < gradient->num_entries; ++i) {
        if (gradient->entries[i].location > entry->location) {
            memmove( &gradient->entries[i], &gradient->entries[i + 1],
                     (gradient->num_entries - i) * sizeof(*entry) );
            memcpy( &gradient->entries[i], entry, sizeof(*entry) );
            gradient->num_entries += 1;
            return 0;
        }
    }

    // if the location indicates it is at the end, put at the end
    memcpy( &gradient->entries[gradient->num_entries], entry, sizeof(*entry) );
    gradient->num_entries += 1;
    return 0;
}

int16_t
gradient_interpolate( gradient_t const * const gradient, float location, point4d_t * point )
{
    uint8_t index;
    float weight;
    point4d_t scaled[2];

    // need at least two points to interpolate between
    if (gradient->num_entries < 2) {
        return -1;
    }

    // first entry must be at 0.0
    // last entry must be at 1.0
    if ((ABS( gradient->entries[0].location ) > 0.001) ||
        (ABS( gradient->entries[gradient->num_entries].location - 1.0 ) > 0.001)) {
        return -2;
    }

    // if the location is less than 0, just take the value at the first point
    if (location < 0) {
        memcpy( point, &gadient->entries[0].point, sizeof(*point) );
        return 0;
    }

    // if the location is greater than 1, just take the value at the last point
    if (location > 1) {
        memcpy( point, &gradient->entries[gradient->num_entries].point, sizeof(*point) );
        return 0;
    }

    // find the indices surrounding the given location value
    index = 0;
    for (index = 1; index < gradient->num_entries; ++index) {
        if (location < gradient->entries[index].location) {
            break;
        }
    }

    // we need to interpolate between (index - 1) and (index)
    // interpolated = weight * entry[index] + (1 - weight) * entry[index - 1]
    weight = ((gradient->entries[index].location - location) /
              (gradient->entries[index].location - gradient->entries[index - 1].location));

    point4d_scale( &scaled[0], gradient->entries[index].point, weight );
    point4d_scale( &scaled[1], gradient->entries[index - 1].point, 1.0 - weight );
    point4d_add( point, &scaled[0], &scaled[1] );

    return 0;
}
