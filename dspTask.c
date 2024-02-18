#include <xc.h>
#include "config.h"

#define INITIAL_CLOSE_TIME 10 // Example value for INITIAL_CLOSE_TIME
#define INITIAL_OPEN_TIME 10 // Example value for INITIAL_OPEN_TIME

// Function Declarations:
void sysTask_GateController(void);

// - Defined in other file(s):
unsigned int adc_GetConversion(void);
void display_WaterLvl_OnSevSeg(unsigned int waterLevel);
void display_Msg_OnLCD(unsigned char gate, unsigned int waterLevel);

// Global Variables:

unsigned char updateADC = 0; // Flag to indicate ADC update
unsigned char hour = 0, min = 0, sec = 0; // Variables for time tracking
unsigned int ADC_WATER_LVL; // Result of ADC conversion
unsigned char GATE_STATUS = 'C'; // O as open, C as close, S stop

unsigned char closeTimer = INITIAL_CLOSE_TIME;
unsigned char openTimer = INITIAL_OPEN_TIME;

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

    if (GATE_STATUS == 'C') {
        if (closeTimer > 0) {
            closeTimer--;
        } else {
            sysTask_GateController();
            closeTimer = INITIAL_CLOSE_TIME;
        }

    } else if(GATE_STATUS == 'O'){
        if (openTimer > 0) {
            openTimer--;
        } else {
            sysTask_GateController();
            openTimer = INITIAL_OPEN_TIME;
        }

    }

    updateADC = 1;
}

void dspTask_OnTimer0(void) {
    if (updateADC == 1) {
        ADC_WATER_LVL = adc_GetConversion(); // Get ADC reading
        display_Msg_OnLCD(GATE_STATUS, ADC_WATER_LVL);
        updateADC = 0; // Reset flag for next reading
    }
    display_WaterLvl_OnSevSeg(ADC_WATER_LVL); // Display ADC result on 7-segment display


}

void sysTask_GateController() {

    if (GATE_STATUS == 'C' || GATE_STATUS == 'O') {
        GATE_STATUS = GATE_STATUS == 'C' ? 'O' : 'C';
    } else {
        // handle current stop and read input
    }


}


