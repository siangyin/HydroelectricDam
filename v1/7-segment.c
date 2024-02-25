#include <xc.h>
#include "config.h"


// FUNCTIONS DECLARATIONS:

// <-- FUNCTIONS IN THIS FILE -->:
void display_7Segment(char position, unsigned int digit);

// <-- FUNCTIONS DEFINED IN OTHER FILE -->:

const unsigned char segTable[] = {
    0b11000000, //0
    0b11111001, //1
    0b10100100, //2
    0b10110000, //3
    0b10011001, //4
    0b10010010, //5
    0b10000010, //6
    0b11111000, //7
    0b10000000, //8
    0b10010000, //9
    0b11111111, //blank
};


void display_7Segment(char position, unsigned int index) {
    switch(position) {
        case 1:
            PORTAbits.RA5 = 1;
            PORTAbits.RA4 = 1;
            
            PORTC = segTable[index];
            __delay_ms(5);
            
            break;
        case 2:
            PORTAbits.RA5 = 1;
            PORTAbits.RA4 = 0;
            
            PORTC = segTable[index];
            __delay_ms(5);
            
            break;
        case 3:
            PORTAbits.RA5 = 0;
            PORTAbits.RA4 = 1;
            
            PORTC = segTable[index];
            __delay_ms(5);
            
            break;
        case 4:
            PORTAbits.RA5 = 0;
            PORTAbits.RA4 = 0;
            
            PORTC = segTable[index];
            __delay_ms(5);
            
            break;
        default:
            // PORTC = segTable[10];
            // Handle invalid position
            break;
    }
}
