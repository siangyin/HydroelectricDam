#include <xc.h>
#include "config.h"

void initSysTimer0(void) {
    INTCONbits.GIE = 0; // Disable Global Interrupt
    T0CON0 = 0b10010000; // Set T0CON0
    T0CON1 = 0b01000100; // Set T0CON1
    TMR0H = 0x0B; // Set TMR0H
    TMR0L = 0xDC; // Set TMR0L
    PIR0bits.TMR0IF = 0; // Clear Timer0 interrupt flag
    PIE0bits.TMR0IE = 1; // Enable Timer0
    INTCONbits.GIE = 1; // Enable Global Interrupt

}