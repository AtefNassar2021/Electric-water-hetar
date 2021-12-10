#include <avr/io.h>
#include "config.h"
#include "mTimer.h"

void init_Timer0(int mode, int clockSelect) {

    TCCR0 &= ~((1 << WGM00) | (1 << WGM01));
    TCCR0 &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));
    
    
    
    TCCR0 |= mode;
    TCCR0 |= clockSelect;

}


void Timer0_enable_INT(int selectINT){
    TIMSK |= (1<<selectINT);
}

void setOutCompare0(unsigned char compareValue){
    OCR0 = compareValue;
}

void setOC0Mode(int OC0_Mode){
    // Config Data Direction for OC0 pin ***********
    setPinDir(_PA, PA0, OUT);
    TCCR0 &= ~((1<<COM01)|(1<<COM00));
    TCCR0 |= (OC0_Mode << COM00);
}