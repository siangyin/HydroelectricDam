#include <xc.h>
#include "config.h"

// Function Declarations:
// - Defined in this file:
void initSysPins(void);

// - Defined in other file(s):
void initSysPins(void);
void initADC(void);
void initSysTimer0(void);
void initSysTimer1(void);
void initSysExtInt(void);
void initLCD(void);
void updateDisplay(void);
void dspTask_UpdateStatus(void);

// Global Variables:
unsigned char GATE_MODE = 0;

void main(void) {
    initSysPins(); // Initialize system pins
    initADC(); // Initialize ADC module
    initSysTimer0(); // Initialize Timer0 for periodic interrupts
    initSysTimer1();
    initSysExtInt();
    initLCD();

    while (1) {
        GATE_MODE = TS2; // to read gate mode input in RB2, Toggle up is for schedule/ down is based on water level
        dspTask_UpdateStatus(); 
    }
}

void initSysPins(void) {
    // Configure analog and digital pins
    ANSELA = 0b00000001; 
    ANSELC = 0b00000001;

    ANSELD = 0b00000000;
    ANSELE = 0b00000000;

    ANSELB = 0b00000000; 
    TRISB = 0b00000111; 

    TRISD = 0b00001111;
    TRISE = 0b11111100;

    TRISA = 0b11000001; 
    TRISC = 0b00000000; 
}