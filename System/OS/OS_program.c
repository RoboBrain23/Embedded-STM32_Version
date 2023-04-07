/*****************************************************************************************************/
/* Author      : Ibrahim Diab                                                                        */
/* File Name   : OS_program.c                                                                        */
/* Description : Functions Implementation for Simple Operating system to handle the application tasks*/
/*****************************************************************************************************/

#include "std_types.h"
#include "common_macros.h"

#include "STK_interface.h"

#include "OS_interface.h"s
#include "OS_config.h"
#include "OS_private.h"

void OS_createTask(uint8 ID, void (*F_PTR)(void), uint16 Periodicity, uint8 FirstDelay)
{
    if(uint8IDCounter < NO_TASKS)
    {
        // Set the task's function pointer to the given function pointer
        Tasks[ID].Func_ptr   = F_PTR;
        // Set the task's period to the given periodicity
        Tasks[ID].Period     = Periodicity;
        // Set the task's initial delay to the given first delay
        Tasks[ID].FirstDelay = FirstDelay;
        // Set the task's state to "ready" to add it to the scheduler's task list
        Tasks[ID].State      = TASK_READY;
    }
    else
    {
        // Handle the error where the number of tasks has exceeded the maximum
    }
}

void OS_start(void)
{
    // Initialize the system timer
    STK_init();
    // Set up the system timer to call the scheduler function periodically
    STK_setIntervalPeriodic ( TASKS_PERIOD_IN_MICRO_SEC, schedule );
}

void schedule()
{
    for(uint8 currentIndex =0 ; currentIndex < NO_TASKS ; currentIndex++)
    {
        // Check if the task is ready to run and has a valid function pointer
        if(Tasks[currentIndex].State == TASK_READY && Tasks[currentIndex].Func_ptr != NULL)
        {
            // Check if the task's initial delay has expired
            if(Tasks[currentIndex].FirstDelay == 0)
            {
                // Call the task's function
                Tasks[currentIndex].Func_ptr();
                // Reset the task's initial delay to its period
                Tasks[currentIndex].FirstDelay = Tasks[currentIndex].Period-1;
            }
            else
            {
                // Decrement the task's initial delay
                Tasks[currentIndex].FirstDelay--;
            }
        }
    }
}

void OS_suspendTask(uint8 TaskID)
{
    // Set the task's state to suspended
    Tasks[TaskID].State = TASK_SUSPEND;
}

void OS_voidResumeTask(u8 TaskID)
{
    // Set the task's state to ready
    Tasks[TaskID].State = TASK_READY;
}

void OS_deleteTask(u8 TaskID)
{
    // Set the task's state to deleted
    Tasks [TaskID].State      = TASK_DELETED;
    // Set the task's function pointer to NULL
    Tasks [TaskID].Func_ptr = NULL;
}
