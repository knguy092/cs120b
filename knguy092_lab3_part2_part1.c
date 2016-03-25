/*Name: Kevin Nguyen, knguy092@ucr.edu
* Partner(s) Name & Email: Jeet Thakkar, jthak002@ucr.edu
* Lab Section:021
* Assignment: Lab #3 Part 2 Exercise #1
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/
#include <avr/io.h>
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

enum States{init, light_one, light_two, light_three} state;

void Tick(){
	switch (state){
		default:
		state = init;
		break;
		
		case init:
		state = light_one;
		break;
		
		case light_one:
		state = light_two;
		break;
		
		case light_two:
		state = light_three;
		break;
		
		case light_three:
		state = light_one;
		break;
		
	}
	
	switch (state){
		default:
		break;
		
		case light_one:
		PORTB = 0x01;
		break;
		
		case light_two:
		PORTB = 0x02;
		break;
		
		case light_three:
		PORTB = 0x04;
		break;
		
		
	}
}

int main(void)
{
	
	DDRB = 0xFF;
	PORTB = 0x00;
	
	TimerSet(1000);
	TimerOn();
	unsigned char tmpB = 0x00;
	
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