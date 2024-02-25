#include <xc.h>
#include "config.h" 
#include <string.h>

#define LCD_DATA PORTD // Define LCD data port
#define LCD_RS PORTEbits.RE1 // Define LCD RS pin
#define LCD_E PORTEbits.RE0 // Define LCD E pin

// Function Declarations:
void sendToLCD(char data, char rs);

// Initialize LCD module
void initLCD() {
    __delay_ms(15); // 15ms LCD power-up delay
    sendToLCD(0b00000011, 0); // Function Set (DB4-DB7:8-bit interface)
    __delay_ms(5); // 5ms delay
    sendToLCD(0b00000010, 0); // Function Set (DB4-DB7:4-bit interface)
    sendToLCD(0b00101000, 0); // Function Set - 4-bit, 2 lines, 5x7
    sendToLCD(0b00001100, 0); // Display on, cursor off
    sendToLCD(0b00000110, 0); // Entry mode - inc addr, no shift
    sendToLCD(0b00000001, 0); // Clear display & home position
}

// Send command or write operation to LCD
void sendToLCD(char data, char rs) {
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

// Display message on LCD based on gate and water conditions
void lcd_DspStatus(unsigned char gate, unsigned char water) {
    
    sendToLCD(0b00000001, 0); // Clear LCD display 
    // Define line1 array to hold up to 15 characters
   char line1[16];          // Define array to hold line 1 characters
   char line2[16];          // Define array to hold line 2 character
   unsigned int i;          // Loop index variable

    // Assign initial value to line1 based on gate condition
    switch (gate) {
        case 1:
            strcpy(line2, "Gate: TB-Close");
            break;
        case 2:
            strcpy(line2, "Gate: Closing");
            break;
        case 3:
            strcpy(line2, "Gate: Close");
            break;
        case 4:
            strcpy(line2, "Gate: TB-Open");
            break;
        case 5:
            strcpy(line2, "Gate: Opening");
            break;
        case 6:
            strcpy(line2, "Gate: Open");
            break;
        case 7:
            strcpy(line2, "Gate: Stop");
            break;
        default:
            strcpy(line2, "Gate: ERROR");
            break;
    }
    
    // Assign message for line 1 based on water condition
    if (water == 1) {
        strcpy(line1, "Water: High");
    } else {
        strcpy(line1, "Water: Safe");
    }
    
    // Display line 1 message
    sendToLCD(0b00000010, 0); // Move to the start of the first line
    for (i = 0; line1[i] != 0; i++)
        sendToLCD(line1[i], 1);
        
    // Display line 2 message
    sendToLCD(0b11000000, 0); // Move to the start of the second line
    for (i = 0; line2[i] != 0; i++)
        sendToLCD(line2[i], 1);
}
