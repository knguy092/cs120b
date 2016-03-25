/*Name: Kevin Nguyen, knguy092@ucr.edu
* Partner(s) Name & E­mail: Jeet Thakkar, jthak002@ucr.edu
* Lab Section:021
* Assignment: Lab #1 Exercise #8
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
	DDRB = 0xFF;
	PORTB = 0x00;
	DDRC = 0xFF;
	PORTC = 0x00;
	unsigned char ucTempA;
	unsigned char ucTempB;
	unsigned char ucTempC;
    while (1) 
    {
		ucTempA = 0x00;	//resets the temps again after every loop
		ucTempB = 0x00;
		ucTempC = 0x00;
		
		
		ucTempA = PINA;
		if ((ucTempA & 0x80) == 0x80){
			ucTempB = ucTempB | 0x08;
		}
		if ((ucTempA & 0x40) == 0x40){
			ucTempB = ucTempB | 0x04;
		}
		if ((ucTempA & 0x20) == 0x20){
			ucTempB = ucTempB | 0x02;
		}
		if ((ucTempA & 0x10) == 0x10){
			ucTempB = ucTempB | 0x01;
		}
		if ((ucTempA & 0x08) == 0x08){
			ucTempC = ucTempC | 0x80;
		}
		if ((ucTempA & 0x04) == 0x04){
			ucTempC = ucTempC | 0x40;
		}
		if ((ucTempA & 0x02) == 0x02){
			ucTempC = ucTempC | 0x20;
		}
		if ((ucTempA & 0x01) == 0x01){
			ucTempC = ucTempC | 0x10;
		}
		
		
		PORTB = ucTempB;
		PORTC = ucTempC;
    }
}

