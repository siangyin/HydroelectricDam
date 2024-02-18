#include <xc.h>
#include "config.h"

void initSysTimer1(void) {
  INTCONbits.GIE = 0;
  INTCONbits.PEIE = 1;
  T1CON = 0b00000010; // Disable Timer1 first. Pre-scaler is 1
  T1CLK = 0b00000001;
  PIE4bits.TMR1IE = 1; // Let Timer1 interrupt be enabled.
  PIR4bits.TMR1IF = 0;
  INTCONbits.GIE = 1;
}
