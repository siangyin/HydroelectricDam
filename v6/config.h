#pragma config FEXTOSC = XT
#pragma config WDTE = OFF
#pragma config LVP = OFF

#define _XTAL_FREQ 4000000

// Timer0 preload values for 0.5 second
#define TIMER0_TMR0H 0xC2 // 0x0B 1S// 0xC2  0.5S
#define TIMER0_TMR0L 0xC2 // 0xDC 1S // 0xC2 0.5S

// Global variables
extern const unsigned int HALF_PERIOD1;
extern const unsigned int FULL_PERIOD1;
extern const unsigned int HALF_PERIOD2;
extern const unsigned int FULL_PERIOD2;
extern const unsigned int HALF_PERIOD3;
extern const unsigned int FULL_PERIOD3;

extern unsigned int ALARM_BUZZER_COUNT;

