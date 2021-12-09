#ifndef CONFIG_H
#define	CONFIG_H


#define F_CPU 16000000UL

#define Relay   PA2
#define Buzzer  PA3


#define Led0    PC0
#define Led1    PC1
#define Led2    PC2


#define ON     1
#define OFF    0

#define OUT     1
#define IN      0


#define Btn0   2 //PB2
#define Btn1   3 //PB3
#define Btn2   4 //PB4

#define _PA    0
#define _PB    1
#define _PC    2
#define _PD    3

#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include "mIO.h"

#endif	/* CONFIG_H */

