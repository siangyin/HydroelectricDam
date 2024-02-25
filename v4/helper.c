#include <xc.h>
#include "config.h"

// Function Declarations:
// - Defined in this file:

unsigned char newWaterStatus=0;
unsigned char newGateStatus=0;

void recordNewWater() {
    if (ADC_WATER_LVL >= MIN_ALLOWABLE_LEVEL) {
        newWaterStatus = 1;
    } else {
        newWaterStatus = 0;
    }
}


//unsigned char includes(const int arr[], int size, unsigned int value) {
//    for (int i = 0; i < size; ++i) {
//        if (arr[i] == value) {
//            return 1;
//        }
//    }
//    return 0;
//}