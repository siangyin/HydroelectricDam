#include <xc.h>
#include "config.h"

void tmr1_StartTone(unsigned int halfPeriod, unsigned int fullPeriod);

unsigned char usrActivatedStop = 0;
unsigned char prevGateStatus = 0;
extern unsigned char updateLCD;
extern unsigned char usrActivatedOpen;
extern unsigned char usrActivatedClose;
extern unsigned char openingTimer;
extern unsigned char closingTimer;

void usrTask_ActivateGateStop(void) {
    if (GATE_STATUS == GATE_7_STOP) {

tmr1_StartTone(HALF_PERIOD1, FULL_PERIOD1);

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

        GATE_STATUS = prevGateStatus;
        updateLCD = 1;

    } else if (GATE_STATUS == GATE_1_TO_BE_CLOSE ||
            GATE_STATUS == GATE_2_CLOSING ||
            GATE_STATUS == GATE_4_TO_BE_OPEN ||
            GATE_STATUS == GATE_5_OPENING) {

tmr1_StartTone(HALF_PERIOD1, FULL_PERIOD1);
        prevGateStatus = GATE_STATUS;

        GATE_STATUS = 7;
        ALARM_BUZZER_COUNT = 0;
        updateLCD = 1;

    }

}