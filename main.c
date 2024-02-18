#include <xc.h>
#include "config.h"

// Function Declarations:
// - Defined in this file:
void initSysPins(void);

// - Defined in other file(s):
void initADC(void);
void initSysTimer0(void);
void dspTask_OnSevSeg(void);

void main(void) {
    initSysPins();
    initADC();
    initSysTimer0();

    while (1) {
        dspTask_OnSevSeg();
    }
}

void initSysPins(void) {
    ANSELA = 0b00000001;
    ANSELC = 0b00000001;
    TRISA = 0b11000001;
    TRISC = 0b00000000;
}