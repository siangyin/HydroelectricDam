#include <xc.h>
#include "config.h"

#define PUSH_BTN_0 PORTBbits.RB0
#define PUSH_BTN_1 PORTBbits.RB1
#define TOGGLE_SWITCH_2 PORTBbits.RB2
#define TOGGLE_SWITCH_4 PORTBbits.RB4

/* __ FUNCTIONS DECLARATION __ */
// Defined in this file
unsigned char usrTask_ReadInput(unsigned char port);

// Defined in other file(s)

unsigned char usrTask_ReadInput(unsigned char port) {
    unsigned char detectVal = 0;

    switch (port) {
        case 0:
            if (PUSH_BTN_0 == 0) {
                __delay_ms(20);
                if (PUSH_BTN_0 == 0) {
                    detectVal = 1;
                    while (PUSH_BTN_0 == 0);
                }
            }
            break;
        case 1:
            if (PUSH_BTN_1 == 0) {
                __delay_ms(20);
                if (PUSH_BTN_1 == 0) {
                    detectVal = 1;
                    while (PUSH_BTN_1 == 0);
                }
            }
            break;
        case 2:
            detectVal = TOGGLE_SWITCH_2 == 1 ? 1 : 0;
            break;
        case 4:
            detectVal = TOGGLE_SWITCH_4 == 1 ? 1 : 0;
            break;
    }

    return detectVal;

}
