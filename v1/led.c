#include <xc.h>
#include "config.h"

#define LED0 PORTAbits.RA0
#define LED1 PORTAbits.RA1
#define LED2 PORTAbits.RA2
#define LED3 PORTAbits.RA3

// FUNCTIONS DECLARATIONS:

// <-- FUNCTIONS IN THIS FILE -->:
void toggleLEDs(void);

// <-- FUNCTIONS DEFINED IN OTHER FILE -->:
char extint_GetLEDPosition(void);

void toggleLEDs(void) {
    char act = extint_GetLEDPosition();

    switch (act) {
        case 0:
            LED0 = 1;
            LED1 = 0;
            LED2 = 0;
            LED3 = 0;
            break;
        case 1:
            LED0 = 0;
            LED1 = 1;
            LED2 = 0;
            LED3 = 0;
            break;
        case 2:
            LED0 = 0;
            LED1 = 0;
            LED2 = 1;
            LED3 = 0;
            break;
        case 3:
            LED0 = 0;
            LED1 = 0;
            LED2 = 0;
            LED3 = 1;
            break;
        case 4:
            LED0 = 1;
            LED1 = 1;
            LED2 = 1;
            LED3 = 1;
            break;
        default:
            LED0 = 0;
            LED1 = 0;
            LED2 = 0;
            LED3 = 0;
    }
}