/*Name: Kevin Nguyen, knguy092@ucr.edu
* Partner(s) Name & Email: Jeet Thakkar, jthak002@ucr.edu
* Lab Section:021
* Assignment: Lab #6 Exercise #3
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/

#include <avr/io.h>

void ADC_init()
{
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	// in Free Running Mode, a new conversion will trigger
	// whenever the previous conversion completes.
}

int main(void)
{
	DDRB = 0xFF;
	PORTB = 0x00;
	
	DDRD = 0xFF;
	PORTD = 0x00;
	
	unsigned char b_value = 0x00;
	unsigned char d_value = 0x00;
	unsigned char max_div2 = 0x20;

	ADC_init();
	while(1)
	{
		unsigned short adc_value = ADC;
		if(adc_value >= max_div2)
		{
			pb_value = (char)adc_value;
			pd_value = (char)(adc_value >> 8);
			
			PORTB = b_value;
			PORTD = d_value;
		}
		else
		{
			PORTB = 0x00;
			PORTD = 0x00;
		}
	}
}
