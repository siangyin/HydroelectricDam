#include <xc.h>
#include "config.h"

void initSysPWM_5(void) {
    CCPTMRS1 = 0b00000100;
    PWM6CON = 0b00000000;
    T2PR = 0X7C;
    PWM6DCH = 0b00000110;
    PWM6DCL = 0b01000000;
    T2CON = 0b11110000;
    T2CLKCON = 0b00000001;
    RA1PPS = 0x0E;
    RA2PPS = 0x0E;
    RA3PPS = 0x0E;
}

void initSysPWM_10(void) {
    CCPTMRS1 = 0b00000100;
    PWM6CON = 0b00000000;
    T2PR = 0X7C;
    PWM6DCH = 0b00001100;
    PWM6DCL = 0b10000000;
    T2CON = 0b11110000;
    T2CLKCON = 0b00000001;
    RA1PPS = 0x0E;
    RA2PPS = 0x0E;
    RA3PPS = 0x0E;
}


void initSysPWM_15(void) {
    CCPTMRS1 = 0b00000100;
    PWM6CON = 0b00000000;
    T2PR = 0X7C;
    PWM6DCH = 0b00010010;
    PWM6DCL = 0b11000000;
    T2CON = 0b11110000;
    T2CLKCON = 0b00000001;
    RA1PPS = 0x0E;
    RA2PPS = 0x0E;
    RA3PPS = 0x0E;
}

void initSysPWM_20(void) {
    CCPTMRS1 = 0b00000100;
    PWM6CON = 0b00000000;
    T2PR = 0X7C;
    PWM6DCH = 0b00011001;
    PWM6DCL = 0b00000000;
    T2CON = 0b11110000;
    T2CLKCON = 0b00000001;
    RA1PPS = 0x0E;
    RA2PPS = 0x0E;
    RA3PPS = 0x0E;
}

void initSysPWM_25(void) {
    CCPTMRS1 = 0b00000100;
    PWM6CON = 0b00000000;
    T2PR = 0X7C;
    PWM6DCH = 0b00011111;
    PWM6DCL = 0b10000000;
    T2CON = 0b11110000;
    T2CLKCON = 0b00000001;
    RA1PPS = 0x0E;
    RA2PPS = 0x0E;
    RA3PPS = 0x0E;
}

void initSysPWM_30(void) {
    CCPTMRS1 = 0b00000100;
    PWM6CON = 0b00000000;
    T2PR = 0X7C;
    PWM6DCH = 0b00100101;
    PWM6DCL = 0b10000000;
    T2CON = 0b11110000;
    T2CLKCON = 0b00000001;
    RA1PPS = 0x0E;
    RA2PPS = 0x0E;
    RA3PPS = 0x0E;
}

void initSysPWM_35(void) {
    CCPTMRS1 = 0b00000100;
    PWM6CON = 0b00000000;
    T2PR = 0X7C;
    PWM6DCH = 0b00101011;
    PWM6DCL = 0b11000000;
    T2CON = 0b11110000;
    T2CLKCON = 0b00000001;
    RA1PPS = 0x0E;
    RA2PPS = 0x0E;
    RA3PPS = 0x0E;
}

void initSysPWM_50(void) {
    CCPTMRS1 = 0b00000100;
    PWM6CON = 0b00000000;
    T2PR = 0X7C;
    PWM6DCH = 0b00111110;
    PWM6DCL = 0b10000000;
    T2CON = 0b11110000;
    T2CLKCON = 0b00000001;
    RA1PPS = 0x0E;
    RA2PPS = 0x0E;
    RA3PPS = 0x0E;
}


void pwm_Controller(unsigned char state) {
    switch (state) {
        case 1:
            PWM6CONbits.EN = 0;
            break;
        case 2:

            initSysPWM_5();
            PWM6CONbits.EN = 1;
            break;
        case 3:
            initSysPWM_10();
            PWM6CONbits.EN = 1;
            break;
        case 4:
            initSysPWM_15();
            PWM6CONbits.EN = 1;
            break;
        case 5:
            initSysPWM_20();
            PWM6CONbits.EN = 1;
            break;
        case 6:
            initSysPWM_25();
            PWM6CONbits.EN = 1;
            break;
        case 7:
            initSysPWM_30();
            PWM6CONbits.EN = 1;
            break;
        case 8:
            initSysPWM_35();
            PWM6CONbits.EN = 1;
            break;
        case 9:
        case 10:
            initSysPWM_50();
            PWM6CONbits.EN = 1;
            break;
        default:
            PWM6CONbits.EN = 0;

    }
}