#include <xc.h>
#include "config.h"

#define LCD_DATA PORTD
#define LCD_RS PORTEbits.RE1 // RS pin
#define LCD_E PORTEbits.RE0 // E pin

/* __ FUNCTIONS DECLARATION __ */
// Defined in this file
void LCD_send(char data, char rs);

// Defined in other file(s)

void initLCD(void) {
  __delay_ms(15); // 15ms LCD power-up delay
  LCD_send(0b00000011, 0); // Reset
  __delay_ms(5); // 5ms delay
  LCD_send(0b00000010, 0); // 4-bit mode
  LCD_send(0b00101000, 0); // Function Set - 4-bit, 2 lines, 5X7
  LCD_send(0b00001100, 0); // Display on, cursor off
  LCD_send(0b00000110, 0); // Entry mode - inc addr, no shift
  LCD_send(0b00000001, 0); // Clear display
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