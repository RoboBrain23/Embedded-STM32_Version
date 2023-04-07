/*******************************************************************************************/
/* Author      : Ibrahim Diab                                                              */
/* File Name   : OS_interface.h                                                            */
/* Description : Interface file for Simple Operating system to handle the application tasks*/
/*******************************************************************************************/


#ifndef OS_INTERFACE_H
#define OS_INTERFACE_H

/* Create task with specified ID, function pointer, periodicity, and initial delay */
void OS_createTask(uint8 ID, void (*F_PTR)(void), uint16 Periodicity, uint8 FirstDelay);

/* Start the OS Scheduler */
void OS_start(void);

/* Suspend task with specified ID */
void OS_suspendTask(u8 TaskID);

/* Resume task with specified ID */
void OS_resumeTask (u8 TaskID);

/* Delete task with specified ID */
void OS_deleteTask (u8 TaskID);

#endif //OS_INTERFACE_H

