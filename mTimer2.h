#ifndef MTIMER2_H
#define	MTIMER2_H

#define NORMAL  0
#define PWM     0x40 // 1
#define CTC     0x08 // 2
#define FPWM    0x48 // 3


#define _TimerOff     0
#define _NoPRE        1
#define _CLk_8        2
#define _CLk_64       3
#define _CLk_256      4
#define _CLk_1024     5

#define _CLk_ext_F    6
#define _CLk_ext_R    7

#define INT_TOV2     TOIE2     
#define INT_TOC2     OCIE2

#define ClearOnComp   2
#define SetOnComp     3


void init_Timer2(int mode, int clockSelect);

void Timer2_enable_INT(int selectINT);
void setOutCompare2(unsigned char compareValue);
void setOC2Mode(int OC2_Mode);

#endif	/* MTIMER2_H */

