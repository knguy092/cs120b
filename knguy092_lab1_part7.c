/*Name: Kevin Nguyen, knguy092@ucr.edu
* Partner(s) Name & E­mail: Jeet Thakkar, jthak002@ucr.edu
* Lab Section:021
* Assignment: Lab #1 Exercise #7
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/
#include <avr/io.h>


int main(void)
{
    /* Replace with your application code */
	DDRA = 0x00;   //input
	PORTA = 0xFF;
	DDRB = 0x00;
	PORTB = 0xFF;
	DDRC = 0x00;
	PORTC = 0xFF;
	
	DDRD = 0xFF;   //output
	PORTD = 0x00;
	
	//temp values
	unsigned char ucTempA;
	unsigned char ucTempB;
	unsigned char ucTempC;
	unsigned char ucTempD;
    while (1) 
    {
		//so there are three seats A, B, C
		//each seat has 8 bits that measure up to 255 kg
		//PORTD0 = 1 if A + B + C > 140kg
		//PORTD1 = 1  if A - C > 80kg or vice versa???
		
		ucTempA = 0x00;
		ucTempB = 0x00;
		ucTempC = 0x00;
		ucTempD = 0x00;
		
		ucTempA = PINA;
		ucTempB = PINB;
		ucTempC = PINC;
		
		//140 in binary is 1000 1100
		//140 in hex is 0x8C
		if (ucTempA + ucTempB + ucTempC > 0x8C){
			ucTempD = ucTempD | 0x01;
		}
		
		//now check whether A or C is larger, then take the difference
		//80 in binary is 0101 0000
		//80 in hex is 0x50
		if (ucTempA > ucTempC){
			if ((ucTempA - ucTempC) > 0x50){
				ucTempD = ucTempD | 0x02;
			}
		}
		else{
			if ((ucTempC - ucTempA) > 0x50){
				ucTempD = ucTempD | 0x02;
			}
		}
		
		PORTD = ucTempD;
    }
}

