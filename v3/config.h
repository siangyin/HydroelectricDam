#pragma config FEXTOSC = XT
#pragma config WDTE = OFF
#pragma config LVP = OFF

#define _XTAL_FREQ 4000000

extern unsigned int SCHEDULED_GATE_CONTROL; // 1 | 0
extern unsigned int ADC_WATER_LVL; 
extern unsigned char GATE_STATUS; 


