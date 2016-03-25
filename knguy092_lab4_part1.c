/*Name: Kevin Nguyen, knguy092@ucr.edu
* Partner(s) Name & Email: Jeet Thakkar, jthak002@ucr.edu
* Lab Section:021
* Assignment: Lab #4 Exercise #1
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/


#include <avr/io.h>
#include "C:/includes/io.c"
#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0;

unsigned long avr_timer_M = 1;
unsigned long avr_timer_cntcurr = 0;

void TimerOn(){
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	avr_timer_cntcurr = avr_timer_M;
	SREG = 0x80;
}

void TimerOff(){
	TCCR1B = 0x00;
}

void TimerISR(){
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect){
	avr_timer_cntcurr--;
	if (avr_timer_cntcurr == 0){
		TimerISR();
		avr_timer_cntcurr = avr_timer_M;
		
	}
}

void TimerSet(unsigned long M){
	avr_timer_M = M;
	avr_timer_cntcurr = avr_timer_M;
	
}


enum States{start, Init, Do_Nothing, Inc, Dec, Reset} state;
unsigned char counter = 0x00;

void Tick(){
	unsigned char button = (~PINA) & 0x01;
	unsigned char button2 = (~PINA) & 0x02;
	switch(state){
		default:
		state = start;
		break;
		
		case start:
		state = Init;
		break;
		
		case Init:
		state = Do_Nothing;
		break;
		
		case Do_Nothing:
		if (button && !button2){
			if (counter < 0x09){
				state = Inc;
				counter++;
			}
			else{
				state = Do_Nothing;
			}
		}
		else if (button2 && !button){
			if (counter > 0x00){
				state = Dec;
				counter--;
			}
			else{
				state = Do_Nothing;
			}
		}
		else if (button && button2){
			state = Reset;
		}
		else{
			state = Do_Nothing;
		}
		break;
		
		case Inc:
		//must have the option to dec from the inc state and vice versa
		if (button && !button2){
				state = Inc;
				if (counter < 0x09){
					counter++;
				}
		}
		else if (!button && !button2){
			state = Do_Nothing;
		}
		else if (!button && button2){
			state = Dec;
			if (counter > 0){
				counter--;
			}
		}
		else if (button && button2){
			state = Reset;
		}
		break;
		
		case Dec:
		if (button2 && !button){
			state = Dec;
			if (counter > 0){
				counter--;
			}
		}
		else if (button && !button2){
			state = Inc;
			if (counter < 0x09){
				counter++;
			}
		}
		else if (button && button2){
			state = Reset;
		}
		else if (!button && !button2){
			state = Do_Nothing;
		}
		break;
		
		case Reset:
		counter = 0x00;
		if (button == 0x03){
			state = Reset;
		}
		else{
			state = Do_Nothing;
		}
		break;
		
		
	}
	
	switch (state){
		default:
			break;
			
		case Init:
			LCD_Cursor(1);
			LCD_WriteData(counter + '0');
			break;
			
		case Inc:
			LCD_Cursor(1);
			LCD_WriteData(counter + '0');
			break;
			
		case Dec:
			LCD_Cursor(1);
			LCD_WriteData(counter + '0');
			break;
			
		case Reset:
			LCD_Cursor(1);
			LCD_WriteData(counter + '0');
			break;
	}
	
}


int main(void)
{
	DDRA = 0x00;
	PORTA = 0xFF;
	
	DDRC = 0xFF; //replace with PORTC
	PORTC = 0x00;
	
	DDRD = 0xFF;
	PORTD = 0x00;
	
	TimerSet(1000);
	TimerOn();
	
	LCD_init();
	LCD_Cursor(1);
	
	state = start;
	/* Replace with your application code */
	while (1)
	{
		Tick();
		while(!TimerFlag){};
			TimerFlag = 0;
	}
}

