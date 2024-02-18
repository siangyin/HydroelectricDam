#include <xc.h>
#include "config.h"

// Function Declarations:
// - Defined in other file(s):
unsigned int adc_GetConversion(void);
void seg_DspAll(unsigned int result);

// Global Variables:
unsigned char updateADC = 0; // Flag to indicate ADC update
unsigned char hour = 0, min = 0, sec = 0; // Variables for time tracking
unsigned int adcResult = 0; // Result of ADC conversion

// This function is called by the ISR whenever there is a 1-second interrupt:

void dspTask_OnTimer0Interrupt(void) {
    sec++; // Increment seconds
    if (sec > 59) {
        sec = 0;
        min++;
        if (min > 59) {
            min = 0;
            hour++;
            if (hour > 23)
                hour = 0;
        }
    }
    // Check if 2 seconds have passed, set updateADC flag accordingly
    if ((sec == 0) || (sec % 2 == 0)) {
        updateADC = 1; // Set the flag to 1
    }
}

void dspTask_OnSevSeg(void) {
    if (updateADC == 1) {
        adcResult = adc_GetConversion(); // Get ADC reading
        updateADC = 0; // Reset flag for next reading
    }
    seg_DspAll(adcResult); // Display ADC result on 7-segment display
}