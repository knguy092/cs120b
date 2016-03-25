/*Name: Kevin Nguyen, knguy092@ucr.edu
* Partner(s) Name & E­mail: Jeet Thakkar, jthak002@ucr.edu
* Lab Section:021
* Assignment: Lab #1 Exercise #6
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
   unsigned char ucTempA;
   unsigned char ucTempC;
   while (1)
   {
	   ucTempA = PINA;
	   ucTempC = 0x00; //sets to zero
	   if ((ucTempA & 0x0F) == 0x00){
		   ucTempC = ucTempC | 0x40;
	   }
	   if (((ucTempA & 0x0F)==0x01) || ((ucTempA & 0x0F) == 0x02)){
		   ucTempC = ucTempC | 0x20;
		   ucTempC = ucTempC | 0x40;
	   }
	   if (((ucTempA & 0x0F) == 0x03) || ((ucTempA & 0x0F) == 0x04)){
		   ucTempC = ucTempC | 0x30;
		   ucTempC = ucTempC | 0x40;
	   }
	   if (((ucTempA & 0x0F) == 0x05) || ((ucTempA & 0x0F) == 0x06)){
		   ucTempC = ucTempC | 0x38;
	   }
	   if (((ucTempA & 0x0F) == 0x07) || ((ucTempA & 0x0F) == 0x08) || ((ucTempA & 0x0F) == 0x09)){
		   ucTempC = ucTempC | 0x3C;
	   }
	   if (((ucTempA & 0x0F) == 0x0A) || ((ucTempA & 0x0F) == 0x0B) || ((ucTempA & 0x0F) == 0x0C)){
		   ucTempC = ucTempC | 0x3E;
	   }
	   if (((ucTempA & 0x0F) == 0x0D) || ((ucTempA & 0x0F) == 0x0E) || ((ucTempA & 0x0F) == 0x0F)){
		   ucTempC = ucTempC | 0x3F;
	   }
	  // if (ucTempA < 0x05){
	//	   ucTempC = ucTempC | 0x40;
	   //}
	   if (((ucTempA & 0x10) == 0x10) && ((ucTempA & 0x20) == 0x20) && ((ucTempA & 0x40) == 0x00)){
		   ucTempC = ucTempC | 0x80;
	   }
	   PORTC = ucTempC;
   }
}

