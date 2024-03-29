#include <xc.h>
#include "config.h"

#define LCD_DATA PORTD
#define LCD_RS PORTEbits.RE1 // RS pin
#define LCD_E PORTEbits.RE0 // E pin

/* __ FUNCTIONS DECLARATION __ */
// Defined in this file
void initLCD(void);
void LCD_sendCW(char x);
void LCD_sendData(char x);
void LCD_setPos(unsigned char row, unsigned char col);

// Defined in other file(s)


void initLCD(void) {

    __delay_ms(15); // 15ms LCD power-up delay
    LCD_sendCW(0b00000011); // Function Set (DB4-DB7:8-bit interface)
    __delay_ms(5); // 5ms delay
    LCD_sendCW(0b00000010); // Function Set (DB4-DB7:4-bit interface)
    LCD_sendCW(0b00101000); // Function Set - 4-bit, 2 lines, 5x7
    LCD_sendCW(0b00001100); // Display on, cursor off
    LCD_sendCW(0b00000110); // Entry mode - inc addr, no shift
    LCD_sendCW(0b00000001); // Clear display & home position
}

void LCD_sendCW(char x) {

    LCD_RS = 0;
    LCD_DATA = x;
    LCD_E = 1;
    __delay_ms(1);
    LCD_E = 0;
    __delay_ms(1);
    LCD_DATA = x << 4;
    LCD_E = 1;
    __delay_ms(1);
    LCD_E = 0;
    __delay_ms(1);
}

void LCD_sendData(char x) {
    LCD_RS = 1;
    LCD_DATA = x;
    LCD_E = 1;
    __delay_ms(1);
    LCD_E = 0;
    __delay_ms(1);
    LCD_DATA = x << 4;
    LCD_E = 1;
    __delay_ms(1);
    LCD_E = 0;
    __delay_ms(1);
}

void LCD_setPos(unsigned char row, unsigned char col) {
    unsigned char ramAddr; // Ctrl instruction to be sent

    if (row == 1) // If row is 1:
        ramAddr = col - 1; // Subtract 1 from the col
    else // If row is 2:
        ramAddr = 0x40 + col - 1; // Add 0x40 to ramAddr, and subtract 1 from the col
    LCD_sendCW(0x80 + ramAddr); // Add 0x80 to ramAddr and write ctrl word
}

void LCD_send(char data, char rs) {
    LCD_RS = rs; // Set RS low for command mode, RS high for data mode
    LCD_DATA = data; // Send command/data to LCD data port
    LCD_E = 1; // Set E high/low
    __delay_ms(1); // Delay to meet LCD timing requirements
    LCD_E = 0;
    __delay_ms(1);
    LCD_DATA = (unsigned char) (data << 4); // Shift data by 4 bits for 4-bit interface
    LCD_E = 1;
    __delay_ms(1);
    LCD_E = 0;
    __delay_ms(1);
}