#include <xc.h>
#include "config.h"

void initSysPins(void) {
    ANSELA = 0b00000001;
    ANSELB = 0b00000000;
    ANSELC = 0b00000001;

    TRISA = 0b11000001;
    TRISB = 0b11111111;
    TRISC = 0b00000000; // Set RC0 as output
}

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

// Function to initialise the ADC

void initADC(void) {
    // Configure ADC reference, clock, and acquisition time
    ADREF = 0b00000000; // Set VREF+ and VREF- to VSS and VDD
    ADCLK = 0b00000011; // Set TAD = 2 us
    ADACQ = 0b00000000; // TACQ to be manually inserted
    ADCON0 = 0b10000100; // Enable ADC, single conversion, FOSC clock, result is right justified
}

// Function to start ADC conversion and get the results

unsigned int sysTask_GetAdcConversion(void) {
    unsigned int result;

    ADPCH = 0b00000000; // Select channel ANA0 for input at RA0
    __delay_us(2); // Add 2 us TACQ manually
    ADCON0bits.ADGO = 1; // Start conversion
    while (ADCON0bits.ADGO == 1); // Wait for conversion to complete
    result = ADRESH * 256 + ADRESL; // Get the results

    return result; // Return the result
}

void initSysExtInt(void) {
    INTCONbits.GIE = 0; //  Disable Global Interrupt
    PIR0bits.INTF = 0; // clear external INT flag
    INTPPS = 0x08; // map external INT to RB0
    INTCONbits.INTEDG = 1; // configure for rising edge
    PIE0bits.INTE = 1; // enable external INT interrupt
    INTCONbits.GIE = 1; // enable global interrupt
}