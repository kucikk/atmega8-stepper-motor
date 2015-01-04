/*
 * atmega8_stepper_motor.cpp
 *
 * Created: 4. 1. 2015 21:36:00
 *  Author: Tomáš Kučera <me@kucikk.cz> http://kucikk.cz
 */

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

#define TICK_DELAY 10


/*
uint8_t seq[8] = {
	0b1000,
	0b1100,
	0b0100,
	0b0110,
	0b0010,
	0b0011,
	0b0001,
	0b1001
};
*/
uint8_t seq[8] = {
	0b1010,
	0b1100,
	0b0101,
	0b0110,
	0b1010,
	0b0011,
	0b0101,
	0b1001
};



int main(void) {
	
	bool pressed = false;
	
	DDRB = 0xff;
	PORTB = 0x00;
	
	DDRC = 0x00;
	PORTC = 0xff;
	
    while(1) {
		pressed = !(PINC & (1 << PC5));
		
		for (uint8_t i = 0; i < 8; i++) {
			if (pressed && !(i & 0x01)) {
				continue;
			}
			PORTB = (PORTB & 0xe1) | ((seq[i] & 0x0f) << 1);
			_delay_ms(TICK_DELAY);
		}
    }
}