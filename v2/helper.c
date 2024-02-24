#include <xc.h>
#include "config.h"

unsigned char includes(const int arr[], int size, unsigned int value) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == value) {
            return 1;
        }
    }
    return 0;
}