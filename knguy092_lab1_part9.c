/*Name: Kevin Nguyen, knguy092@ucr.edu
* Partner(s) Name & E­mail: Jeet Thakkar, jthak002@ucr.edu
* Lab Section:021
* Assignment: Lab #1 Exercise #9
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/

#include <avr/io.h>


int main(void)
{
    /* Replace with your application code */
	DDRD = 0x00;
	PORTD = 0xFF;
	DDRB = 0xFF;
	PORTB = 0x00;
	unsigned char ucTempD;
	unsigned char ucTempB;
    while (1) 
    {
		ucTempD = 0x00;
		ucTempB = 0x00;
		
		ucTempD = PIND;
		
		//70 in binary is 0100 0110
		//70 in hex is 0x46
		
		if (ucTempD > 0x45){
			//if the PIND is greater than or equal to 70
			ucTempB = ucTempB | 0x02;
		}
		if ((ucTempD < 0x46) && (ucTempD > 0x05)){
			//if PIND is less than 70 but greater than 5
			ucTempB = ucTempB | 0x04;
		}
		
		PORTB = ucTempB;
    }
}

