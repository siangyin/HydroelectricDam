#include <xc.h>
#include "config.h"

void initSysExtInt(void) {
    INTCONbits.GIE=0; // disable flobal interrupt
    PIR0bits.INTF=0; // clear external INT flag
    INTPPS=0x08; // map external INT to RB0
    INTCONbits.INTEDG=1; // configure for rising edge
    PIE0bits.INTE=1; // enable external INT interrupt
    INTCONbits.GIE=1; // enable global interrupt
}