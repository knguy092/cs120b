/*Name: Kevin Nguyen, knguy092@ucr.edu
* Partner(s) Name & E≠mail: Jeet Thakkar, jthak002@ucr.edu
* Lab Section:021
* Assignment: Lab #2 Exercise #3
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/

#include <avr/io.h>

enum States(start, iterate, doNothing) state;
unsigned char button = 0;
unsigned char counter = 0;

void Tick(){
	button = (~PINA) & 0x01;  //checks the zero bit
	
	default:
		state = start;
		break;
		
	case iterate:
		if (button == 0x01){
			state = iterate;
		}
		else 
		{
			state = doNothing;
		}
		break;
		
	case doNothing:
		if (button == 0x01){
			if (counter < 6){
				state = increment;
				counter++;
			}
			else if (counter == 6){
				state = doNothing;
				counter = 0;
			}
		}
		else{
			state = doNothing;
		}
		break;
		
		PINB = counter;
}

int main(void)
{
    /* Replace with your application code */
	DDRB = 0xFF;
	PORTB = 0x00;
	DDRA = 0x00;
	PORTA = 0xFF;
	
	state = start;
    while (1) 
    {
		Tick();
    }
}

