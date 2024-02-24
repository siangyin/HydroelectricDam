#include <xc.h>
#include "config.h"

#define SW0 PORTBbits.RB0
#define SW1 PORTBbits.RB1



unsigned char usrTask_CheckGateStatus(void) {
    unsigned char detect = 0;

    if (SW0 == 0 || SW1 == 0) {
        __delay_ms(20);
        if (SW0 == 0 || SW1 == 0) {
            detect = SW0 == 0 ? 1 : 2;
            if (GATE_STATUS == 'S') {
                GATE_STATUS = detect == 1 ? 'O' : 'C';
            } else {
                GATE_STATUS = 'S';
            }

            while (SW0 == 0 || SW1 == 0);
        }
    }


    return detect;
}

