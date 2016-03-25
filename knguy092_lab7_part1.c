/*Name: Kevin Nguyen, knguy092@ucr.edu
* Partner(s) Name & Email: Jeet Thakkar, jthak002@ucr.edu
* Lab Section:021
* Assignment: Lab #7 Part #1
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/

#include <avr/interrupt.h>
#include "C:\includes\io.c"
#include "C:\includes\io.h"
#include "C:\includes\timer.h"
#include "C:\includes\keypad.h"
#include <avr/io.h>

unsigned char val = 0x1F;

typedef struct Tasks {
	//Task's current state, period, and the time elapsed
	// since the last tick
	signed char state;
	unsigned long int period;
	unsigned long int elapsedTime;
	//Task tick function
	int (*TickFct)(int);
} task;


enum States{init, press} state;
	
int tick(int state){
	
	switch(state){
		default:
			state = init;
			val = 0x1F;
			break;
		
		case init:
			if (val == 0x1F){
				state = init;
			}
			else{
				state = press;
			}
			break;
			
		case press:
			if (val == 0x1F){
				state = init;
			}
			else{
				state = press;
			}
			break;
			
			
		
	}
	
	switch(state){
		case init:
			break;
			
		case press:
			val = GetKeypadKey();
			break;
			
		default:
			val = 0x1F;
			break;
			
		
	}
	
	return state;
}

int main(void)
{
	unsigned char val;
	// PORTB set to output, outputs init 0s
	DDRB = 0xFF; 
	PORTB = 0x00;
	// PC7..4 outputs init 0s, PC3..0 inputs init 1s
	DDRC = 0xF0; 
	PORTC = 0x0F;
	
	static task task1;
	
	task *tasks[] = {&task1};
	
	unsigned long int task_period = 10;
	unsigned long int task_tick = 10;
	const unsigned short numTasks = sizeof(task)/sizeof(task*);
	
	
	
	task1.state = -1;
	task1.period = task_period;
	task1.elapsedTime = task_tick;
	task1.TickFct = &tick;
	
	TimerSet(task_tick);
	TimerOn();
    
    while (1) 
    {
		
		
		// Scheduler code
		for (unsigned short i = 0; i < numTasks; i++ ) {
			// Task is ready to tick
			if ( tasks[i]->elapsedTime == tasks[i]->period ) {
				// Setting next state for task
				tasks[i]->state =
				tasks[i]->TickFct(tasks[i]->state);
				// Reset elapsed time for next tick.
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += 1;
		}
		
			val = GetKeypadKey();
			switch (val) {
				// All 5 LEDs on
				case '\0': PORTB = 0x1F; break;
				// hex equivalent
				case '1': PORTB = 0x01; break;
				case '2': PORTB = 0x02; break;
				case '3': PORTB = 0x03; break;
				case '4': PORTB = 0x04; break;
				case '5': PORTB = 0x05; break;
				case '6': PORTB = 0x06; break;
				case '7': PORTB = 0x07; break;
				case '8': PORTB = 0x08; break;
				case '9': PORTB = 0x09; break;
				// . . . ***** FINISH *****
				case 'A': PORTB = 0x0A; break;
				case 'B': PORTB = 0x0B; break;
				case 'C': PORTB = 0x0C; break;
				case 'D': PORTB = 0x0D; break;
				case '*': PORTB = 0x0E; break;
				case '0': PORTB = 0x00; break;
				case '#': PORTB = 0x0F; break;
				// Should never occur. Middle LED off.
				default: PORTB = 0x1B; break;
			
		}
    }
}

