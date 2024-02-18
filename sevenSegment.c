#include <xc.h>
#include "config.h"


// 7-segment display table for digits 0-9 and blank
const unsigned char segTable[] = {
    0b11000000, // 0
    0b11111001, // 1
    0b10100100, // 2
    0b10110000, // 3
    0b10011001, // 4
    0b10010010, // 5
    0b10000010, // 6
    0b11111000, // 7
    0b10000000, // 8
    0b10010000, // 9
    0b11111111, // blank
};

// Function to display the ADC water level on the 7-segment display & lcd

void display_WaterLvl_OnSevSeg(unsigned int waterLevel) {
    int dig0, dig1, dig2, dig3;

    // Extract individual digits from the ADC result
    dig0 = waterLevel % 10;
    dig1 = (waterLevel / 10) % 10;
    dig2 = (waterLevel / 100) % 10;
    dig3 = (waterLevel / 1000) % 10;

    // Display each digit on the 7-segment display sequentially
    PORTAbits.RA5 = 0;
    PORTAbits.RA4 = 0;
    PORTC = segTable[dig0];
    __delay_ms(1);
    PORTC = segTable[10];

    PORTAbits.RA5 = 0;
    PORTAbits.RA4 = 1;
    PORTC = segTable[dig1];
    __delay_ms(1);
    PORTC = segTable[10];

    PORTAbits.RA5 = 1;
    PORTAbits.RA4 = 0;
    PORTC = segTable[dig2];
    __delay_ms(1);
    PORTC = segTable[10];

    PORTAbits.RA5 = 1;
    PORTAbits.RA4 = 1;
    PORTC = segTable[dig3];
    __delay_ms(1);
    PORTC = segTable[10];


}