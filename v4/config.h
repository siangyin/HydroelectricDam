#pragma config FEXTOSC = XT
#pragma config WDTE = OFF
#pragma config LVP = OFF

#define _XTAL_FREQ 4000000

#define TIMER0_TMR0H 0x0B // 0xC2 
#define TIMER0_TMR0L 0xDC // 0xF7

#define PB0 PORTBbits.RB0
#define PB1 PORTBbits.RB1
#define TS2 PORTBbits.RB2
#define TS4 PORTBbits.RB4

#define LED1 PORTAbits.RA1
#define LED2 PORTAbits.RA2
#define LED3 PORTAbits.RA3
#define BUZZER PORTBbits.RB3 // Buzzer is connected at RB3

#define MIN_ALLOWABLE_LEVEL 800
#define SAFE_LEVEL 500

extern const unsigned int HALF_PERIOD1;
extern const unsigned int FULL_PERIOD1;

extern const unsigned int HALF_PERIOD2;
extern const unsigned int FULL_PERIOD2;

extern const unsigned int HALF_PERIOD3;
extern const unsigned int FULL_PERIOD3;

extern unsigned int ADC_WATER_LEVEL;
extern char WATER_STATE[];
extern unsigned char GATE_STATUS_VALUE;
extern char GATE_STATUS_TEXT[];

extern unsigned int ALARM_BUZZER_COUNT;