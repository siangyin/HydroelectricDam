#pragma config FEXTOSC = XT
#pragma config WDTE = OFF
#pragma config LVP = OFF

#define _XTAL_FREQ 4000000

// Timer0 preload values for 0.5 second
#define TIMER0_TMR0H 0xC2 // 0x0B 1S// 0xC2  0.5S
#define TIMER0_TMR0L 0xC2 // 0xDC 1S // 0xC2 0.5S

// Water level thresholds
#define MIN_ALLOWABLE_LEVEL 800
#define SAFE_LEVEL 500

// Global variables

extern const unsigned int HALF_PERIOD1;
extern const unsigned int FULL_PERIOD1;
extern const unsigned int HALF_PERIOD2;
extern const unsigned int FULL_PERIOD2;
extern const unsigned int HALF_PERIOD3;
extern const unsigned int FULL_PERIOD3;

extern unsigned int ADC_WATER_LVL;
extern unsigned char WATER_STATUS;
extern unsigned char GATE_STATUS;

extern unsigned int ALARM_BUZZER_COUNT;

extern const unsigned char GATE_1_TO_BE_CLOSE;
extern const unsigned char GATE_2_CLOSING;
extern const unsigned char GATE_3_CLOSE;
extern const unsigned char GATE_4_TO_BE_OPEN;
extern const unsigned char GATE_5_OPENING;
extern const unsigned char GATE_6_OPEN;
extern const unsigned char GATE_7_STOP;