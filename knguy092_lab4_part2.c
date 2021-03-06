/*Name: Kevin Nguyen, knguy092@ucr.edu
* Partner(s) Name & Email: Jeet Thakkar, jthak002@ucr.edu
* Lab Section:021
* Assignment: Lab #4 Part 2
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "C:/includes/io.c"

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

enum States{init, light_one, light_two, light_three, light_two_back, stop, wait_begin} state;
unsigned char temp;
unsigned char counter = 5;
unsigned char inc_once = 1;

void Tick(){
	unsigned char button = (~PINA) & 0x01;
	switch (state){
		default:
		state = init;
		break;
		
		case init:
		if (counter == 9){
			LCD_ClearScreen();
			counter = 5;
		}
		LCD_Cursor(1);
		LCD_WriteData(counter + '0');
		state = light_one;
		//insert LCD display here
		break;
		
		case light_one:
		if (button == 0x01){
			state = stop;
			if (counter > 0){
				counter--;
				LCD_Cursor(1);
				LCD_WriteData(counter + '0');
			}
		}
		else{
			state = light_two;
		}
		break;
		
		case light_two:
		if (button == 0x01){
			state = stop;
			if (counter < 9){
				counter++;
				LCD_Cursor(1);
				LCD_WriteData(counter + '0');
			}
			if (counter == 9){
				LCD_DisplayString(1, "YAY YOU WON!");
			}
		}
		else{
			state = light_three;
		}
		break;
		
		case light_three:
		if (button == 0x01){
			state = stop;
			if (counter > 0){
				counter--;
				LCD_Cursor(1);
				LCD_WriteData(counter + '0');
			}
		}
		else{
			state = light_two_back;
		}
		break;
		
		case light_two_back:
		if (button == 0x01){
			state = stop;
			if (counter < 9){
				counter++;
				LCD_Cursor(1);
				LCD_WriteData(counter + '0');
			}
			if (counter == 9){
				LCD_DisplayString(1, "YAY YOU WON!");
			}
		}
		else{
			state = light_one;
		}
		break;
		
		case stop:
		if (button == 0x01){
			state = stop;
		}
		else{
			state = wait_begin;
		}
		break;
		
		case wait_begin:
		inc_once = 1;
		if (button == 0x00){
			state = wait_begin;
		}
		else{
			state = init;
		}
		break;
		
	}
	
	switch (state){
		case init:
			LCD_Cursor(1);
			LCD_WriteData(counter + '0');
			break;
		
		case light_one:
		temp = 0x01;
		break;
		
		case light_two:
		temp = 0x02;
		break;
		
		case light_three:
		temp = 0x04;
		break;
		
		case light_two_back:
		temp = 0x02;
		break;
		
		case stop:
			break;
			
		case wait_begin:
			break;
		
	}
	PORTB = temp;
}

int main(void)
{
	DDRA = 0x00;
	PORTA = 0xFF;
	
	DDRC = 0xFF;
	PORTC = 0x00;
	
	DDRD = 0xFF;
	PORTD = 0x00;
	
	TimerSet(300);
	TimerOn();
	unsigned char tmpB = 0x00;
	
	LCD_init();
	LCD_Cursor(1);
	
	state = init;

	while(1)
	{
		//TODO:: Please write your application code
		tmpB = ~tmpB;
		PORTB = tmpB & 0x07;
		Tick();
		
		while(!TimerFlag);
		TimerFlag = 0;
	}
}