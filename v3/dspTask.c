#include <xc.h>
#include "config.h"

#define LED1 PORTAbits.RA1
#define LED2 PORTAbits.RA2
#define LED3 PORTAbits.RA3

/* __ FUNCTIONS DECLARATION __ */
// Defined in this file
void dspTask_LedController(unsigned char led1, unsigned char led2, unsigned char led3);

// Defined in other file(s)
unsigned int sysTask_GetAdcConversion(void);
void dspTask_on7Segment(unsigned int result);

// Global Variables:
unsigned char updateADC = 0; // Flag to indicate ADC update

unsigned char timer0_sec = 0; // Variables for time tracking
unsigned int ADC_WATER_LVL; // Result of ADC conversion

void dspTask_LedController(unsigned char led1, unsigned char led2, unsigned char led3) {
    LED1 = led1 == 1 ? 1 : 0;
    LED2 = led2 == 1 ? 1 : 0;
    LED3 = led3 == 1 ? 1 : 0;
}




// This function is called by the ISR whenever there is a 1-second interrupt:

void dspTask_OnTimer0Interrupt(void) {
    timer0_sec++;

    if (timer0_sec > 59) {
        timer0_sec = 0;
    }

    updateADC = 1;
  ADC_WATER_LVL=sysTask_GetAdcConversion(); // Get ADC reading
         //ADC_WATER_LVL=((sysTask_GetAdcConversion()/1023.0)*100); // Get ADC reading
    updateADC = 0; // Reset flag for next reading
   
}

void dspTask_updateDisplay(void) {
    if (updateADC == 1) {
         
    }
    
    dspTask_on7Segment(ADC_WATER_LVL);
}

//void updateDisplay(void) {
//    // Update the display based on the current display mode (seven-segment or LCD)
//    if (displayMode == 0) {
//        // Update seven-segment display with adcValue
//        // Toggle seven-segment display enable pins
//    } else {
//        // Update LCD with adcValue
//        // Communicate with LCD module to send adcValue
//    }
//}