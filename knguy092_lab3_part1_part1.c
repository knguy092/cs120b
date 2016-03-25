/*Name: Kevin Nguyen, knguy092@ucr.edu
* Partner(s) Name & Email: Jeet Thakkar, jthak002@ucr.edu
* Lab Section:021
* Assignment: Lab #3 Exercise #1
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/


#include <avr/io.h>
enum States{start, Do_nothing, Do_Nothing2, Press, Press2} state;
	
void Tick(){
	unsigned char button =  (~PINA) & 0x01;
	
	switch(state){
		default:
			state = start;
			break;
			
		case start:
			state = Do_nothing;
			break;
		
		case Do_nothing:
			PORTB = 0x01;
			if (button == 0x00){
				state = Do_nothing;
			}
			else if (button == 0x01){
				PORTB = 0x02;
				state = Press;
			}
			break;
		
		case Do_Nothing2:
			PORTB = 0x02;
			if ( button == 0x00){
				state = Do_Nothing2;
			}
			else if (button == 0x01){
				PORTB = 0x01;
				state = Press2;
			}
			break;
		
		case Press:
			if (button == 0x01){
				state = Press;
			}
			else if (button == 0x00){
				state = Do_Nothing2;
			}
			break;
		
		case Press2:
			if (button == 0x01){
				state = Press2;
			}
			else if (button == 0x00){
				state = Do_nothing;
			}
			break;
			
	}
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

