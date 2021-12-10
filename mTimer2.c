#include <avr/io.h>
#include "config.h"
#include "mTimer2.h"

void init_Timer2(int mode, int clockSelect) {

    TCCR2 &= ~((1 << WGM20) | (1 << WGM21));
    TCCR2 &= ~((1 << CS22) | (1 << CS21) | (1 << CS20));
    
    
    
    TCCR2 |= mode;
    TCCR2 |= clockSelect;

}


void Timer2_enable_INT(int selectINT){
    TIMSK |= (1<<selectINT);
}

void setOutCompare2(unsigned char compareValue){
    OCR2 = compareValue;
}

void setOC2Mode(int OC2_Mode){
    // Config Data Direction for OC0 pin ***********
    setPinDir(_PD, PIND7, OUT);
    TCCR2 &= ~((1<<COM21)|(1<<COM20));
    TCCR2 |= (OC2_Mode << COM20);
}