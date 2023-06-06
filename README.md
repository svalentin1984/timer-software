TIMER SOFTWARE
==============

This project implements a software timer library in order to be used especially in embedded systems. Timings in embedded systems are usually implemented using hardware timers available in most microcontroller. However, the number of hardware timers is usually limited and which may limit the complexity of applications. This library provides a software solution to this problem. The user may define as many software timers as it needs with the memory being the only expense. 

TIMER SOFTWARE Description
--------------------------

This software timer implementation needs a base timing which may be insured either by a hardware timer or by a thread/task/process implementation of an operating system. The software timer requires that its main task function to be called with a strict period of 1 ms. The timer software's main task function is represented by

`void TIMER_SOFTWARE_Task()`


my Description
asdasdasd

Examples
========


Example 1
---------


Example 2
---------


Example 3
---------
