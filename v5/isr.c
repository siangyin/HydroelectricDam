#include <xc.h>
#include "config.h"


const unsigned int MAX_COUNT_VALUE_16BIT_TIMER = 65536;

const unsigned int HALF_PERIOD1 = 478; // 478, 426, 379
const unsigned int FULL_PERIOD1 = 1046; // 1046, 1175, 1319

const unsigned int HALF_PERIOD2 = 426; // 478, 426, 379
const unsigned int FULL_PERIOD2 = 1175; // 1046, 1175, 1319

const unsigned int HALF_PERIOD3 = 379; // 478, 426, 379
const unsigned int FULL_PERIOD3 = 1319; // 1046, 1175, 1319

/* __ FUNCTIONS DECLARATION __ */
// Defined in this file
unsigned int getHalfPeriod(void);

// Defined in other file(s)
void dspTask_OnTimer0Interrupt(void);


unsigned int tmr1_TotalReqdCount;
unsigned int tmr1_RunCount;

void __interrupt() isr(void) {
    if (PIR0bits.TMR0IF == 1) { // Check Timer0 interrupt flag
        PIR0bits.TMR0IF = 0; // Clear Timer0 interrupt flag
        dspTask_OnTimer0Interrupt(); // Call display task on Timer0 interrupt

        // Reload the preload value for next interrupt
        TMR0H = TIMER0_TMR0H;
        TMR0L = TIMER0_TMR0L;
    }

    unsigned int preload_value;
    if (PIR4bits.TMR1IF == 1) {
        PIR4bits.TMR1IF = 0;
        if (tmr1_RunCount < tmr1_TotalReqdCount) {
            BUZZER = ~BUZZER; // Toggle the buzzer stat
            tmr1_RunCount++;
            // Reload Timer1 again
            preload_value = (MAX_COUNT_VALUE_16BIT_TIMER - getHalfPeriod()); //
            TMR1H = (unsigned char) (preload_value >> 8);
            TMR1L = (unsigned char) preload_value;
        } else {
            // If running count has reached desired, stop the tone
            T1CONbits.TMR1ON = 0; // Stop timer
        }
    }
}


void tmr1_makeTone(unsigned int halfPeriod, unsigned int fullPeriod) {
    unsigned int preload_value;

    preload_value = (MAX_COUNT_VALUE_16BIT_TIMER - halfPeriod);

    // Write to the Timer1 register
    TMR1H = (unsigned char) (preload_value >> 8);
    TMR1L = (unsigned char) preload_value;

    tmr1_TotalReqdCount = fullPeriod;
    tmr1_RunCount = 0;
    T1CONbits.TMR1ON = 1; // Start timer
}

unsigned int getHalfPeriod(void) {
    switch (ALARM_BUZZER_COUNT) {
        case 3:
            return HALF_PERIOD1;
        case 2:
           return HALF_PERIOD2;
        case 1:
            return HALF_PERIOD3;
    }
    return 0;
}
