#pragma config FEXTOSC = XT
#pragma config WDTE = OFF
#pragma config LVP = OFF

#define _XTAL_FREQ 4000000

#define TIMER0_TMR0H 0xC2 // 0x0B 1S// 0xC2  0.5S
#define TIMER0_TMR0L 0xC2 // 0xDC 1S // 0xC2 0.5S

#define PB0 PORTBbits.RB0
#define PB1 PORTBbits.RB1
#define TS2 PORTBbits.RB2
#define TS4 PORTBbits.RB4

#define LED1 PORTAbits.RA1
#define LED2 PORTAbits.RA2
#define LED3 PORTAbits.RA3

#define MIN_ALLOWABLE_LEVEL 800
#define SAFE_LEVEL 500

extern const unsigned int MAX_COUNT_VALUE_16BIT_TIMER;

extern const unsigned int HALF_PERIOD1;
extern const unsigned int FULL_PERIOD1;
extern const unsigned int HALF_PERIOD2;
extern const unsigned int FULL_PERIOD2;
extern const unsigned int HALF_PERIOD3;
extern const unsigned int FULL_PERIOD3;

extern unsigned int ADC_WATER_LVL;
extern unsigned char WATER_STATUS;
extern unsigned char GATE_STATUS;
extern unsigned char GATE_MODE;
extern unsigned int ALARM_BUZZER_COUNT;

extern const unsigned char GATE_1_TO_BE_CLOSE;
extern const unsigned char GATE_2_CLOSING;
extern const unsigned char GATE_3_CLOSE;
extern const unsigned char GATE_4_TO_BE_OPEN;
extern const unsigned char GATE_5_OPENING;
extern const unsigned char GATE_6_OPEN;
extern const unsigned char GATE_7_STOP;