#include <lpc22xx.h>
#include <stdint.h>
#include "timer.h"
#include "timer_software.h"

void TIMER_IRQ() __irq
{
	TIMER_SOFTWARE_ModX();
	T1IR = 1;
}

void TIMER_Init()
{
	VICIntEnable |= 0x00000020;
	/*M start timers and enable interrupt*/
	VICIntSelect |= 0x00000020;
	/* M: timer1 match interrupt enable */
	/* M: start timer0 */
	T1PR = 0;
	T1MR0 = 14745;
	T1MCR = 3;
	T1TCR = 0x00000001;	
}
