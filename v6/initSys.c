#include <xc.h>
#include "config.h"

// Initialize Timer0 module
void initSysTimer0(void) {
    INTCONbits.GIE = 0;       // Disable Global Interrupt
    T0CON0 = 0b10010000;      // Set T0CON0
    T0CON1 = 0b01000101;      // Set T0CON1
    TMR0H = TIMER0_TMR0H;     // Set TMR0H
    TMR0L = TIMER0_TMR0L;     // Set TMR0L
    PIR0bits.TMR0IF = 0;      // Clear Timer0 interrupt flag
    PIE0bits.TMR0IE = 1;      // Enable Timer0
    INTCONbits.GIE = 1;       // Enable Global Interrupt
}

// Initialize Timer1 module
void initSysTimer1(void) {
    INTCONbits.GIE = 0;       // Disable Global Interrupt
    INTCONbits.PEIE = 1;      // Enable Peripheral Interrupt
    T1CON = 0b00000010;       // Disable Timer1 first. Pre-scaler is 1
    T1CLK = 0b00000001;
    PIE4bits.TMR1IE = 1;      // Enable Timer1 interrupt
    PIR4bits.TMR1IF = 0;      // Clear Timer1 interrupt flag
    INTCONbits.GIE = 1;       // Enable Global Interrupt
}

// Initialize External Interrupt module
void initSysExtInt(void) {
    INTCONbits.GIE = 0;       // Disable Global Interrupt
    PIR0bits.INTF = 0;        // Clear external INT flag
    INTPPS = 0x09;            // Map external INTPPS =0x08(RB0)/ INTPPS =0x09(RB1)
    INTCONbits.INTEDG = 1;    // Configure for rising edge
    PIE0bits.INTE = 1;        // Enable external INT interrupt
    INTCONbits.GIE = 1;       // Enable Global Interrupt
}
