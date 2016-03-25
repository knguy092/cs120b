/*Name: Kevin Nguyen, knguy092@ucr.edu
* Partner(s) Name & Email: Jeet Thakkar, jthak002@ucr.edu
* Lab Section:021
* Assignment: Lab #3 Exercise #4
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/
#include <avr/io.h>

enum States {
	init,
	wait,
	Press1,
	Press1_wait,
	Press2,
	Press2_wait,
	Inside,
	Inside_Wait
	} state;

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}

unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}

unsigned char lock = 0;
unsigned char unlock = 1;

void tick_lock()
{
	switch(state){
		case init:
				PORTB = 0x00;
				state = wait;
			break;
		case wait:
			//PORTC = 0x01;
			if(!GetBit(PINA, 2) && GetBit(PINA,0) && GetBit(PINA, 1) && GetBit(PINA, 7))
				state = Press1;
			else if(GetBit(PINA,0) && GetBit(PINA, 1) && GetBit(PINA, 2) && !GetBit(PINA,7))
				state = Inside;
			else if(GetBit(PINA,0) && !GetBit(PINA, 1) && GetBit(PINA, 2) && GetBit(PINA,7) && lock == 1)
				state = Press2;
			else
				state = wait;
			break;
		case Press1:
			PORTC = 0x02;
				if(lock == 1)
				{
					PORTC = 0x0E;
				}
				lock = 1;
				state = wait;
			break;
		case Press2:
			state = wait;
			if(unlock == 0){
				 PORTB = 0x00;
				 unlock = 1;
				 lock = 0;
				 PORTC = 0x09;
			}
			else {
				PORTB = 0x01;
				PORTC = 0x0F;
				unlock = 0;
				lock = 0;
			}
			break;
		case Inside:
			PORTC = 0x04;
			state = Inside_Wait;
			lock = 0;
			unlock = 1;
			PORTB = 0x00;
			break;
		case Inside_Wait:
			PORTC = 0x05;
			if((GetBit(PINA,0) && GetBit(PINA, 1) && GetBit(PINA, 2) && !GetBit(PINA,7)))
				state = Inside_Wait;
			else
				state = wait;
			break;
		default: state = wait;
	}
	
}



int main(void)
{
	 DDRA = 0x00;
	 PORTA = 0xFF;
	 
	 DDRB = 0xFF;
	 PORTB = 0x00;
	 
	 DDRC = 0xFF;
	 PORTC = 0x00;
	 
	 state = init;
	 
	 while(1)
	 {
		 tick_lock();
	 }
}