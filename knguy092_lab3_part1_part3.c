/*Name: Kevin Nguyen, knguy092@ucr.edu
* Partner(s) Name & Email: Jeet Thakkar, jthak002@ucr.edu
* Lab Section:021
* Assignment: Lab #3 Exercise #3
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/
#include <avr/io.h>

enum States { init, pressed, released, unlocked, inside } state;

unsigned char led_c = 0x00;
unsigned char button0 = 0x00;
unsigned char button1 = 0x00;
unsigned char button2 = 0x00;
unsigned char button7 = 0x00;
unsigned char led_b = 0x00;

void Tick() {
	button0 = ~PINA & 0x01; //connects button0 to A0
	button1 = ~PINA & 0x02; //connects button1 to A1
	button2 = ~PINA & 0x04; //connects button2 to A2
	button7 = ~PINA & 0x80;
	switch(state) { // Transitions
		case init:
		if (button2) {
			state = pressed;
		}
		else {
			state = init;
		}
		break;
		
		case pressed:
		if (!button2) {
			state = released;
		}
		else if (button2)
		{
			state = pressed;
		}
		else {
			state = init;
		}
		break;
		
		case released:
		if (button0 || button2) {
			state = init;
		}
		else if (button1) {
			state = unlocked;
		}
		else if (!button1) {
			state = released;
		}
		break;
		
		case unlocked:
		if (!button1) {
			state = inside;
		}
		else {
			state = unlocked;
		}
		break;
		
		case inside:
		if (button7) {
			state = init;
		}
		else {
			state = inside;
		}
		break;
		

		default:
		state = init;
	} // Transitions

	switch(state) { // State actions
		case init:
			led_c = 0x00;
			PORTC = led_c;
			led_b = 0x00;
			PORTB = led_b;
		break;
		
		case pressed:
			led_c = 0x01;
			PORTC = led_c;
		break;
		
		case released:
			led_c = 0x02;
			PORTC = led_c;
		break;
		
		case unlocked:
			led_c = 0x03; ////////////
			PORTC = led_c;
			led_b = 0x01;
			PORTB = led_b;
		break;
		
		case inside:
			led_c = 0x04;
			PORTC = led_c;
		break;
		
		default: // ADD default behaviour below
		break;
	} // State actions

}

int main(void) {

	DDRA = 0x00; //set port A as input
	PORTA = 0xFF; //set to all 1s
	DDRB = 0xFF; //set port B as output
	PORTB = 0x00; //set to all 0s
	DDRC = 0xFF; //set port C as output
	PORTC = 0x00;
	state = init; //Initial state


	while(1) {
		Tick();

	} // while (1)
} // Main