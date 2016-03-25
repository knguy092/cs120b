/*Name: Kevin Nguyen, knguy092@ucr.edu
* Partner(s) Name & E≠mail: Jeet Thakkar, jthak002@ucr.edu
* Lab Section:021
* Assignment: Lab #2 Exercise #2
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/

#include <avr/io.h>

enum States{start, inc, dec, reset, doNothing} state;
unsigned char counter = 0;

void Tick(){
	unsigned char button = (~PINA) & 0x03;  //not PINA and AND it with 0x03 
	switch(state){
		case start:
			state = doNothing;
			break;
		
		case inc:
			if (button == 0x01){
				state = inc;
			}
			else{
				state = doNothing;
			}
			break;
		
		case dec:
			if (button == 0x02){
				state = dec;
			}
			else{
				state = doNothing;
			}
			break;
		
		case reset:
			if (reset == 0x03){
				state = reset;
			}
			else {
				state = doNothing;
			}
			break;
		
		case doNothing:
			if (button == 0x01){
				state = inc;
				if (counter < 9){
					counter++;}
			}
			else if (button == 0x02){
				state = dec;
				if (counter > 0){
					counter--;}
			}
			else if (button == 0x03){
				state = reset;
				counter = 0;
			}
			break;
		
		default:
			state = start;
			break;
		
	}
	PINB = counter;
}

int main(void)
{
    /* Replace with your application code */
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRB = 0xFF;
	PORTB = 0x00;
	state = start;
    while (1) 
    {
		Tick();
    }
}

