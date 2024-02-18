#include <xc.h>
#include "config.h" // Include configuration file for device settings
#include <string.h>

#define LCD_DATA PORTD // Define LCD data port
#define LCD_RS PORTEbits.RE1 // Define LCD RS pin
#define LCD_E PORTEbits.RE0 // Define LCD E pin

// Function Declarations:
void LCD_send(char data, char rs);

// Initialize LCD module

void initLCD() {
    __delay_ms(15); // 15ms LCD power-up delay
    LCD_send(0b00000011, 0); // Function Set (DB4-DB7:8-bit interface)
    __delay_ms(5); // 5ms delay
    LCD_send(0b00000010, 0); // Function Set (DB4-DB7:4-bit interface)
    LCD_send(0b00101000, 0); // Function Set - 4-bit, 2 lines, 5x7
    LCD_send(0b00001100, 0); // Display on, cursor off
    LCD_send(0b00000110, 0); // Entry mode - inc addr, no shift
    LCD_send(0b00000001, 0); // Clear display & home position
}

// Send command or write operation to LCD

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

void display_Msg_OnLCD(unsigned char gate, unsigned int waterLevel) {
    LCD_send(0b00000001, 0); // Clear LCD display 
    unsigned int i;
    // Define line1 array to hold up to 15 characters
    char line1[16]; 
    char line2[16];

    // Assign initial value to line1 based on gate parameter
    switch (gate) {
        case 'O':
            strcpy(line1, "Gate: OPEN");
            break;

        case 'C':
            strcpy(line1, "Gate: CLOSE");
            break;

        case 'S':
            strcpy(line1, "Gate: STOP");
            break;

        default:
            strcpy(line1, "Gate: ERROR");
            break;
    }

    if(waterLevel > 800){
        strcpy(line2, "Water: High");
    } else if(waterLevel<500){
        strcpy(line2, "Water: Low");
    } else{
        strcpy(line2, "Water: Safe");
    }

    LCD_send(0b00000010, 0); // Move to the start of the first line
    for (i = 0; line1[i] != 0; i++)
        LCD_send(line1[i], 1);

    LCD_send(0b11000000, 0); // Move to the start of the second line
    for (i = 0; line2[i] != 0; i++)
        LCD_send(line2[i], 1);

    //__delay_ms(1);
}