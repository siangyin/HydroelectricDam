#include <xc.h>
#include "config.h"

void initSysPins(void) {
    // Configure analog and digital pins
    ANSELA = 0b00000001; // Set RA0 as analog input
    ANSELC = 0b00000001; // Set RC0 as analog input

    ANSELD = 0b00000000;
    ANSELE = 0b00000000;

    ANSELB = 0b00000000;
    TRISB = 0b00000011; // Set RB0 & RB1 as input pin
    
    TRISA = 0b11000001; // Set RA1, RA2, RA3, RA5 as outputs
    TRISC = 0b00000000; // Set RC0 as output

    TRISD = 0b00001111;
    TRISE = 0b11111100;

}

void initSysExtInt(void) {
    INTCONbits.GIE = 0; // disable global interrupt
    PIR0bits.INTF = 0; // clear external INT flag
    INTPPS = 0x08; // map external INTPPS =0x08(RB0)/ INTPPS =0x09(RB1)
    INTCONbits.INTEDG = 1; // configure for rising edge
    PIE0bits.INTE = 1; // enable external INT interrupt
    INTCONbits.GIE = 1; // enable global interrupt
}

void initSysTimer0(void) {
    INTCONbits.GIE = 0; // Disable Global Interrupt
    T0CON0 = 0b10010000;
    T0CON1 = 0b01000100;
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


