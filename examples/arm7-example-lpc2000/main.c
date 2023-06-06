#include <lpc22xx.h>
#include "timer.h"
#include "timer_software.h"

void my_timer_callback(timer_software_handler_t handler)
{
	static uint8_t value = 0;
	if (value % 2)
	{
		IO0SET = 1 << 30;
	}
	else
	{
		IO0CLR = (1 << 30);
	}	
	value++;
}

int main(void)
{
	PINSEL1 &= ~(3 << 28);
	PINSEL1 &= ~(3 << 26);
	IO0DIR |= 1 << 30;
	IO0DIR |= 1 << 29;
	TIMER_SOFTWARE_init();
	TIMER_Init();

	uint8_t another_value = 0;
	
	timer_software_handler_t my_timer;
	timer_software_handler_t polling_timer;	

	my_timer = TIMER_SOFTWARE_request_timer();	
	if (my_timer < 0)
	{
		while(1);
	}
	
	polling_timer = TIMER_SOFTWARE_request_timer();	
	if (polling_timer < 0)
	{
		while(1);
	}
	
	if (TIMER_SOFTWARE_configure_timer(my_timer, MODE_1, 100, 1) < 0)
	{
		while(1);
	}
	if (TIMER_SOFTWARE_configure_timer(polling_timer, MODE_1, 1000, 1) < 0)
	{
		while(1);
	}


	TIMER_SOFTWARE_set_callback(my_timer, my_timer_callback);	

	TIMER_SOFTWARE_start_timer(my_timer);
	TIMER_SOFTWARE_start_timer(polling_timer);
	
	while (1)
	{
		if (TIMER_SOFTWARE_interrupt_pending(polling_timer))
		{
			if (another_value % 2)
			{
				IO0SET = 1 << 29;
			}
			else
			{
				IO0CLR = 1 << 29;
			}
			another_value++;			
			TIMER_SOFTWARE_clear_interrupt(polling_timer);
		}	
	}
	return 0;
}

