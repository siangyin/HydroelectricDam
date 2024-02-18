#include <xc.h>
#include "config.h"

#define LED1 PORTAbits.RA1
#define LED2 PORTAbits.RA2
#define LED3 PORTAbits.RA3

#define INITIAL_CLOSE_TIME 10 // Example value for INITIAL_CLOSE_TIME
#define INITIAL_OPEN_TIME 10 // Example value for INITIAL_OPEN_TIME
#define MIN_ALLOWABLE_LEVEL 800
#define SAFE_LEVEL 500

// Function Declarations:
void sysTask_GateController(unsigned char status);
void sysTask_AutoGateOnWater(unsigned int waterLevel);
void alarm_trigger(unsigned int timer);
void onLEDs(unsigned char led1, unsigned char led2, unsigned char led3);

// - Defined in other file(s):
unsigned int adc_GetConversion(void);
void display_WaterLvl_OnSevSeg(unsigned int waterLevel);
void display_Msg_OnLCD(unsigned char gate, unsigned int waterLevel);
void tmr1_StartTone(unsigned int halfPeriod, unsigned int fullPeriod);

// Global Variables:

unsigned char updateADC = 0; // Flag to indicate ADC update
unsigned char hour = 0, min = 0, sec = 0; // Variables for time tracking
unsigned int ADC_WATER_LVL; // Result of ADC conversion
unsigned char GATE_STATUS = 'C'; // O as open, C as close, S stop

unsigned char closeTimer = 0;
unsigned char openTimer = 0;
unsigned int alarmTimer = 0;

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

    if (GATE_STATUS == 'C' && closeTimer > 0 && alarmTimer == 0) {
        closeTimer--;
    }

    if (GATE_STATUS == 'O' && openTimer > 0 && alarmTimer == 0) {
        openTimer--;
    }


    if (alarmTimer > 0) {
        onLEDs(1, 1, 1);
        alarm_trigger(alarmTimer);
    }
    updateADC = 1;
}

void dspTask_OnTimer0(void) {
    if (updateADC == 1) {
        ADC_WATER_LVL = adc_GetConversion(); // Get ADC reading
        sysTask_AutoGateOnWater(ADC_WATER_LVL);
        display_Msg_OnLCD(GATE_STATUS, ADC_WATER_LVL);
        updateADC = 0; // Reset flag for next reading
        onLEDs(0, 0, 0);
    }
    display_WaterLvl_OnSevSeg(ADC_WATER_LVL); // Display ADC result on 7-segment display




}

void sysTask_GateController(unsigned char status) {

    switch (status) {
        case 'O':
            openTimer = INITIAL_OPEN_TIME;
            alarmTimer = 3;

            GATE_STATUS = 'O';

            break;
        case 'C':
            closeTimer = INITIAL_CLOSE_TIME;
            alarmTimer = 3;
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

void alarm_trigger(unsigned int timer) {
    switch (timer) {
        case 3:
            tmr1_StartTone(HALF_PERIOD1, FULL_PERIOD1);

            break;
        case 2:
            tmr1_StartTone(HALF_PERIOD2, FULL_PERIOD2);

            break;
        case 1:

            tmr1_StartTone(HALF_PERIOD3, FULL_PERIOD3);

            break;
    }

    alarmTimer--;
}

void onLEDs(unsigned char led1, unsigned char led2, unsigned char led3) {
    LED1 = led1 == 1 ? 1 : 0;
    LED2 = led2 == 1 ? 1 : 0;
    LED3 = led3 == 1 ? 1 : 0;
}