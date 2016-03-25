/*Name: Kevin Nguyen, knguy092@ucr.edu
* Partner(s) Name & Email: Jeet Thakkar, jthak002@ucr.edu
* Lab Section:021
* Assignment: Lab #3 Exercise #2
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/


#include <avr/io.h>
//REMEMBER TO SWITCH FROM PORTB TO PORTC 

//README ^^^^^^^^
enum States{start, Init, Do_Nothing, Inc, Dec, Reset} state;
unsigned char counter = 0x00;
	
void Tick(){
	unsigned char button = (~PINA) & 0x03;
	switch(state){
		default:
			state = start;
			break;
		
		case start:
			state = Init;
			break;
			
		case Init:
			counter = 0x07;
			state = Do_Nothing;
			break;
			
		case Do_Nothing:
			if (button == 0x01){
				if (counter < 0x09){
					state = Inc;
					counter++;
				}
				else{
					state = Do_Nothing;
				}
			}
			else if (button == 0x02){
				if (counter > 0x00){
					state = Dec;
					counter--;
				}
				else{
					state = Do_Nothing;
				}
			}
			else if (button == 0x03){
				state = Reset;
			}
			break;
			
		case Inc:
			if (button == 0x01){
				state = Inc;
			}
			else if (button == 0x00){
				state = Do_Nothing;
			}
			else if (button == 0x03){
				state = Reset;
			}
			break;
			
		case Dec:
			if (button == 0x02){
				state = Dec;
			}
			else if (button == 0x03){
				state = Reset;
			}
			else if (button == 0x00){
				state = Do_Nothing;
			}
			break;
			
		case Reset:
			counter = 0x00;
			if (button == 0x03){
				state = Reset;
			}
			else{
				state = Do_Nothing;
			}
			break;
			
			
	}
	PORTC = counter;
}


int main(void)
{
	DDRA = 0x00;
	PORTA = 0xFF;
	
	DDRC = 0xFF; //replace with PORTC
	PORTC = 0x00;
	
	state = start;
    /* Replace with your application code */
    while (1) 
    {
		Tick();
    }
}

