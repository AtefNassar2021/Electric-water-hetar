#include <avr/io.h>
#include "config.h"
#include "mSSD.h"

void SvnSEG_Disp(float num) {
    DDRB = 0xFF;
    uint8_t num_int = (uint8_t) num; // Will take values from Zero to 5
    uint8_t after_point = (num - (uint8_t) num)*10; // Will take values from Zero to 9
    PORTB &= ~(1 << PB5); // Set PB5 to Zero. Use first 7SEG
    PORTB |= (1 << PB6); // Set PB6 to One. Don't use second 7SEG
    PORTB |= (1 << PB4); // Set PB4 turning on the Decimal point.
    PORTB &= ~(1 << PB0); // Set PB0 to 0
    PORTB &= ~(1 << PB1); // Set PB1 to 0
    PORTB &= ~(1 << PB2); // Set PB2 to 0
    PORTB &= ~(1 << PB3); // Set PB3 to 0 


    PORTB |= num_int; // Set the lower 4 bits of Port D (PD0 - PD3) to the bits of the number.
    _delay_ms(30);
    PORTB |= (1 << PB5); // Set PB5 to One. Don't use first 7SEG
    PORTB &= ~(1 << PB6); // Set PB6 to Zero. Use second 7SEG
    PORTB |= (1 << PB4); // Set PB4 turning on the Decimal point.
    PORTB &= ~(1 << PB0); // Set PB0 to 0
    PORTB &= ~(1 << PB1); // Set PB1 to 0
    PORTB &= ~(1 << PB2); // Set PB2 to 0
    PORTB &= ~(1 << PB3); // Set PB3 to 0


    PORTB |= after_point; // Set the lower 4 bits of Port D (PD0 - PD3) to the bits of the number.
    _delay_ms(30);
}