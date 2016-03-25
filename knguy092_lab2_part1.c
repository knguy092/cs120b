/*Name: Kevin Nguyen, knguy092@ucr.edu
* Partner(s) Name & E≠mail: Jeet Thakkar, jthak002@ucr.edu
* Lab Section:021
* Assignment: Lab #2 Exercise #1
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/

int main(void)
{
   /* Replace with your application code */
   DDRA = 0x00;
   PORTA = 0xFF;
   DDRC = 0xFF;
   PORTC = 0x00;
   unsigned char button_zero;
   unsigned char button_one;
   unsigned char button_two;
   unsigned char button_three;
   unsigned char ucTempA;
   unsigned char ucTempC;
   while (1)
   {
	   ucTempA = PINA;
	   ucTempC = 0x00; //sets to zero
	   button_zero = (~PINA) & 0x01;
	   button_one = (~PINA) & 0x02;
	   button_two = (~PINA) & 0x04;
	   button_three = (~PINA) & 0x08;
	   if (button_zero || button_one){//if 1 and 2
		   ucTempC = ucTempC | 0x20;
	   }
	   if ((button_zero && button_one) || button_two){//if 3 and 4
		   ucTempC = ucTempC | 0x30;
	   }
	   if ((button_two && button_zero) || (button_two && button_one)){ //if 5 or 6
		   ucTempC = ucTempC | 0x38;
	   }
	   if ((button_two && button_one && button_zero) || (button_three) || (button_three && button_zero)){//if 7 or 8 or 9
		   ucTempC = ucTempC | 0x3C;
	   }
	   if ((button_three && button_one) || (button_three && button_one && button_zero) || (button_three && button_two)){//if 10 or 11 or 12
		   ucTempC = ucTempC | 0x3E;
	   }
	   if ((button_three && button_two && button_zero) || (button_three && button_two && button_one) || (button_three && button_two && button_one && button_zero)){//if 13 or 14 or 15
		   ucTempC = ucTempC | 0x3F;
	   }
	   if (ucTempA < 0x05){//if less than 4
		   ucTempC = ucTempC | 0x40;
	   }
	   PORTC = ucTempC;
   }
}

