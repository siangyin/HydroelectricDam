#include <xc.h>
#include "config.h"

// Function Declarations:
// - Defined in this file:


// - Defined in other file(s):
void initSysPins(void);
void initADC(void);
void initSysTimer0(void);
void initSysTimer1(void);
void initLCD(void);
void updateDisplay(void);
unsigned char usrTask_CheckInput(void);

void main(void) {
    initSysPins(); // Initialize system pins
    initADC(); // Initialize ADC module
    initSysTimer0(); // Initialize Timer0 for periodic interrupts
    initSysTimer1();
    initLCD();

    while (1) {
        updateDisplay();
        usrTask_CheckInput();
    }
}

