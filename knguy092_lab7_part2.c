/*Name: Kevin Nguyen, knguy092@ucr.edu
* Partner(s) Name & Email: Jeet Thakkar, jthak002@ucr.edu
* Lab Section:021
* Assignment: Lab #7 Part #2
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

char* str = "C120b is Legend... wait for it DARY! ";
unsigned char count = 0;
unsigned char screen[16];

typedef struct Tasks {
	//Task's current state, period, and the time elapsed
	// since the last tick
	signed char state;
	unsigned long int period;
	unsigned long int elapsedTime;
	//Task tick function
	int (*TickFct)(int);
} task;


enum States{init} state;
	
int tick(state){
		
			for (unsigned int j = 0; j < 16; j++){
				screen[j] = str[(count + j) % 38];
			}
			count = (count + 1) % 38;
			LCD_DisplayString(1, screen);
			state = init;
			
			
	
	
	return state;
}



int main(void)
{
	// PORTB set to output, outputs init 0s
	DDRD = 0xFF;
	PORTD = 0x00;
	// PC7..4 outputs init 0s, PC3..0 inputs init 1s
	DDRA = 0xFF;
	PORTA = 0x00;
	
	static task task1;
	
	task *tasks[] = {&task1};
	
	unsigned long int task_period = 35;
	unsigned long int task_tick = 35;
	const unsigned short numTasks = sizeof(task)/sizeof(task*);
	
	
	
	task1.state = -1;
	task1.period = task_period;
	task1.elapsedTime = task_tick;
	task1.TickFct = &tick;
	
	TimerSet(task_tick);
	TimerOn();
	LCD_init();
	
	while (1)
	{
		
		
		// Scheduler code
		for (unsigned short i = 0; i < numTasks; i++ ) {
			// Task is ready to tick
			if ( tasks[i]->elapsedTime == tasks[i]->period ) {
				// Setting next state for task
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				// Reset elapsed time for next tick.
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += 1;
		}
		while(!TimerFlag){};
		TimerFlag = 0;
		
		
	}
}

