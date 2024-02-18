#include <xc.h>
#include "config.h"

const unsigned int MAX_COUNT_VALUE_16BIT_TIMER = 65536;

const unsigned int HALF_PERIOD1 = 478; // 478, 426, 379
const unsigned int FULL_PERIOD1 = 1046; // 1046, 1175, 1319

const unsigned int HALF_PERIOD2 = 426; // 478, 426, 379
const unsigned int FULL_PERIOD2 = 1175; // 1046, 1175, 1319

const unsigned int HALF_PERIOD3 = 379; // 478, 426, 379
const unsigned int FULL_PERIOD3 = 1319; // 1046, 1175, 1319

unsigned int tmr1_TotalReqdCount;
unsigned int tmr1_RunCount;

void initSysTimer1(void) {
  INTCONbits.GIE = 0;
  INTCONbits.PEIE = 1;
  T1CON = 0b00000010; // Disable Timer1 first. Pre-scaler is 1
  T1CLK = 0b00000001;
  PIE4bits.TMR1IE = 1; // Let Timer1 interrupt be enabled.
  PIR4bits.TMR1IF = 0;
  INTCONbits.GIE = 1;
}
//
//void tmr1_StartTone(unsigned int halfPeriod, unsigned int fullPeriod) {
//  unsigned int preload_value;
//
//  preload_value = (MAX_COUNT_VALUE_16BIT_TIMER - halfPeriod);
//
//  // Write to the Timer1 register
//  TMR1H = (unsigned char)(preload_value >> 8);
//  TMR1L = (unsigned char) preload_value;
//
//  tmr1_TotalReqdCount = fullPeriod; 
//  tmr1_RunCount = 0;
//  T1CONbits.TMR1ON = 1; // Start timer
//}