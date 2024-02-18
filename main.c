#include <xc.h>
#include "config.h"

// Function Declarations:
// - Defined in this file:
void initSysPins(void);

// - Defined in other file(s):
void initADC(void);
void initSysTimer0(void);
void initLCD(void);
void dspTask_OnTimer0(void);

void main(void) {
    initSysPins(); // Initialize system pins
    initADC(); // Initialize ADC module
    initSysTimer0(); // Initialize Timer0 for periodic interrupts
    initLCD();

    while (1) {
        dspTask_OnTimer0(); // Call display task for updating 7-segment display
        
    }
}

void initSysPins(void) {
    // Configure analog and digital pins
    ANSELA = 0b00000001; // Set RA0 as analog input
    ANSELC = 0b00000001; // Set RC0 as analog input

    ANSELD = 0b00000000;
    ANSELE = 0b00000000;


    TRISA = 0b11000001; // Set RA1, RA2, RA3, RA5 as outputs
    TRISC = 0b00000000; // Set RC0 as output

    TRISD = 0b00001111;
    TRISE = 0b11111100;
}