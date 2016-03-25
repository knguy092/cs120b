/*Name: Kevin Nguyen, knguy092@ucr.edu
* Partner(s) Name & Email: Jeet Thakkar, jthak002@ucr.edu
* Lab Section:021
* Assignment: Lab #3 Exercise #5
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/
#include <avr/io.h>

enum States{init, press1, press2, press3, press4, press5, press6, do_nothing, unlock} state;
unsigned char button_x;
unsigned char button_y;
unsigned char button_hash;
unsigned char button_7;
	
void tick(){
	button_x = (~PINA) & 0x01;
	button_y = (~PINA) & 0x02;
	button_hash = (~PINA) & 0x04;
	button_7 = (~PINA) & 0x80;
	
	switch(state){
		default:
			state = init;
			break;
			
		case init:
			state = do_nothing;
			break;
			
		case do_nothing:
			PORTB = 0x00;
			if (!button_hash){
				state = do_nothing;
			}
			else{
				state = press1;
			}
			break;
			
		case press1:
			if (!button_x){
				state = do_nothing;
			}
			else{
				state = press2;
			}
			break;
			
		case press2:
			if (!button_y){
				state = do_nothing;
			}
			else{
				state = press3;
			}
			break;
			
		case press3:
			if(!button_x){
				state = do_nothing;
			}
			else{
				state = unlock;
			}
			break;
			
		case unlock:
			PORTB = 0x01;
			if (button_7){
				state = do_nothing;
			}
			else if (button_hash){
				state = press4;
			}
			else{
				state = unlock;
			}
			break;
			
			case press4:
			if (!button_x){
				state = do_nothing;
			}
			else{
				state = press5;
			}
			break;
			
			case press5:
			if (!button_y){
				state = do_nothing;
			}
			else{
				state = press6;
			}
			break;
			
			case press6:
			if(!button_x){
				state = do_nothing;
			}
			else{
				state = do_nothing;
			}
			break;
		
			
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
		 tick();
	 }
}