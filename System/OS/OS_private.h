/************************************************************************************************/
/* Author      : Ibrahim Diab                                                                   */
/* File Name   : OS_private.h                                                                   */
/* Description : Private definitions for Simple Operating system to handle the application tasks*/
/************************************************************************************************/

#ifndef OS_PRIVATE_H
#define OS_PRIVATE_H

// Define some constants for task states
#define TASK_READY      0
#define TASK_SUSPEND    1
#define TASK_DELETED    2

// Define a task struct to hold task information
typedef struct
{
    void (*Func_ptr) (void); // A function pointer to the task function
    uint16 Period;           // The period of the task in milliseconds
    uint8  State;            // The current state of the task
    uint8  FirstDelay;       // The initial delay before running the task for the first time
} Task;

// Declare a counter variable for generating task IDs
static volatile uint8 uint8IDCounter = 0;

// Declare an array of tasks
static volatile Task Tasks[NO_TASKS] = { NULL };

// Declare a function to schedule tasks
void schedule();

#endif // OS_PRIVATE_H

