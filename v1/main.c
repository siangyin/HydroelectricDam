#include <xc.h>
#include "config.h"

// FUNCTIONS DECLARATIONS:

// <-- FUNCTIONS IN THIS FILE -->:
void initSysPins(void);

// <-- FUNCTIONS DEFINED IN OTHER FILE -->:
void initSysTimer0(void);
void toggleLEDs(void);
void display_7Segment(char position, unsigned int digit);
unsigned int extint_GetWaterLevel(void);


void main(void) {
    initSysPins(); // Initialise the port pins
    initSysTimer0(); // Initialise Timer 0


    while (1) {

        unsigned int waterLevel = extint_GetWaterLevel();
        unsigned int dig0 = waterLevel % 10;
        unsigned int dig1 = (waterLevel / 10) % 10;
        
        display_7Segment(1,dig1);
        display_7Segment(2,dig0);
        
        toggleLEDs();


    }
}

void initSysPins(void) {
    ANSELA = 0b00000000; // Set all PORT pins are digital
    ANSELB = 0b00000000; // Set all PORT pins are digital
    ANSELC = 0b00000000; // Set all PORT pins are digital
    TRISA = 0b11000000; // Set RA5, RA4, and all LEDs as output, rest unused pins as inputs
    TRISB = 0b11111111; // Set all Port B pins as inputs
    TRISC = 0b00000000; // Set all Port C pins as outputs
}
