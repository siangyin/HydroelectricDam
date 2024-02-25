#include <xc.h>
#include "config.h"

/* __ FUNCTIONS DECLARATION __ */
// Defined in this file


// Defined in other file(s)
void initSysPins(void);
void initSysTimer0(void);
void initSysTimer1(void);
void initLCD(void);
void initADC(void);

void dspTask_showStatus(void);
void onLEDs(unsigned char led1, unsigned char led2, unsigned char led3);

void main(void) {
    initSysPins(); // Initialize system pins
    initLCD();
    initADC(); // Initialize ADC module
    initSysTimer0(); // Initialize Timer0 for periodic interrupts
    initSysTimer1();
    
    while (1) {
        dspTask_showStatus(); // Call display task for updating 7-segment display

       

    }
}
