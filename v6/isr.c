#include <xc.h>
#include "config.h"
#define BUZZER PORTBbits.RB3 // Buzzer is connected at RB3

// Constants for timer and buzzer
const unsigned int MAX_COUNT_VALUE_16BIT_TIMER = 65536;

const unsigned int HALF_PERIOD1 = 478;
const unsigned int FULL_PERIOD1 = 1046;
const unsigned int HALF_PERIOD2 = 426;
const unsigned int FULL_PERIOD2 = 1175; 
const unsigned int HALF_PERIOD3 = 379; 
const unsigned int FULL_PERIOD3 = 1319;

const unsigned int halfPeriods[] = {478, 426, 379};
const unsigned int fullPeriods[] = {1046, 1175, 1319};

// Function Declarations
unsigned int getHalfPeriod(void);
unsigned int isr_GetToneIndex(unsigned int currCount);

// - Defined in other file(s)
void dspTask_OnTimer0Interrupt(void);
void usrTask_ActivateGateStop(void);

// Varaibles Declarations
unsigned int tmr1TotalReqdCount;
unsigned int tmr1RunCount;

// Interrupt Service Routine
void __interrupt() isr(void) {
    // Timer0 Interrupt
    if (PIR0bits.TMR0IF == 1) { // Check Timer0 interrupt flag
        PIR0bits.TMR0IF = 0; // Clear Timer0 interrupt flag
        dspTask_OnTimer0Interrupt(); // Call display task on Timer0 interrupt

        // Reload Timer0 preload value for next interrupt
        TMR0H = TIMER0_TMR0H; // Set TMR0H
        TMR0L = TIMER0_TMR0L; // Set TMR0L
    }

    // Timer1 Interrupt
    unsigned int preload_value;
    if (PIR4bits.TMR1IF == 1) {
        PIR4bits.TMR1IF = 0; // Clear Timer1 interrupt flag

        if (tmr1RunCount < tmr1TotalReqdCount) {
            // Toggle the buzzer and update run count
            BUZZER = ~BUZZER;
            tmr1RunCount++;
            // Reload Timer1 again
            preload_value = (MAX_COUNT_VALUE_16BIT_TIMER - getHalfPeriod()); //
            TMR1H = (unsigned char) (preload_value >> 8);
            TMR1L = (unsigned char) preload_value;
        } else {
            // If running count has reached desired, stop the tone
            T1CONbits.TMR1ON = 0; // Stop timer
        }
    }

    // External interrupt
    if (PIR0bits.INTF == 1) { // Check external interrupt flag
        PIR0bits.INTF = 0; // Clear external interrupt flag
        usrTask_ActivateGateStop();
    }
}

// Function to start tone with given half and full periods
void tmr1_MakeTone(unsigned int halfPeriod, unsigned int fullPeriod) {
    unsigned int preload_value = (MAX_COUNT_VALUE_16BIT_TIMER - halfPeriod);

    // Write to the Timer1 register
    TMR1H = (unsigned char) (preload_value >> 8);
    TMR1L = (unsigned char) preload_value;

    // Set total required count and start Timer1
    tmr1TotalReqdCount = fullPeriod;
    tmr1RunCount = 0;
    T1CONbits.TMR1ON = 1; // Start timer
}

// Function to determine the half period based on alarm buzzer count
unsigned int getHalfPeriod(void) {
    unsigned int toneIndex = isr_GetToneIndex(ALARM_BUZZER_COUNT);
    return halfPeriods[toneIndex];
}

// Function to determine the index of the tone based on the current count
unsigned int isr_GetToneIndex(unsigned int currCount) {
    switch (currCount) {
        // Cases for specific counts corresponding to different tones
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
            return 2; // Return index 2 for specific counts
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
            return 1; // Return index 1 for specific counts
        case 1:
        case 10:
        case 23:
            return 0; // Return index 0 for specific counts
        default:
            return 0; // Return default index 0 for unknown counts
    }
}
