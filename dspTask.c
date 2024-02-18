#include <xc.h>
#include "config.h"

#define INITIAL_CLOSE_TIME 10 // Example value for INITIAL_CLOSE_TIME
#define INITIAL_OPEN_TIME 10 // Example value for INITIAL_OPEN_TIME
#define MIN_ALLOWABLE_LEVEL 800
#define SAFE_LEVEL 500

// Function Declarations:
void sysTask_GateController(unsigned char status);
void sysTask_AutoGateOnWater(unsigned int waterLevel);

// - Defined in other file(s):
unsigned int adc_GetConversion(void);
void display_WaterLvl_OnSevSeg(unsigned int waterLevel);
void display_Msg_OnLCD(unsigned char gate, unsigned int waterLevel);

// Global Variables:

unsigned char updateADC = 0; // Flag to indicate ADC update
unsigned char hour = 0, min = 0, sec = 0; // Variables for time tracking
unsigned int ADC_WATER_LVL; // Result of ADC conversion
unsigned char GATE_STATUS = 'C'; // O as open, C as close, S stop

unsigned char closeTimer = 0;
unsigned char openTimer = 0;

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

    if (GATE_STATUS == 'C' && closeTimer > 0) {
        closeTimer--;
    }

    if (GATE_STATUS == 'O' && openTimer > 0) {
        openTimer--;
    }

    updateADC = 1;
}

void dspTask_OnTimer0(void) {
    if (updateADC == 1) {
        ADC_WATER_LVL = adc_GetConversion(); // Get ADC reading
        sysTask_AutoGateOnWater(ADC_WATER_LVL);
        display_Msg_OnLCD(GATE_STATUS, ADC_WATER_LVL);
        updateADC = 0; // Reset flag for next reading
    }
    display_WaterLvl_OnSevSeg(ADC_WATER_LVL); // Display ADC result on 7-segment display


}

void sysTask_GateController(unsigned char status) {

    switch (status) {
        case 'O':
            openTimer = INITIAL_OPEN_TIME;
            GATE_STATUS = 'O';

            break;
        case 'C':
            closeTimer = INITIAL_CLOSE_TIME;
            GATE_STATUS = 'C';

            break;
        case 'S':

            GATE_STATUS = 'S';
            break;

    }
}

void sysTask_AutoGateOnWater(unsigned int waterLevel) {
    if (waterLevel > MIN_ALLOWABLE_LEVEL && GATE_STATUS == 'C') {
        sysTask_GateController('O');
    } else if (waterLevel >= SAFE_LEVEL && waterLevel <= MIN_ALLOWABLE_LEVEL && GATE_STATUS == 'O') {
        sysTask_GateController('C');
    }

}


