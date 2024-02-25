#include <xc.h>
#include "config.h"

/* __ FUNCTIONS DECLARATION __ */
// Defined in this file

// Defined in other file(s)

unsigned char getWaterState(void) {
    return ADC_WATER_LEVEL > MIN_ALLOWABLE_LEVEL ? 'H' : 'S';
}
