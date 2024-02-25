#include <xc.h>
#include "config.h"

/* __ FUNCTIONS DECLARATION __ */
// Defined in this file


// Defined in other file(s)


void initSysPins(void) {
    // Configure analog and digital pins
    ANSELA = 0b00000001; // Set RA0 as analog input
    ANSELC = 0b00000001; // Set RC0 as analog input

    ANSELD = 0b00000000; // for lcd
    ANSELE = 0b00000000; // for lcd

    ANSELB = 0b00000000; // Set RB1 as digital input // buzzer and input
    TRISB = 0b00010111; // Set RB1 as input pin // buzzer and input

    TRISD = 0b00001111; // for lcd
    TRISE = 0b11111100; // for lcd

    TRISA = 0b11000001; // Set RA1, RA2, RA3, RA5 as outputs
    TRISC = 0b00000000; // Set RC0 as output
}

void initSysTimer0(void) {
    INTCONbits.GIE = 0; // Disable Global Interrupt
    T0CON0 = 0b10010000; // Set T0CON0
    T0CON1 = 0b01000100; // Set T0CON1
    TMR0H = TIMER0_TMR0H;
    TMR0L = TIMER0_TMR0L;
    PIR0bits.TMR0IF = 0; // Clear Timer0 interrupt flag
    PIE0bits.TMR0IE = 1; // Enable Timer0
    INTCONbits.GIE = 1; // Enable Global Interrupt
}

void initSysTimer1(void) {
    INTCONbits.GIE = 0;
    INTCONbits.PEIE = 1;
    T1CON = 0b00000010; // Disable Timer1 first. Pre-scaler is 1
    T1CLK = 0b00000001;
    PIE4bits.TMR1IE = 1; // Let Timer1 interrupt be enabled.
    PIR4bits.TMR1IF = 0;
    INTCONbits.GIE = 1;
}

