#include <xc.h>
#include "config.h"

#define SW0 PORTBbits.RB0
#define SW1 PORTBbits.RB1


// Function Declarations:
// - Defined in this file:
void initSysPins(void);
//unsigned char detSW0(void);
unsigned char detSW1(void);
// void tmr1_StartTone(unsigned int halfPeriod, unsigned int fullPeriod);


// - Defined in other file(s):
void initADC(void);
void initSysTimer0(void);
void initSysTimer1(void);
void initLCD(void);
void dspTask_OnTimer0(void);

void main(void) {
    initSysPins(); // Initialize system pins
    initADC(); // Initialize ADC module
    initSysTimer0(); // Initialize Timer0 for periodic interrupts
    initSysTimer1();
    initLCD();

    while (1) {
        dspTask_OnTimer0(); // Call display task for updating 7-segment display

        if (detSW1() == 1) {
            //
        }

    }
}


//unsigned char detSW0(void) {
//  unsigned char detect = 0;
//
//  if (SW0 == 0) {
//    __delay_ms(20);
//    if (SW0 == 0) {
//      detect = 1;
//      while (SW0 == 0);
//    }
//  }
//
//  return detect;
//}

unsigned char detSW1(void) {
    unsigned char detect = 0;

    if (SW1 == 0) {
        __delay_ms(20);
        if (SW1 == 0) {
            detect = 1;
            while (SW1 == 0);
        }
    }

    return detect;
}

void initSysPins(void) {
    // Configure analog and digital pins
    ANSELA = 0b00000001; // Set RA0 as analog input
    ANSELC = 0b00000001; // Set RC0 as analog input

    ANSELD = 0b00000000;
    ANSELE = 0b00000000;

    ANSELB = 0b00000000;

    TRISA = 0b11000001; // Set RA1, RA2, RA3, RA5 as outputs
    TRISC = 0b00000000; // Set RC0 as output

    TRISD = 0b00001111;
    TRISE = 0b11111100;

    TRISB = 0b00000011; // Set RB0 & RB1 as input pin
}