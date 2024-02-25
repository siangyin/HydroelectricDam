#include <xc.h>
#include "config.h"

// Function Declarations:
void gateController(unsigned char status);
void onLEDs(unsigned char led1, unsigned char led2, unsigned char led3);
void playAlarm(unsigned int timer);

// - Defined in other file(s):
unsigned int adc_GetConversion(void);
void seg_DspAll(unsigned int result);
void display_Msg_OnLCD(unsigned char gate, unsigned char water);

//void recordNewWater();
void tmr1_StartTone(unsigned int halfPeriod, unsigned int fullPeriod);
//unsigned char includes(const int arr[], int size, unsigned int value);

// Global Variables:
const unsigned char GATE_1_TO_BE_CLOSE = 1;
const unsigned char GATE_2_CLOSING = 2;
const unsigned char GATE_3_CLOSE = 3;
const unsigned char GATE_4_TO_BE_OPEN = 4;
const unsigned char GATE_5_OPENING = 5;
const unsigned char GATE_6_OPEN = 6;
const unsigned char GATE_7_STOP = 7;

unsigned int ADC_WATER_LVL = 0;
unsigned char WATER_STATUS = 0;
unsigned char GATE_STATUS = 3;
unsigned char GATE_MODE = 1;
unsigned int ALARM_BUZZER_COUNT = 0;

unsigned char updateADC = 0; // Flag to indicate ADC update
unsigned char updateLCD = 0;
unsigned char sec = 0;
unsigned char openingTimer = 0;
unsigned char closingTimer = 0;

extern unsigned char newWaterStatus;
extern unsigned char newGateStatus;
unsigned char waterStatus_HasChange;
unsigned char gateStatus_HasChange;

//void alarm_trigger(unsigned int timer) {
//    // sound 1-E,2-D,3-C, eg(1232111222111123211122123)
//
//    const int arrE[] = {25, 21, 20, 19, 15, 14, 13, 12, 8, 7, 6, 3};
//    const int arrD[] = {24, 22, 18, 17, 16, 11, 9, 5, 4, 2};
//    const int arrC[] = {23, 10, 1};
//    unsigned int i = timer;
//    if (includes(arrE, sizeof (arrE) / sizeof (arrE[0]), i)) {
//        tmr1_StartTone(HALF_PERIOD3, FULL_PERIOD3);
//    } else if (includes(arrD, sizeof (arrD) / sizeof (arrD[0]), i)) {
//        tmr1_StartTone(HALF_PERIOD2, FULL_PERIOD2);
//    } else if (includes(arrC, sizeof (arrC) / sizeof (arrC[0]), i)) {
//        tmr1_StartTone(HALF_PERIOD1, FULL_PERIOD1);
//    }
//
//    ALARM_BUZZER_COUNT--;
//}


// This function is called by the ISR whenever there is a 1-second interrupt:

void dspTask_OnTimer0Interrupt(void) {
    sec++; // Increment seconds
    if (sec > 59) {
        sec = 0;
    }

    if (GATE_STATUS == GATE_5_OPENING && ALARM_BUZZER_COUNT == 0 && openingTimer > 0) {
        openingTimer--;
    }

    onLEDs(0, 0, 0);
    if (ALARM_BUZZER_COUNT > 0) {
        //onLEDs(1, 1, 1);
        playAlarm(ALARM_BUZZER_COUNT);
    } else {
        updateADC = 1;
    }





}

void dspTask_showStatus(void) {

    if (updateADC == 1) {
        ADC_WATER_LVL = adc_GetConversion(); // Get ADC reading
        newWaterStatus = ADC_WATER_LVL >= MIN_ALLOWABLE_LEVEL ? 1 : 0;
        
        waterStatus_HasChange = WATER_STATUS != newWaterStatus ? 1 : 0;
        gateStatus_HasChange = 0;

        if (GATE_MODE == 1) {
            if (newWaterStatus == 1) {
                if (GATE_STATUS >= GATE_1_TO_BE_CLOSE && GATE_STATUS <= GATE_3_CLOSE) {
                    newGateStatus = 4; // GATE_4_TO_BE_OPEN
                    gateStatus_HasChange = 1;
                } else if (GATE_STATUS == GATE_4_TO_BE_OPEN && ALARM_BUZZER_COUNT == 0) {
                    openingTimer = 10;
                    newGateStatus = 5;
                    gateStatus_HasChange = 1;
                } else if (GATE_STATUS == GATE_5_OPENING && openingTimer == 0) {
                    newGateStatus = 6;
                    gateStatus_HasChange = 1;
                }
            } else if (ADC_WATER_LVL>=500) {
                if (GATE_STATUS >= GATE_4_TO_BE_OPEN && GATE_STATUS <= GATE_6_OPEN) {
                    newGateStatus = 1; // GATE_1_TO_BE_CLOSE
                    gateStatus_HasChange = 1;
                } else if (GATE_STATUS == GATE_1_TO_BE_CLOSE || ALARM_BUZZER_COUNT == 0) {
                    closingTimer = 10;
                    newGateStatus = 2; //GATE_2_CLOSING
                } else if (GATE_STATUS == GATE_2_CLOSING && closingTimer == 0) {
                    newGateStatus = 3;
                    gateStatus_HasChange = 1;
                }
            }
        }

        if (waterStatus_HasChange == 1 || gateStatus_HasChange == 1 || sec == 1) {
            WATER_STATUS = waterStatus_HasChange == 1 ? newWaterStatus : WATER_STATUS;
            GATE_STATUS = gateStatus_HasChange == 1 ? newGateStatus : GATE_STATUS;
            updateLCD = 1;
            ALARM_BUZZER_COUNT = newGateStatus == GATE_4_TO_BE_OPEN || newGateStatus == GATE_1_TO_BE_CLOSE ? 25 : 0;
        }

        updateADC = 0; // Reset flag for next reading
    }

    if (updateLCD == 1) {
        display_Msg_OnLCD(GATE_STATUS, WATER_STATUS);
        updateLCD = 0;
    }

    seg_DspAll(ADC_WATER_LVL); // Display ADC result on 7-segment display
}

void gateController(unsigned char status) {
    ALARM_BUZZER_COUNT = 25;
    GATE_STATUS = status - 1;

}

void onLEDs(unsigned char led1, unsigned char led2, unsigned char led3) {
    LED1 = led1 == 1 ? 1 : 0;
    LED2 = led2 == 1 ? 1 : 0;
    LED3 = led3 == 1 ? 1 : 0;
}

void playAlarm(unsigned int timer) {
    // sound 1-E,2-D,3-C, eg(1232111222111123211122123)

    //    const int arrE[] = {25, 21, 20, 19, 15, 14, 13, 12, 8, 7, 6, 3};
    //    const int arrD[] = {24, 22, 18, 17, 16, 11, 9, 5, 4, 2};
    //    const int arrC[] = {23, 10, 1};
    //    unsigned int i = timer;
    //    if (includes(arrE, sizeof (arrE) / sizeof (arrE[0]), i)) {
    //        tmr1_makeTone(HALF_PERIOD3, FULL_PERIOD3);
    //    } else if (includes(arrD, sizeof (arrD) / sizeof (arrD[0]), i)) {
    //        tmr1_makeTone(HALF_PERIOD2, FULL_PERIOD2);
    //    } else if (includes(arrC, sizeof (arrC) / sizeof (arrC[0]), i)) {
    //        tmr1_makeTone(HALF_PERIOD1, FULL_PERIOD1);
    //    }

    switch (timer) {
        case 3:
        case 6:
        case 7:
        case 8:
        case 12:
        case 13:
        case 14:
        case 15:
        case 19:
        case 20:
        case 21:
        case 25:
            tmr1_StartTone(HALF_PERIOD3, FULL_PERIOD3);
            break;
        case 2:
        case 4:
        case 5:
        case 9:
        case 11:
        case 16:
        case 17:
        case 18:
        case 22:
        case 24:
            tmr1_StartTone(HALF_PERIOD2, FULL_PERIOD2);
            break;
        case 1:
        case 10:
        case 23:
            tmr1_StartTone(HALF_PERIOD1, FULL_PERIOD1);
            break;
    }



    ALARM_BUZZER_COUNT--;
}