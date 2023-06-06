#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include "timer_software.h"

static volatile uint8_t running = 0;

void my_timer_callback(timer_software_handler_t handler)
{
  printf ("Timer callback\n");
}

void int_handler(int sig)
{
  running = 0;
}

void *timer_software_task_thread(void *arg)
{
  while (running)
    {
      TIMER_SOFTWARE_ModX();
      usleep(1000);
    }
  return NULL;
}

int main(void)
{
  pthread_t th;
  struct sigaction sgn;
  TIMER_SOFTWARE_init();

  timer_software_handler_t my_timer;
  timer_software_handler_t polling_timer;
  
  memset(&sgn, 0, sizeof(struct sigaction));
  sgn.sa_handler = int_handler;
  if (sigaction(SIGINT, &sgn, NULL) != 0)
    {
      perror(NULL);
      exit(-1);
    }
  running = 1;
  if (pthread_create(&th, NULL, timer_software_task_thread, NULL) != 0)
    {
      perror(NULL);
      exit(-1);
    }

  my_timer = TIMER_SOFTWARE_request_timer();	
  if (my_timer < 0)
    {
      fprintf(stderr, "Error requesting timer\n");
      exit(-2);
    }

  polling_timer = TIMER_SOFTWARE_request_timer();	
  if (polling_timer < 0)
    {
      fprintf(stderr, "Error requesting timer\n");
      exit(-2);
    }
  
  if (TIMER_SOFTWARE_configure_timer(my_timer, MODE_1, 100, 1) < 0)
    {
      fprintf(stderr, "Error configuring timer\n");
      exit(-2);    
    }

  if (TIMER_SOFTWARE_configure_timer(polling_timer, MODE_1, 1000, 1) < 0)
    {
      fprintf(stderr, "Error configuring timer\n");
      exit(-2);    
    }
  
  TIMER_SOFTWARE_set_callback(my_timer, my_timer_callback);	
  
  TIMER_SOFTWARE_start_timer(my_timer);
  TIMER_SOFTWARE_start_timer(polling_timer);
  
  while (running)
    {
      if (TIMER_SOFTWARE_interrupt_pending(polling_timer))
	{
	  printf ("Polling timer\n");
	  TIMER_SOFTWARE_clear_interrupt(polling_timer);
	}      
    }
  
  if (pthread_join(th, NULL) != 0)
    {
      perror(NULL);
      exit(-1);
    }
  
  printf ("Program ended\n");
  return 0;
}
