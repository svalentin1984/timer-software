/*
 * timer.c
 *
 * Created: 06.06.2023 08:43:30
 *  Author: valentin.stangaciu
 */ 

#define F_CPU 14745600UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "timer.h"
#include "timer_software.h"

unsigned int n = 0;

ISR(TIMER1_COMPA_vect)
{
	TIMER_SOFTWARE_Task();
}

void TIMER_Init()
{
	OCR1AH = (TIMER_VALUE >> 8) & 0xFF;
	OCR1AL = (TIMER_VALUE & 0xFF);
	TCCR1A = 0;	
	TCCR1B = (1 << WGM12) | (1 << CS11);	
	TIMSK = 1 << OCIE1A;
}
