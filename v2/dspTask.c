#include <xc.h>
#include "config.h"

#define LED1 PORTAbits.RA1
#define LED2 PORTAbits.RA2
#define LED3 PORTAbits.RA3

#define SW0 PORTBbits.RB0
#define SW1 PORTBbits.RB1

#define INITIAL_CLOSE_TIME 10 //  value for INITIAL_CLOSE_TIME
#define INITIAL_OPEN_TIME 10 //  value for INITIAL_OPEN_TIME
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
unsigned char includes(const int arr[], int size, unsigned int value);

// Global Variables:
unsigned char updateADC = 0; // Flag to indicate ADC update
unsigned char hour = 0, min = 0, sec = 0; // Variables for time tracking
unsigned int ADC_WATER_LVL; // Result of ADC conversion
unsigned char GATE_STATUS = 'C'; // O as open, C as close, S stop

unsigned char closeTimer = 0;
unsigned char openTimer = 0;
unsigned int ALARM_BUZZER_COUNT = 0;

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

    if (GATE_STATUS == 'C' && closeTimer > 0 && ALARM_BUZZER_COUNT == 0) {
        closeTimer--;
    }

    if (GATE_STATUS == 'O' && openTimer > 0 && ALARM_BUZZER_COUNT == 0) {
        openTimer--;
    }


    if (ALARM_BUZZER_COUNT > 0) {
        onLEDs(1, 1, 1);
        alarm_trigger(ALARM_BUZZER_COUNT);
    }
    updateADC = 1;
}

void dspTask_OnTimer0(void) {
    if (updateADC == 1) {
        ADC_WATER_LVL = adc_GetConversion(); // Get ADC reading
        //ADC_WATER_LVL = (ADC_WATER_LEVEL/1023.0) * 100;
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
            ALARM_BUZZER_COUNT = 25;
            GATE_STATUS = 'O';
            break;
        case 'C':
            closeTimer = INITIAL_CLOSE_TIME;
            ALARM_BUZZER_COUNT = 25;
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
    // sound 1-E,2-D,3-C, eg(1232111222111123211122123)

    const int arrE[] = {25, 21, 20, 19, 15, 14, 13, 12, 8, 7, 6, 3};
    const int arrD[] = {24, 22, 18, 17, 16, 11, 9, 5, 4, 2};
    const int arrC[] = {23, 10, 1};
    unsigned int i = timer;
    if (includes(arrE, sizeof (arrE) / sizeof (arrE[0]), i)) {
        tmr1_StartTone(HALF_PERIOD3, FULL_PERIOD3);
    } else if (includes(arrD, sizeof (arrD) / sizeof (arrD[0]), i)) {
        tmr1_StartTone(HALF_PERIOD2, FULL_PERIOD2);
    } else if (includes(arrC, sizeof (arrC) / sizeof (arrC[0]), i)) {
        tmr1_StartTone(HALF_PERIOD1, FULL_PERIOD1);
    }


    ALARM_BUZZER_COUNT--;
}

void onLEDs(unsigned char led1, unsigned char led2, unsigned char led3) {
    LED1 = led1 == 1 ? 1 : 0;
    LED2 = led2 == 1 ? 1 : 0;
    LED3 = led3 == 1 ? 1 : 0;
}

unsigned char usrTask_CheckInput(void) {
    unsigned char detect = 0;

    if (SW0 == 0 || SW1 == 0) {
        __delay_ms(20);
        if (SW0 == 0 || SW1 == 0) {
            detect = SW0 == 0 ? 1 : 2;
            if (GATE_STATUS == 'S') {
                GATE_STATUS = detect == 1 ? 'O' : 'C';
            } else {
                GATE_STATUS = 'S';
            }

            while (SW0 == 0 || SW1 == 0);
        }
    }


    return detect;
}
