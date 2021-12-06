#include <avr/io.h>
#include  "config.h"
#include  "mTimer2.h"

void init_Timer2(int mode, int clockSelect) {

    TCCR2 &= ~((1 << WGM00) | (1 << WGM01));
    TCCR2 &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));
    
    TCCR2 |= mode;
    TCCR2 |= clockSelect;
}


void Timer2_enable_INT(int selectINT){
    TIMSK |= (1<<selectINT);
}

void setOutCompare2(unsigned char compareValue){
    OCR2 = compareValue;
}

void setOC0Mode2(int OC0_Mode){
    // Config Data Direction for OC0 pin ***********
    setPinDir(_PA, PA0, OUT);
    TCCR2 &= ~((1<<COM01)|(1<<COM00));
    TCCR2 |= (OC0_Mode << COM00);
}
