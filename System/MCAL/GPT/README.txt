-The advanced-control timers (TIM1 and TIM8) consist of a 16-bit auto-reload counter driven
by a programmable prescaler.

use for:
measuring the pulse lengths of input signals (input capture) or 
generating output waveforms (output compare, PWM,complementary PWM with dead-time insertion).

/***************************************features**************************************/
16-bit up, down, up/down auto-reload counter.
• 16-bit programmable prescaler allowing dividing (also “on the fly”) the counter clock
frequency either by any factor between 1 and 65536.
• Up to 4 independent channels for:
– Input Capture
– Output Compare
– PWM generation (Edge and Center-aligned Mode)
– One-pulse mode output
• Complementary outputs with programmable dead-time
• Synchronization circuit to control the timer with external signals and to interconnect
several timers together.
• Repetition counter to update the timer registers only after a given number of cycles of
the counter.
• Break input to put the timer’s output signals in reset state or in a known state.
• Interrupt/DMA generation on the following events:
– Update: counter overflow/underflow, counter initialization (by software or
internal/external trigger)
– Trigger event (counter start, stop, initialization or count by internal/external trigger)
– Input capture
– Output compare
– Break input
• Supports incremental (quadrature) encoder and hall-sensor circuitry for positioning
purposes
• Trigger input for external clock or cycle-by-cycle current management






The time-base unit includes:
• Counter register (TIMx_CNT)
• Prescaler register (TIMx_PSC)
• Auto-reload register (TIMx_ARR)
• Repetition counter register (TIMx_RCR)



/***************************counter mode****************************/
--->>>uncounting mode
In upcounting mode, the counter counts from 0 to the auto-reload value (content of the
TIMx_ARR register), then restarts from 0 and generates a counter overflow event.
 --->>>Downcounting mode
In downcounting mode, the counter counts from the auto-reload value (content of the
TIMx_ARR register) down to 0, then restarts from the auto-reload value and generates a counter underflow event.
 --->>>Center-aligned mode (up/down counting)
In center-aligned mode, the counter counts from 0 to the auto-reload value (content of the
TIMx_ARR register) – 1, generates a counter overflow event, then counts from the autoreload
value down to 1 and generates a counter underflow event. Then it restarts counting
from 0.



/*******************Registers*********************************/
CR1 - Timer Control Register 1

This register controls the general behavior of the timer.
Relevant bits for advanced timers include:
ARPE: Auto-reload preload enable bit
CEN: Counter enable bit


CR2 - Timer Control Register 2

This register is used to configure external trigger inputs for the timer.
Relevant bits for advanced timers include:
MMS: Master mode selection bits


SMCR - Slave Mode Control Register

This register is used to configure the timer's behavior as a slave in a multi-timer synchronization scheme.
Relevant bits for advanced timers include:
SMS: Slave mode selection bits
TS: Trigger selection bits


DIER - DMA/Interrupt Enable Register

This register is used to enable or disable timer interrupts and DMA requests.
Relevant bits for advanced timers include:
UDE: Update DMA request enable bit
UIE: Update interrupt enable bit


SR - Status Register

This register contains status flags indicating the current state of the timer.
Relevant bits for advanced timers include:
UIF: Update interrupt flag
UG: Update generation bit


EGR - Event Generation Register

This register is used to generate events manually.
Relevant bits for advanced timers include:
UG: Update generation bit


CCMR1 and CCMR2 - Capture/Compare Mode Registers 1 and 2

These registers are used to configure the capture/compare channels of the timer.
Relevant bits for advanced timers include:
OCxM: Output compare mode bits
OCxPE: Output compare preload enable bit
ICxPSC: Input capture prescaler bits
ICxF: Input capture filter bits



CCER - Capture/Compare Enable Register

This register is used to enable or disable the capture/compare channels of the timer.
Relevant bits for advanced timers include:
CCxE: Capture/compare enable bit
CCxP: Capture/compare polarity bit


CNT - Counter Register

This register holds the current value of the timer counter.


PSC - Prescaler Register

This register sets the value of the prescaler
/*********************functions**************************/
Timer Initialization:
This function initializes the timer by setting its clock source, prescaler, and period. The prescaler determines how fast the timer clock runs, while the period sets the length of time for which the timer will count before it overflows.

Timer Interrupt Initialization:
This function initializes the interrupt for the timer. You can specify the interrupt priority and enable or disable the interrupt.

Start Timer:
This function starts the timer by enabling the timer clock and setting the timer enable bit.

Stop Timer:
This function stops the timer by disabling the timer clock and clearing the timer enable bit.

Read Timer Value:
This function reads the current value of the timer.

Reset Timer:
This function resets the timer by setting the timer value to 0.

Capture Mode Initialization:
This function initializes the timer in capture mode,
 which allows you to capture the value of an external signal at a specific moment in time. 
 You can specify the capture edge (rising, falling, or both) and enable or disable the capture 
 interrupt.

PWM Mode Initialization:
This function initializes the timer in PWM mode,
 which allows you to generate a pulse-width modulated signal.
 You can specify the pulse width and period of the PWM signal.

Input Capture Handling:
This function handles the input capture interrupt by reading the captured value and 
performing any necessary processing.

Output Compare Handling:
This function handles the output compare interrupt by performing any necessary 
processing when the timer matches a specific value.