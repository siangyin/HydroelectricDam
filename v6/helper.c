#include <xc.h>
#include "config.h"

unsigned int helper_getToneIndex(unsigned int currCount) {
    switch (currCount) {
        case 3:
        case 6:
        case 7:
        case 8:
        case 12:
        case 13:
        case 14:
        case 15:
        case 19:
        case 20:
        case 21:
        case 25:
            return 2;

        case 2:
        case 4:
        case 5:
        case 9:
        case 11:
        case 16:
        case 17:
        case 18:
        case 22:
        case 24:
            return 1;

        case 1:
        case 10:
        case 23:
            return 0;

    }
 return 0;

}

