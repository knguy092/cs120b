/*Name: Kevin Nguyen, knguy092@ucr.edu
* Partner(s) Name & E­mail: Jeet Thakkar, jthak002@ucr.edu
* Lab Section:021
* Assignment: Lab #1 Exercise #4
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/
#include <avr/io.h>


int main(void)
{
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRB = 0x00;
	PORTB = 0xFF;
	DDRC = 0xFF;
	PORTC = 0x00;
	unsigned char tempA;
	unsigned char tempB;
	unsigned char ucNumA;
	unsigned char ucNumB;
    /* Replace with your application code */
    while (1) 
    {
		tempA = PINA;
		ucNumA = 0x00;
		ucNumB = 0x00;
		for (unsigned char i = 0x00; i < 8; ++i){
			if (tempA & 0x80){
				ucNumA = ucNumA + 1;
			}
			tempA = tempA << 1;  //left shift
		}
		
		tempB = PINB;
		for (unsigned char i = 0x00; i < 8; ++i){
			if (tempB & 0x80){
				ucNumB = ucNumB + 1;  //left shift
			}
			tempB = tempB << 1;
		}
		//PORTA = ucNumA;
		//PORTB = ucNumB;
		PORTC = ucNumA + ucNumB;
    }
}

