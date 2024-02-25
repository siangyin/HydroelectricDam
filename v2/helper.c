#include <xc.h>
#include "config.h"

unsigned char newWaterStatus=0;
unsigned char newGateStatus=0;

void updateNewState(unsigned int adcResult) {
    if (adcResult >= MIN_ALLOWABLE_LEVEL) {
        newWaterStatus = 1;
        newGateStatus = 4;
    } else {
        newWaterStatus = 0;
        newGateStatus = 2;
    }
}


unsigned char includes(const int arr[], int size, unsigned int value) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == value) {
            return 1;
        }
    }
    return 0;
}