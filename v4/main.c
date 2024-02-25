#include <xc.h>
#include "config.h"

/* __ FUNCTIONS DECLARATION __ */
// Defined in this file
void usrTask_CheckInputRB1(void);

// Defined in other file(s)
void initSysPins(void);
void initSysExtInt(void);
void initSysTimer0(void);
void initSysTimer1(void);

void initLCD(void);
void initADC(void);
void updateDisplay(void);



void main(void) {
    initSysPins(); // Initialise the port pins
    initSysExtInt();
    initSysTimer0(); // Initialise Timer 0
    initSysTimer1(); // Initialise Timer 0
    initADC();
    initLCD();
    
    while (1) {
        
        updateDisplay();
        usrTask_CheckInputRB1();
        
    }
} 


void usrTask_CheckInputRB1(void) {
    if (PB1 == 0) { // check SW1 for the first time
        __delay_ms(20); // delay contact bounce period
        if (PB1 == 0) { // check SW1 for the second time
            while (PB1 == 0); // wait for switch to be released
            PORTAbits.RA1 = 1; // turn on RA1 for 5s
            __delay_ms(5000); // delay for 5s
            PORTAbits.RA1 = 0; // turn off RA1
        }
    }
}