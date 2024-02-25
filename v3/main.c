#include <xc.h>
#include "config.h"

/* __ FUNCTIONS DECLARATION __ */
// Defined in this file


// Defined in other file(s)
void initSysPins(void);
void initSysTimer0(void);
void initADC(void);

unsigned char usrTask_ReadInput(unsigned char port);
//void dspTask_updateDisplay(void);
void dspTask_on7Segment(unsigned int result);

void main(void) {
    initSysPins(); // initialise the port pins
    initADC(); // Initialize ADC module
    initSysTimer0(); // Initialize Timer0 for periodic interrupts
    
    
    while (1) {
        if(usrTask_ReadInput(2)==1){//schedule
            //dspTask_LedController(1,0,0);
        }else{//auto
             //dspTask_on7Segment(ADC_WATER_LVL); // Display ADC result on 7-segment display
        }

        dspTask_on7Segment(ADC_WATER_LVL);
        //dspTask_updateDisplay();
    }
}
