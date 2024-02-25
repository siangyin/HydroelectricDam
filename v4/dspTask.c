#include <xc.h>
#include "config.h"
#include <stdio.h>
#include <string.h>

/* __ FUNCTIONS DECLARATION __ */ //
// Defined in this file
void alarm_trigger(unsigned int timer);

// Defined in other file(s)
void LCD_sendData(char x);
void LCD_setPos(unsigned char row, unsigned char col);
unsigned int adc_GetConversion(void);
void seg_DspAll(unsigned int result);
void LCD_send(char data, char rs);
void tmr1_StartTone(unsigned int halfPeriod, unsigned int fullPeriod);

// Global Variable
unsigned int ADC_WATER_LEVEL; // Result of ADC conversion
char WATER_STATE[] = "Safe";
unsigned char GATE_STATUS_VALUE = 2;
char GATE_STATUS_TEXT[] = "Close";
unsigned int ALARM_BUZZER_COUNT = 0;

unsigned char updateLCD = 0; // flag
unsigned char hour = 0, min = 0, sec = 0;
unsigned char updateADC = 0; // Flag to indicate ADC update

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
// This function is called by ISR whenever there is 0.5-second interrupt:

void dspTask_OnTimer0Interrupt() {
    updateTime();
    ADC_WATER_LEVEL = adc_GetConversion(); // Get ADC reading

    updateLCD = 1;
    updateADC = 1; // Set the flag to 1

    if (ALARM_BUZZER_COUNT > 0) {
        //onLEDs(1, 1, 1);
        alarm_trigger(ALARM_BUZZER_COUNT);
    }
}

void dspTask_MsgOnLCD(void) {

    if (updateLCD == 1) {
        unsigned int i;
        char line1[16];
        sprintf(line1, "%02d:%02d:%02d", hour, min, sec);
        LCD_send(0b00000010, 0); // Move to the start of the first line
        for (i = 0; line1[i] != 0; i++)
            LCD_send(line1[i], 1);

        char line2[16];
        sprintf(line2, "W:%s G:%s", WATER_STATE, GATE_STATUS_TEXT);
        LCD_send(0b11000000, 0); // Move to the start of the second line
        for (i = 0; line2[i] != 0; i++)
            LCD_send(line2[i], 1);

        updateLCD = 0; // reset flag to zero so it refresh on LCD

    }
}

void updateDisplay(void) {
    seg_DspAll(ADC_WATER_LEVEL); // Display ADC result on 7-segment display
    dspTask_MsgOnLCD();
}

void alarm_trigger(unsigned int timer) {
    switch (timer) {
        case 9:
            tmr1_StartTone(HALF_PERIOD1, FULL_PERIOD1);
            break;
        case 8:
        case 6:
        case 5:
        case 4:
            tmr1_StartTone(HALF_PERIOD2, FULL_PERIOD2);
            break;
        case 7:
        case 3:
        case 2:
        case 1:
            tmr1_StartTone(HALF_PERIOD3, FULL_PERIOD3);
            break;
    }

    if (ALARM_BUZZER_COUNT > 0)
        ALARM_BUZZER_COUNT--;

}
void addAlarm(unsigned int timer){
    ALARM_BUZZER_COUNT=timer;
}