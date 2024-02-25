#include <xc.h>
#include "config.h"

void tmr1_MakeTone(unsigned int halfPeriod, unsigned int fullPeriod);

// Global variables
unsigned char usrActivatedStop = 0;
unsigned char prevGateStatus = 0;

// External variables
extern const unsigned char GATE_1_TO_BE_CLOSE;
extern const unsigned char GATE_2_CLOSING;
extern const unsigned char GATE_3_CLOSE;
extern const unsigned char GATE_4_TO_BE_OPEN;
extern const unsigned char GATE_5_OPENING;
extern const unsigned char GATE_6_OPEN;
extern const unsigned char GATE_7_STOP;
extern unsigned char GATE_STATUS;

extern unsigned char updateLCD;
extern unsigned char usrActivatedOpen;
extern unsigned char usrActivatedClose;
extern unsigned char openingTimer;
extern unsigned char closingTimer;


// Function to activate gate stop based on gate status
void usrTask_ActivateGateStop(void) {
    // If gate status indicates stop condition
    if (GATE_STATUS == GATE_7_STOP) {
        // Start tone generation
        tmr1_MakeTone(HALF_PERIOD1, FULL_PERIOD1);

        // Set appropriate parameters based on previous gate status
        switch (prevGateStatus) {
            case 1:
            case 4:
                ALARM_BUZZER_COUNT = 25;
                break;
            case 2:
                closingTimer = 10;
                break;
            case 5:
                openingTimer = 10;
                break;
        }

        // Restore prev gate status and request LCD update
        GATE_STATUS = prevGateStatus;
        updateLCD = 1;

    }  else if (GATE_STATUS == GATE_1_TO_BE_CLOSE ||
             GATE_STATUS == GATE_2_CLOSING ||
             GATE_STATUS == GATE_4_TO_BE_OPEN ||
             GATE_STATUS == GATE_5_OPENING) {
        // If gate status indicates gate movement
        // Start tone generation
        tmr1_MakeTone(HALF_PERIOD1, FULL_PERIOD1);

        // Save current gate status as previous, set gate status to stop, reset alarm count, and request LCD update
        prevGateStatus = GATE_STATUS;
        GATE_STATUS = 7;
        ALARM_BUZZER_COUNT = 0;
        updateLCD = 1;

    }

}