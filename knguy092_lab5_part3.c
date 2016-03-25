/*Name: Kevin Nguyen, knguy092@ucr.edu
* Partner(s) Name & Email: Jeet Thakkar, jthak002@ucr.edu
* Lab Section:021
* Assignment: Lab #5 Part #3
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

unsigned char temp = 0x00;
unsigned char temp2 = 0x00;
unsigned char speak = 0x00;

enum speak_states{speak_on, speak_off} speaker_state;

void Speaker(){
	unsigned char button = (~PINA) & 0x04;
	switch(speaker_state){
		default:
		speaker_state = speak_off;
		break;
		
		case speak_off:
		if (button){
			speaker_state = speak_on;
		}
		else{
			speaker_state = speak_off;
		}
		break;
		
		case speak_on:
		speaker_state = speak_off;
		break;
	}
	
	switch(speaker_state){
		default:
		break;
		
		case speak_on:
		speak = 0x10;
		break;
		
		case speak_off:
		speak = 0x00;
		break;
	}

	
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
		temp = 0x01;
		break;
		
		case light_two:
		temp = 0x02;
		break;
		
		case light_three:
		temp = 0x04;
		break;
		
		
	}
}

enum States_2 {start, on , off} state_2;

void Tick_2(){
	switch(state_2){
		default:
		state_2 = start;
		break;
		
		case init:
		state_2 = on;
		break;
		
		case on:
		state_2 = off;
		break;
		
		case off:
		state_2 = on;
		break;
		
	}
	
	switch(state_2){
		default:
		break;
		
		case start:
		break;
		
		case on:
		temp2 = 0x08;
		break;
		
		case off:
		temp2 = 0x00;
		break;
	}
}

enum Repeat{begin} repeat;

void repeat_states(){
	switch(repeat){
		default:
		repeat = begin;
		break;
		
		case begin:
		repeat = begin;
		break;
		
	}
	
	switch(repeat){
		case begin:
		PORTB = temp | temp2 | speak;
	}
	
}

int main(void)
{
	DDRA = 0x00;
	PORTA = 0xFF;
	
	DDRB = 0xFF;
	PORTB = 0x00;
	
	TimerSet(2);
	TimerOn();
	//unsigned char tmpB = 0x00;
	
	state = init;
	state_2 = start;
	speaker_state = speak_off;
	
	unsigned char count1 = 0;
	unsigned char count2 = 0;

	while(1)
	{
		//TODO:: Please write your application code
		//tmpB = ~tmpB;
		//PORTB = tmpB & 0x0F;
		count1++;
		count2++;
		
		
		if (count1 == 150){
			Tick();
			count1 = 0;
		}
		
		if (count2 == 500){
			Tick_2();
			count2 = 0;
		}
		repeat_states();
		Speaker();
		
		while(!TimerFlag);
		TimerFlag = 0;
	}
}