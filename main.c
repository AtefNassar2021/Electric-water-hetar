/*****************LIBRARIES******************/

#include <avr/io.h>
#include "config.h"
#include "mTimer.h"
#include "mADC.h"
#include "mSSD.h"
#include "mExternalInterrupt.h"

/*****************VARIABLES*****************/

static float temp = 60; //Initial Temp
static float data = 0; //ADC Read
static int avg = 0; //Average Of 10 Readings

/***************PUSH BUTTONS*********/

ISR(INT0_vect) { //UP Button
    if (temp < 75) { //Max Req Temp Is 75
        temp += 5; //One Click Means 5 Increments
    } else {
    }
}

ISR(INT1_vect) { //DOWN Button
    if (temp > 35) { //Min Req Temp Is 35
        temp -= 5; //One Click Means 5 Increments
    } else {
    }
}

/***************TIMER***************/

ISR(TIMER0_COMP_vect) {
    /*Time Here In (ms)*/
    static int t = 0;
    static int h = 0;
    static int c = 0;
    static int temp1;
    temp1 = temp;
    t++;
    h++;
    c++;
    if (t == 100) { // CPU FRQ / PRESCALER / NO.BITS = NO.TICKS --> Req Time 100ms
        ADC_SC();
        data += ADC_read() * 0.4887585532746823;
        t = 0;
    } else {
    }
    if (h == 1000) { // CPU FRQ / PRESCALER / NO.BITS = NO.TICKS --> Req Time 1s = 1000ms
        avg = data / 10;
        data = 0;
        if (!(PINC & (1 << PC4))) {
            togglePinData(_PC, PINC0); //Heating Element Led Blink Every 1 Sec
            h = 0;
        } else {
        }
    }
    if (c == 5000 && temp == temp1) {
        setPinData(_PB, PINB5, OFF);
        setPinData(_PB, PINB6, OFF);
    }
}

/******************MAIN CODE******************/

int main(void) {

    /***************INITIANLIZATION**************/

    setPortDir(_PD, IN);
    init_INT(_INT0, _Mode_Rising);
    init_INT(_INT1, _Mode_Rising);
    setPinDir(_PC, PC2, OUT); //Cooler Is Output
    setPinDir(_PC, PC4, OUT); //Heater Is Output
    setOC0Mode(ClearOnComp);
    setOutCompare(250); // 0 ~ 255 
    init_Leds();
    init_ADC(_CH0, _AVCC, _PRE128);
    //init_LCD_4bit();
    Timer_enable_INT(INT_TOC);
    init_Timer(CTC, _CLk_64);
    sei();

    /****************DYNAMIC CODE****************/
    while (1) {
        while (isPressed(_PD, PIND4)) {
            SvnSEG_Disp(temp / 10);
            if (temp - avg == 5 && avg != 0) {
                setPinData(_PC, PINC4, ON); //Turn ON Heater When It Reaches The Req Temp
                setPinData(_PC, PINC2, OFF); //Turn OFF Cooler When It Reaches The Req Temp
            } else {
            }
            if (avg - temp == 5 && avg != 0) {
                setPinData(_PC, PINC2, ON); //Turn ON Cooler When It Reaches The Req Temp
                setPinData(_PC, PINC4, OFF); //Turn OFF Heater When It Reaches The Req Temp
                set_Led(Led0, ON);
            } else {
            }
            if (temp == avg && avg != 0) { // When The Temp Of Water Equals The The Req Temp
                setPinData(_PC, PINC2, OFF); //Turn OFF Cooler When It Reaches The Req Temp
                setPinData(_PC, PINC4, OFF); //Turn OFF Heater When It Reaches The Req Temp
                set_Led(Led0, OFF);
            } else {
            }
        }
    }
    return 0;
}