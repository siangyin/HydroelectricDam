#pragma config FEXTOSC = XT
#pragma config WDTE = OFF
#pragma config LVP = OFF
#define _XTAL_FREQ 4000000

extern unsigned int ADC_WATER_LVL;
extern unsigned char GATE_STATUS;

extern const unsigned int MAX_COUNT_VALUE_16BIT_TIMER;
extern unsigned int ALARM_BUZZER_COUNT;
extern const unsigned int HALF_PERIOD1;
extern const unsigned int FULL_PERIOD1;

extern const unsigned int HALF_PERIOD2;
extern const unsigned int FULL_PERIOD2;

extern const unsigned int HALF_PERIOD3;
extern const unsigned int FULL_PERIOD3;