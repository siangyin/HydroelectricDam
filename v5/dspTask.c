#include <xc.h>
#include "config.h"
#include <stdio.h>
#include <string.h>

/* __ FUNCTIONS DECLARATION __ */
// Defined in this file
void dspTask_MsgOnLCD(void);
void gateController(unsigned char status);

// Defined in other file(s)
unsigned int adc_GetConversion(void);
void seg_DspAll(unsigned int result);
void LCD_send(char data, char rs);
void alarm_trigger(unsigned int timer);
void onLEDs(unsigned char led1, unsigned char led2, unsigned char led3);
void tmr1_makeTone(unsigned int halfPeriod, unsigned int fullPeriod);
unsigned char includes(const int arr[], int size, unsigned int value);
// Global Variables:
unsigned char updateADC = 0; // Flag to indicate ADC update
unsigned char updateLCD = 0; // Flag to indicate ADC update

unsigned char hour = 0, min = 0, sec = 0; // Variables for time tracking
unsigned int ADC_WATER_LEVEL = 0; // Result of ADC conversion

unsigned char WATER_STATUS_CODE = 's';
unsigned char newWaterStatus;
unsigned char GATE_STATUS_CODE = 2;
unsigned char newGateStatus;

unsigned int ALARM_BUZZER_COUNT = 0;

void updateTime(void) {
    sec++;
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


}

unsigned char includes(const int arr[], int size, unsigned int value) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == value) {
            return 1;
        }
    }
    return 0;
}


// This function is called by the ISR whenever there is a 1-second interrupt:

void dspTask_OnTimer0Interrupt(void) {
    updateTime();
    updateADC = 1; // Set the flag to 1




    if (ALARM_BUZZER_COUNT > 0) {
        onLEDs(1, 1, 1);
        alarm_trigger(ALARM_BUZZER_COUNT);
    }
}

void dspTask_showStatus(void) {
    unsigned char isWaterStateChanging = 0;
    unsigned char  isGateStateChanging =0;
    if (updateADC == 1) {
        ADC_WATER_LEVEL = adc_GetConversion(); // Get ADC reading
        newWaterStatus = (ADC_WATER_LEVEL > MIN_ALLOWABLE_LEVEL) ? 'm' : 's'; // Corrected initialization

        isWaterStateChanging = newWaterStatus == WATER_STATUS_CODE ? 0 : 1;


        if (isWaterStateChanging == 1) {
            updateLCD = 1;
            newGateStatus = newWaterStatus == 'm' ? 3 : 1;
            isGateStateChanging = newGateStatus == GATE_STATUS_CODE ? 0 : 1;
            WATER_STATUS_CODE = newWaterStatus;

            if (isGateStateChanging==1) {
                gateController(newGateStatus);
            }
        }


        updateADC = 0; // Reset flag for next reading

    }

    seg_DspAll(ADC_WATER_LEVEL); // Display ADC result on 7-segment display
    dspTask_MsgOnLCD();
}

void dspTask_MsgOnLCD(void) {

    char gateStatus[] = "Close";

    //char* strcpy(char* destination, const char* source);
    switch (GATE_STATUS_CODE) {
        case 1:
            strcpy(gateStatus, "Closing");
            break;
        case 2:
            strcpy(gateStatus, "Close");
            break;
        case 3:
            strcpy(gateStatus, "Opening");
            break;
        case 4:
            strcpy(gateStatus, "Open");
            break;
        case 5:
            strcpy(gateStatus, "Stop");
            break;

    }

    char waterStatus[] = "Safe";

    //char* strcpy(char* destination, const char* source);
    switch (WATER_STATUS_CODE) {
        case 's':
            strcpy(waterStatus, "Safe");
            break;
        case 'm':
            strcpy(waterStatus, "MIA");
            break;

    }




    if (updateLCD == 1) {
        unsigned int i;
        char line1[16];
        sprintf(line1, "%02d:%02d:%02d", hour, min, sec);
        LCD_send(0b00000010, 0); // Move to the start of the first line
        for (i = 0; line1[i] != 0; i++)
            LCD_send(line1[i], 1);

        char line2[16];
        sprintf(line2, "W:%s G:%s", waterStatus, gateStatus);
        LCD_send(0b11000000, 0); // Move to the start of the second line
        for (i = 0; line2[i] != 0; i++)
            LCD_send(line2[i], 1);

        updateLCD = 0; // reset flag to zero so it refresh on LCD

    }
}

void alarm_trigger(unsigned int timer) {
    // sound 1-E,2-D,3-C, eg(1232111222111123211122123)

    const int arrE[] = {25, 21, 20, 19, 15, 14, 13, 12, 8, 7, 6, 3};
    const int arrD[] = {24, 22, 18, 17, 16, 11, 9, 5, 4, 2};
    const int arrC[] = {23, 10, 1};
    unsigned int i = timer;
    if (includes(arrE, sizeof (arrE) / sizeof (arrE[0]), i)) {
        tmr1_makeTone(HALF_PERIOD3, FULL_PERIOD3);
    } else if (includes(arrD, sizeof (arrD) / sizeof (arrD[0]), i)) {
        tmr1_makeTone(HALF_PERIOD2, FULL_PERIOD2);
    } else if (includes(arrC, sizeof (arrC) / sizeof (arrC[0]), i)) {
        tmr1_makeTone(HALF_PERIOD1, FULL_PERIOD1);
    }


    ALARM_BUZZER_COUNT--;
}

void onLEDs(unsigned char led1, unsigned char led2, unsigned char led3) {
    LED1 = led1 == 1 ? 1 : 0;
    LED2 = led2 == 1 ? 1 : 0;
    LED3 = led3 == 1 ? 1 : 0;
}

void gateController(unsigned char status) {
    ALARM_BUZZER_COUNT = 25;
    GATE_STATUS_CODE = status;

    //    switch (status) {
    //        case 'O':
    //            //openTimer = INITIAL_OPEN_TIME;
    //            ALARM_BUZZER_COUNT = 25;
    //            GATE_STATUS_CODE = 'O';
    //            break;
    //        case 'C':
    //            //closeTimer = INITIAL_CLOSE_TIME;
    //            ALARM_BUZZER_COUNT = 25;
    //            GATE_STATUS_CODE = 'C';
    //            break;
    //        case 'S':
    //            GATE_STATUS_CODE = 'S';
    //            break;
    //    }
}