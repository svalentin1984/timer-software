TIMER SOFTWARE
==============

This project implements a software timer library in order to be used especially in embedded systems. Timings in embedded systems are usually implemented using hardware timers available in most microcontrollers. However, the number of hardware timers is usually limited and in small numbers which may limit the complexity of applications or may unnecessarily complicate the code. 

This library provides a software solution to this problem. The user may define as many software timers as it needs with the memory being the only expense. The user may use and reuse each timer independently and it may adjust the maximum space reserved for all the timers. 

The code is written in C and documentated using Doxygen. 

TIMER SOFTWARE Usage Description
--------------------------

This software timer implementation needs a base timing which may be insured either by a hardware timer or by a thread/task/process implementation of an operating system. The software timer requires that its main task function is called with a strict period of 1 ms. The timer software's main task function is represented by the following function:

```C
void TIMER_SOFTWARE_Task();
```

This function must be called periodically each millisecond. 

Before calling the above function, the user must first initialize the library by calling:

```C
void TIMER_SOFTWARE_Init();
```

The initialization function above must be called only once, prior to any other calls from this library. 

There are no special options for compiling this library. Before compilation the use may adjust the maximum number of supported timers be changing the *MAX_NR_TIMERS* macro in *timer_software.h* file.

In order to use a time, the programmer must define a variable of type *timer_software_handler_t* which will hold a unique identifier of the timer. The programmer must assign this variable with the value returned by the function *TIMER_SOFTWARE_request_timer*. In other word, before using a timer, it must be requested to the library. After the request, the returned handler will uniquely identify the timer within the library.

After a timer has been requested, the user must configure the timer by calling *TIMER_SOFTWARE_configure_timer*. The user must specify the timer through the handler along with the period, operating mode and a flag that should enable the timer. 

The programmer may then use the timer through the functions provided by the library according to the doxygen documentation.

Each timer has 4 operating modes:

  * **MODE_0** - The software timer counts to the value given by period. When the counter is equal to the value of the period, the timer stops and generates an event.
  * **MODE_1** - The software timer counts to the value given by period. When the counter is equal to the value of the period, the timer generates an event, resets the counter and restarts
  * **MODE_2** - The software timer counts to the value given by period. When the counter is equal to the value of the peiod, the timer generates an event and continues running
  * **MODE_3** - This operating mode is free run mode. THe counter just starts from 0 and keeps counting without generating any evenys.

The programmer may use this timer with event generation via a callback system or
using polling methods via dedicated methods for checking pending events. Before using a timer, the programmers needs to acquire such a timer by calling TIMER_SOFTWARE_request_timer which returns a descriptor for the newly allocated timer. A timer may be released after the programmer finishes using it, by calling TIMER_SOFTWARE_release_timer. After a timer has been acquired by the programmer it has to be configured by specifying its operating mode and its counting period.

The library also offers a simple wait function which blocks the code execution for an
amount of time given as argument. It may be used for delay generation.

Generic Examples
================

In this sections we will present 2 usages examples: one for using a timer in a polling method and one using callbacks. In both cases, we only show the actual usage of the library. We presume that the rest of the preparations are made (the task function is called with a period of 1 ms)

Example using callbacks
-----------------------

This example describes a simple usage of a software timer with event generation via callbacks:

```C
#include "timer_software.h"

void mycallback(timer_software_handler_t handler)
{
    // code to be executed on event
}

void main(void)
{
    // some code
    TIMER_SOFTWARE_init();
    // some code
    timer_software_handler_t handler;           // declare a sotware timer
    handler = TIMER_SOFTWARE_request_timer();   // request a software timer
    if (handler < 0)                            // check if the request was successful
    {
        // error
        // the system could not offer a software timer
    }
    //configure the software timer to run in MODE_1 (reset and restart on match) with a period of 1 second (1000 ms)
    TIMER_SOFTWARE_configure_timer(handler, MODE_1, 1000, true);
    // set a callback for the requested timer
    TIMER_SOFTWARE_set_callback(handler, mycallback);
    TIMER_SOFTWARE_start_timer(handler);
    while(1)
    {
        // some code
    }
    // some code
}
```

Examples
========

Several examples are given in the /examples directory of this repo. 


Example 1
---------


Example 2
---------


Example 3
---------
