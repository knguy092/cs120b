/*Name: Kevin Nguyen, knguy092@ucr.edu
* Partner(s) Name & E­mail: Jeet Thakkar, jthak002@ucr.edu
* Lab Section:021
* Assignment: Lab #1 Exercise #5
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/
#include <avr/io.h>


int main(void)
{
    /* Replace with your application code */
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRC = 0xFF;
	PORTC = 0x00;
	unsigned char ucTempA;
	unsigned char ucTempC;
    while (1) 
    {
		ucTempA = PINA; 
		ucTempC = 0x00; //sets to zero
		if (((ucTempA & 0x01)==0x01) || ((ucTempA & 0x02) == 0x02)){
			ucTempC = ucTempC | 0x20;
		}
		if (((ucTempA & 0x03) == 0x03) || ((ucTempA & 0x04) == 0x04)){
			ucTempC = ucTempC | 0x30;
		}
		if (((ucTempA & 0x05) == 0x05) || ((ucTempA & 0x06) == 0x06)){
			ucTempC = ucTempC | 0x38;
		}
		if (((ucTempA & 0x07) == 0x07) || ((ucTempA & 0x08) == 0x08) || ((ucTempA & 0x09) == 0x09)){
			ucTempC = ucTempC | 0x3C;
		}
		if (((ucTempA & 0x0A) == 0x0A) || ((ucTempA & 0x0B) == 0x0B) || ((ucTempA & 0x0C) == 0x0C)){
			ucTempC = ucTempC | 0x3E;
		}
		if (((ucTempA & 0x0D) == 0x0D) || ((ucTempA & 0x0E) == 0x0E) || ((ucTempA & 0x0F) == 0x0F)){
			ucTempC = ucTempC | 0x3F;
		}
		if (ucTempA < 0x05){
			ucTempC = ucTempC | 0x40;
		}
		PORTC = ucTempC;
    }
}

