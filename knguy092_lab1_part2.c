/*Name: Kevin Nguyen, knguy092@ucr.edu
* Partner(s) Name & E­mail: Jeet Thakkar, jthak002@ucr.edu
* Lab Section:021
* Assignment: Lab #1 Exercise #2
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/
#include <avr/io.h>


int main(void)
{
    DDRA = 0x00;
	PORTA = 0xFF;
	DDRC = 0xFF;
	PORTC = 0x00;

	unsigned char numSpaces = 0x00;
    while (1) 
    {
		numSpaces = 0x00;  //resets numSpaces everytime the while loop starts
		if (PINA & 0x01){ //checks to see if PINA at the zero bit is "occupied or not"
			numSpaces = numSpaces + 1;
		}
		if (PINA & 0x02){ //chcks the first bit of PINA
			numSpaces = numSpaces + 1;
		}
		if (PINA & 0x04){ //so on and so forth
			numSpaces = numSpaces + 1;
		}
		if (PINA & 0x08){
			numSpaces = numSpaces + 1;
		}
		PORTC = 4 -numSpaces;
		
    }
}

