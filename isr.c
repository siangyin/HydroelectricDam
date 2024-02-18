#include <xc.h>
#include "config.h"
#define BUZZER PORTBbits.RB3 // Buzzer is connected at RB3

const unsigned int MAX_COUNT_VALUE_16BIT_TIMER = 65536;

const unsigned int HALF_PERIOD1 = 478; // 478, 426, 379
const unsigned int FULL_PERIOD1 = 1046; // 1046, 1175, 1319

const unsigned int HALF_PERIOD2 = 426; // 478, 426, 379
const unsigned int FULL_PERIOD2 = 1175; // 1046, 1175, 1319

const unsigned int HALF_PERIOD3 = 379; // 478, 426, 379
const unsigned int FULL_PERIOD3 = 1319; // 1046, 1175, 1319


// Function Declarations
// - Defined in other file(s)
void dspTask_OnTimer0Interrupt(void);

unsigned int tmr1_TotalReqdCount;
unsigned int tmr1_RunCount;

void __interrupt() isr(void) {
    if (PIR0bits.TMR0IF == 1) { // Check Timer0 interrupt flag
        PIR0bits.TMR0IF = 0; // Clear Timer0 interrupt flag
        dspTask_OnTimer0Interrupt(); // Call display task on Timer0 interrupt

        // Reload the preload value for next interrupt
        TMR0H = 0x0B;
        TMR0L = 0x0C;
    }

    unsigned int preload_value;
    if (PIR4bits.TMR1IF == 1) {
        PIR4bits.TMR1IF = 0;
        if (tmr1_RunCount < tmr1_TotalReqdCount) {
            BUZZER = ~BUZZER; // Toggle the buzzer stat
            tmr1_RunCount++;
            // Reload Timer1 again
            preload_value = (MAX_COUNT_VALUE_16BIT_TIMER - HALF_PERIOD1); //
            TMR1H = (unsigned char) (preload_value >> 8);
            TMR1L = (unsigned char) preload_value;
        } else {
            // If running count has reached desired, stop the tone
            T1CONbits.TMR1ON = 0; // Stop timer
        }
    }


    // external interrupt
    if (PIR0bits.INTF == 1) { // check INT flag
        PIR0bits.INTF = 0; // clear INT flag
        PORTAbits.RA0 = ~PORTAbits.RA0; // toggle LED at RA0
    }
}

void tmr1_StartTone(unsigned int halfPeriod, unsigned int fullPeriod) {
    unsigned int preload_value;

    preload_value = (MAX_COUNT_VALUE_16BIT_TIMER - halfPeriod);

    // Write to the Timer1 register
    TMR1H = (unsigned char) (preload_value >> 8);
    TMR1L = (unsigned char) preload_value;

    tmr1_TotalReqdCount = fullPeriod;
    tmr1_RunCount = 0;
    T1CONbits.TMR1ON = 1; // Start timer
}