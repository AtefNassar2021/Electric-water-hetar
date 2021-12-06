/*****************LIBRARIES*********************/

#include <avr/io.h>
#include "config.h"
#include "mTimer.h"
#include "mTimer2.h"
#include "mADC.h"
#include "mSSD.h"
#include "mExternalInterrupt.h"

/*****************VARIABLES*********************/

static float temp = 60; //Initial Temp
char data = 0; // Temp Sensor Read

/***************PUSH BUTTONS***************/
ISR(INT0_vect) { //UP Button
    temp += 5; //One Click Means 5 Increments
    SvnSEG_Disp(temp / 10); //Display The New Temp
    //        setPinData(_PC, PC6, ON); //Turn ON Heater Until It Reaches The Req Temp
    //        set_Led(Led0, OFF);
}

ISR(INT1_vect) { //DOWN Button
    temp -= 5; //One Click Means 5 Increments
    SvnSEG_Disp(temp / 10); //Display The New Temp
    //        setPinData(_PC, PC6, ON); //Turn ON Heater Until It Reaches The Req Temp
    //        set_Led(Led0, OFF);
}

/***************TIMER***************/

ISR(TIMER0_COMP_vect) {
    static int t = 0;
    static int h = 0;
    t++;
    h++;
    if (t == 100) { // CPU FRQ / PRESCALER / NO.BITS = NO.TICKS --> Req Time 100ms
        ADC_SC();
        data = ADC_read();
        /*E2PROM*/
        t = 0;
    } else {
    }
    if (h == 1000) { // CPU FRQ / PRESCALER / NO.BITS = NO.TICKS --> Req Time 100ms
        if (PINC & (1 << PC6)) {
            togglePinData(_PC, PC0); //Heating Element Led Blink Every 1 Sec
            h = 0;
        } else {
            /*E2PROM*/
            h = 0;
        }
    }
}

/******************MAIN CODE******************/

int main(void) {

    /***************INITIANLIZATION**************/
    
    init_INT(_INT0, _Mode_Rising);
    init_INT(_INT1, _Mode_Rising);
    setOC0Mode(ClearOnComp);
    init_Timer(CTC, _CLk_64);
    setOutCompare(250); // 0 ~ 255  
    sei();
    init_Leds();
    
    /*****************ADD IO******************/

    setPinDir(_PC, PC6, OUT); //Heater Is Output
    setPinDir(_PC, PC3, OUT); //Cooler Is Output

    /****************DYNAMIC CODE****************/

    while (isPressed(_PD, PIND4)) {
        SvnSEG_Disp(temp / 10);
        if (temp == data) { // When The Temp Of Water Equals The The Req Temp
            setPinData(_PC, PC6, OFF); //Turn OFF Heater When It Reaches The Req Temp
            setPinData(_PC, PC3, OFF); //Turn OFF Heater When It Reaches The Req Temp
            set_Led(Led0, OFF);
        } else {
        }
    }
    return 0;
}