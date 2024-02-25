#include <xc.h>
#include "config.h"

// FUNCTIONS DECLARATIONS:

// <-- FUNCTIONS IN THIS FILE -->:

// <-- FUNCTIONS DEFINED IN OTHER FILE -->:
void extint_Timer0Task(void);

void __interrupt() isr(void) {
    if (PIR0bits.TMR0IF == 1) { // Check Timer0 interrupt flag
        PIR0bits.TMR0IF = 0; // Clear Timer0 interrupt flag
        
        extint_Timer0Task(); // increment the number of INT count
        
        // reload the preload value for next interrupt
        TMR0H=0x0B;
        TMR0L=0x0c;
    }
}