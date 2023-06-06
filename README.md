TIMER SOFTWARE
==============

This project implements a software timer library in order to be used especially in embedded systems. Timings in embedded systems are usually implemented using hardware timers available in most microcontrollers. However, the number of hardware timers is usually limited and in small numbers which may limit the complexity of applications or may unnecessarily complicate the code. 

This library provides a software solution to this problem. The user may define as many software timers as it needs with the memory being the only expense. The user may use and reuse each timer independently and it may adjust the maximum space reserved for all the timers. 

The code is written in C and documentated using Doxygen. 

TIMER SOFTWARE Usage Description
--------------------------

This software timer implementation needs a base timing which may be insured either by a hardware timer or by a thread/task/process implementation of an operating system. The software timer requires that its main task function is called with a strict period of 1 ms. The timer software's main task function is represented by the following function:

`void TIMER_SOFTWARE_Task()`

This function must be called periodically each millisecond. Before calling this function, the user must first initialize the library by calling 

```C
void TIMER_SOFTWARE_Init()
```

Examples
========


Example 1
---------


Example 2
---------


Example 3
---------
