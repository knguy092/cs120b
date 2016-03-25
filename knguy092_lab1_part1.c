/*Name: Kevin Nguyen, knguy092@ucr.edu
* Partner(s) Name & E­mail: Jeet Thakkar, jthak002@ucr.edu
* Lab Section:021
* Assignment: Lab #1 Exercise #1
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/

#include <avr/io.h>


int main(void)
{
    /* Replace with your application code */
	DDRB = 0xFF;
	PORTB = 0x00;
	DDRA = 0x00;
	PORTA = 0xFF;
	unsigned char tempA0 = 0x00;
	unsigned char tempA1 = 0x00;
	unsigned char tempB = 0x00;
    while (1) 
    {
		tempA0 = PINA & 0x01; //sets tempA0 to the zero bit of pinA
		tempA1 = PINA & 0x02; //sets tempA1 to the first bit of pinA
		if (tempA1 == 0x00 && tempA0 == 0x01){
			tempB = 0x01;
		}

		else{
			tempB = 0x00;
		}
		PORTB = tempB;
    }


	PORTB = tempB;
}

