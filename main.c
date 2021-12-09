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
static uint8_t value = 0; //Temp Sensor Read

/***************PUSH BUTTONS*********/

ISR(INT0_vect) { //UP Button
    if (temp < 75) { //Max Req Temp Is 75
        temp += 5; //One Click Means 5 Increments
        SvnSEG_Disp(temp / 10);
    } else {
    }
}

ISR(INT1_vect) { //DOWN Button
    if (temp > 35) { //Min Req Temp Is 35
        temp -= 5; //One Click Means 5 Increments
        SvnSEG_Disp(temp / 10);
    } else {
    }
}

/***************TIMER***************/

ISR(TIMER0_COMP_vect) {
    /*Time Here In (ms)*/
    static int t = 0;
    static int h = 0;
    static int c = 0;
    int AC = 20; //Address Counter
    float temp1 = temp;
    t++;
    h++;
    c++;
    if (t == 100) { // CPU FRQ / PRESCALER / NO.BITS = NO.TICKS --> Req Time 100ms
        ADC_SC();
        data = ADC_read() * (5 / 1023) * 100;
        eeprom_write_float((float *) AC, data);
        t = 0;
        AC += 4;
    } else {
    }
    if (h == 1000) { // CPU FRQ / PRESCALER / NO.BITS = NO.TICKS --> Req Time 1s = 1000ms
        AC = 20;
        value = 0;
        for (char i = 0; i < 10; ++i) {
            value += eeprom_read_byte((const uint8_t*) AC); /* Read value from 64 address */
        }
        value = value / 10;
        if (PINC & (1 << PC4)) {
            togglePinData(_PC, PC0); //Heating Element Led Blink Every 1 Sec
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
    setOC0Mode(ClearOnComp);
    init_Timer(CTC, _CLk_64);
    setOutCompare(250); // 0 ~ 255  
    sei();
    init_Leds();
    init_ADC(_CH0, _AVCC, _PRE128);

    /*******************ADD IO********************/

    setPinDir(_PC, PC2, OUT); //Cooler Is Output
    setPinDir(_PC, PC4, OUT); //Heater Is Output

    /****************INITIAL DATA****************/



    /****************DYNAMIC CODE****************/

    while (isPressed(_PD, PIND4)) {
        SvnSEG_Disp(temp / 10);
        if (temp - data >= 5 && data != 0) {
            setPinData(_PC, PC4, ON); //Turn ON Heater When It Reaches The Req Temp
            _delay_ms(200);
        } else if (data - temp >= 5 && data != 0) {
            setPinData(_PC, PC2, ON); //Turn ON Cooler When It Reaches The Req Temp
            _delay_ms(200);
        }
        if (temp == data) { // When The Temp Of Water Equals The The Req Temp
            setPinData(_PC, PC2, OFF); //Turn OFF Cooler When It Reaches The Req Temp
            setPinData(_PC, PC4, OFF); //Turn OFF Heater When It Reaches The Req Temp
            set_Led(Led0, OFF);
        } else {
        }
    }
    return 0;
}