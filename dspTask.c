#include <xc.h>
#include "config.h"

// Function Declarations:

// - Defined in other file(s):
unsigned int adc_GetConversion(void);
void display_WaterLvl_OnSevSeg(unsigned int waterLevel);
void display_Msg_OnLCD(const char * line1, const char * line2);

// Global Variables:
unsigned char updateADC = 0; // Flag to indicate ADC update
unsigned char hour = 0, min = 0, sec = 0; // Variables for time tracking
unsigned int ADC_WATER_LVL; // Result of ADC conversion

// This function is called by the ISR whenever there is a 1-second interrupt:

void dspTask_OnTimer0Interrupt(void) {
    sec++; // Increment seconds

    if (sec > 59) {
        sec = 0;
        min++;
        if (min > 59) {
            min = 0;
            hour++;
            if (hour > 23) {
                hour = 0;
            }
        }
    }

    updateADC = 1;
}

void dspTask_OnTimer0(void) {
    if (updateADC == 1) {
        ADC_WATER_LVL = adc_GetConversion(); // Get ADC reading
        
        if (ADC_WATER_LVL > 800) {
            display_Msg_OnLCD("gate:open", "water lvl:max");

        } else if (ADC_WATER_LVL < 200) {
            display_Msg_OnLCD("gate:open", "water lvl:low");

        } else {
            display_Msg_OnLCD("gate:open", "water lvl:safe");
        }

        updateADC = 0; // Reset flag for next reading
    }

    display_WaterLvl_OnSevSeg(ADC_WATER_LVL); // Display ADC result on 7-segment display


}




