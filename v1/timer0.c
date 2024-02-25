#include <xc.h>
#include "config.h"

// GLOBAL VARIABLES:
unsigned int extint_WaterLevel = 0; // keep track of button presses
char extint_OnToggleLED = 3;

void initSysTimer0(void) {
    INTCONbits.GIE = 0; // Disable Global Interrupt
    T0CON0 = 0b10010000; // Set T0CON0
    T0CON1 = 0b01000100; // Set T0CON1
    TMR0H = 0x0B; // Set TMR0H
    TMR0L = 0xDC; // Set TMR0L
    PIR0bits.TMR0IF = 0; // Clear Timer0 interrupt flag
    PIE0bits.TMR0IE = 1; // Enable Timer0
    INTCONbits.GIE = 1; // Enable Global Interrupt
}

void extint_Timer0Task(void) { 
 
  if (extint_WaterLevel == 99) { // prevent count from exceeding
    extint_WaterLevel = 0;
  } else extint_WaterLevel++; // increment the count
  
 if(extint_OnToggleLED==0){
      extint_OnToggleLED=3;
  } else extint_OnToggleLED--;
  
 
      
  
}

unsigned int extint_GetWaterLevel(void) { // function for other files to get count
  return (extint_WaterLevel);
}

char extint_GetLEDPosition(void) { // function for other files to get count
  return (extint_OnToggleLED);
}