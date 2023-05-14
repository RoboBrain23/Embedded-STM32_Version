			 
 /**********************************************************************************/
/* Author	: Hind Fouad                                                          */
/* date		:19 Mar 2022                                                          */
/* Version	: V01                                                                 */
/**********************************************************************************/

/**************includes***************/
#include "std_types.h"
#include "common_macros.h"
#include "RCC_interface.h"
#include "GPT_interface.h"
#include "GPT_private.h"
#include "GPT_config.h"


/****************Functions***********/

/************************************************************************************************************* */
/*Static global variables*/
/************************************************************************************************************* */
/* Variable to define interval mode of Timer*/
static volatile uint8 TIM_IntervalMode;


/************************************************************************************************************* */
/* Local macros to set and get Interval mode for timer interrupt*/
#define TIM_SET_INTERVAL_MODE(MODE)                          TIM_IntervalMode = MODE
#define TIM_GET_INTERVAL_MODE()                               (TIM_IntervalMode & 1)
/************************************************************************************************************* */

static void (*Timer_CallBack)(void);
/************************************************************************************************************* */
void Tim_init(TIM_t * TIMx, TIM_ConfigType * config){
   
     /*call functions*/
  Tim_stopTimer( TIMx);
  Tim_setPrescaler(TIMx , config -> Prescaler);
  Tim_setPeriod (TIMx , config -> Period);
    
    /* Set the update event as the interrupt source*/
    TIMx->DIER |= TIM_DIER_UIE;
	/* enable the timer interrupt in the NVIC*/
  //NVIC_EnableIRQ(TIMx_IRQn);
  Tim_setClockSource(TIMx, config -> CLK_SRC );
  Tim_setClkDiv(TIMx,config ->ClockFactor );
  Tim_setCounterMode(TIMx,config -> CounterMode);
  Tim_set_Interrupt(TIMx,config -> State);
  Tim_startTimer( TIMx);



}
void Tim_stopTimer(TIM_t * TIMx){
	
	CLR_BIT(TIMx ->CR1 ,CEN);
}
void Tim_startTimer(TIM_t* TIMx){
	SET_BIT(TIMx->CR1,CEN);
}
void Tim_setPrescaler(TIM_t * TIMx , uint32 prescaler){
	  /*Set the pre scaler value in PSC register*/
    TIMx ->PSC =  prescaler;
	
	
}
void Tim_setPeriod (TIM_t * TIMx , uint32 period){
	/* Set the auto reload value value in ARP register*/
    TIMx->ARR = period;
}
void Tim_setClockSource(TIM_t *TIMx, timer_clk_src_t CLK_SRC) {
	switch (CLK_SRC){
  
	  case TIMER_CLK_SRC_INTERNAL:
      // Configure timer clock source to internal oscillator
	  /*SMS bits */
	  CLR_BIT (TIMx -> SMCR ,0);
	  CLR_BIT (TIMx -> SMCR ,1);
	  CLR_BIT (TIMx -> SMCR ,2);
      /*clear MMS bits*/
	  CLR_BIT (TIMx -> CR2,4);
	  CLR_BIT (TIMx -> CR2,5);
	  CLR_BIT (TIMx -> CR2,6);
    
	  SET_BIT ( TIMx -> EGR , UG);
      
      break;

    case TIMER_CLK_SRC_EXTERNAL_MODE1:
      // Configure timer clock source to external clock mode 1
      /*SMS bits */
	  SET_BIT (TIMx -> SMCR ,0);
	  SET_BIT (TIMx -> SMCR ,1);
	  SET_BIT (TIMx -> SMCR ,2);
      /*clear MMS bits*/
	  CLR_BIT (TIMx -> CR2,4);
	  CLR_BIT (TIMx -> CR2,5);
	  CLR_BIT (TIMx -> CR2,6);
      SET_BIT (TIMx -> EGR , UG);
      break;

    case TIMER_CLK_SRC_EXTERNAL_MODE2:
      // Configure timer clock source to external clock mode 2
      CLR_BIT (TIMx -> SMCR ,0);
	  CLR_BIT (TIMx -> SMCR ,1);
	  SET_BIT (TIMx -> SMCR ,2);
     
      /*clear MMS bits*/
	  CLR_BIT (TIMx -> CR2,4);
	  CLR_BIT (TIMx -> CR2,5);
	  SET_BIT (TIMx -> CR2,6);
      
      SET_BIT (TIMx -> EGR , UG);
      break;

    default:
      // Invalid clock source specified
      return;
	  
	  
  }
	
	
}
void Tim_setCounterMode(TIM_t *TIMx,counter_m counterMode){
	switch (counterMode){
  case Up_Counting:
  /*set direction of counter: up */
      CLR_BIT(TIMx -> CR1 ,DIR );

	  break;
  case Down_Counting :
    /*set direction of counter: up */
      SET_BIT (TIMx -> CR1 ,DIR);
	 
	  break;
  case Center_Aligned:
      CLR_BIT ( TIMx -> CR1 , DIR);
	  SET_BIT (TIMx -> CR1 ,6);
	  CLR_BIT (TIMx -> CR1 ,5);
     break;
	  default:
	  break;
	  
  
    
}
}
void TIM_voidReptitionCounter(TIM_t * TIMx,uint32 count ){
	/*Auto-reload pre load enable*/
	SET_BIT (TIMx -> CR1 , ARPE);
	/*save count number in repetition counter register*/
	TIMx ->RCR = count;

}
void Tim_setClkDiv(TIM_t *TIMx,Clk_Div clockDiv)
{
	switch(clockDiv)
	{
	case Div_1:
		CLR_BIT(TIMx->CR1,8);
		CLR_BIT(TIMx->CR1,9);
		break;

	case Div_2:
		SET_BIT(TIMx->CR1,8);
		CLR_BIT(TIMx->CR1,9);
		break;

	case Div_3:
		CLR_BIT(TIMx->CR1,8);
		SET_BIT(TIMx->CR1,9);
		break;

	default:
		break;
	}
}


/*********Modes ( input capture|PEM input|forced output| output compare********/
void Tim_setInputCaptureMode(TIM_t* TIMx, channel_t Channel, uint32 filterDuration,edge_t Edge)
{
	uint32 Local_uint32Prescaler = TIMx -> PSC;
	
	/*select the channel*/
	if (Channel == TIM_Channel1 )
	{
		
	/*1-  write 01 to cc1s bits in CCMR register*/
	SET_BIT (TIMx -> CCMR1 ,0) ;
	CLR_BIT (TIMx -> CCMR1 ,1);
	 /*2-set input filter */
	CLR_BIT (TIMx -> CCMR1 , IC1F);
    TIMx->CCMR1 |= (filterDuration << IC1F);  // Set IC1F bits
	/*3- select edge*/
	    if (Edge == RISING ){
			 CLR_BIT (TIMx -> CCER, CC1P);
		}else if (Edge == FALLING)
		{
			SET_BIT (TIMx -> CCER, CC1P);
		}
		/*4- enable register*/
		SET_BIT (TIMx -> CCER ,CC1E);
	
	}else if (Channel == TIM_Channel2){
		/*1-  write 01 to cc2s bits in CCMR register*/
	SET_BIT (TIMx -> CCMR1 ,8) ;
	CLR_BIT (TIMx -> CCMR1 ,9);
	  /*2-  set input filter */
	CLR_BIT (TIMx -> CCMR1 , IC2F);
    TIMx->CCMR1 |= (filterDuration << IC2F);  // Set IC2F bits
	/*3- select edge*/
	   if (Edge == RISING ){
			 CLR_BIT (TIMx -> CCER, CC2P);
		}else if (Edge == FALLING)
		{
			SET_BIT (TIMx -> CCER, CC2P);
		}
		/*4- enable register*/
		SET_BIT (TIMx -> CCER ,CC2E);
	
	}else if (Channel == TIM_Channel3){
		/*1-  write 01 to cc3s bits in CCMR2 register*/
	SET_BIT (TIMx -> CCMR2 ,0) ;
	CLR_BIT (TIMx -> CCMR2 ,1);
	  /*2- set input filter */
	CLR_BIT (TIMx -> CCMR2 , IC3F);
    TIMx->CCMR2 |= (filterDuration << IC3F);  // Set IC1F bits
	/*3- select edge*/
	 if (Edge == RISING ){
			 CLR_BIT (TIMx -> CCER, CC3P);
		}else if (Edge == FALLING)
		{
			SET_BIT (TIMx -> CCER, CC3P);
		}
		/*4- enable register*/
		SET_BIT (TIMx -> CCER ,CC3E);
	
	}else if (Channel == TIM_Channel4){
		/*1-  write 01 to cc4s bits in CCMR2 register*/
	SET_BIT (TIMx -> CCMR2 ,8) ;
	CLR_BIT (TIMx -> CCMR2 ,9);
	 /*2- set input filter */
	CLR_BIT (TIMx -> CCMR2 , IC4F);
    TIMx->CCMR2 |= (filterDuration << IC4F);  // Set IC1F bits
	/*3- select edge*/
	 if (Edge == RISING ){
			 CLR_BIT (TIMx -> CCER, CC4P);
		}else if (Edge == FALLING)
		{
			SET_BIT (TIMx -> CCER, CC4P);
		}
		/*4- enable register*/
		SET_BIT (TIMx -> CCER ,CC4E);
	
	}

	
	
	
	
}

void Tim_setPWMInputMode(TIM_t* TIMx, channel_t Channel,edge_t Edge){
	if (Channel== TIM_Channel1){
	
	
		SET_BIT (TIMx -> CCMR1 ,0);
		CLR_BIT (TIMx -> CCMR1 ,1);
		 if (Edge == RISING ){
			 CLR_BIT (TIMx -> CCER, CC1P);
		}else if (Edge == FALLING)
		{
			SET_BIT (TIMx -> CCER, CC1P);
		}
		
	}else if (Channel == TIM_Channel2){
	
		SET_BIT (TIMx -> CCMR1 ,9);
		CLR_BIT (TIMx -> CCMR1 ,8);
		 if (Edge == RISING ){
			 CLR_BIT (TIMx -> CCER, CC2P);
		}else if (Edge == FALLING)
		{
			SET_BIT (TIMx -> CCER, CC2P);
		}
	}else if (Channel == TIM_Channel3){
		
		SET_BIT (TIMx -> CCMR2 ,0);
		CLR_BIT (TIMx -> CCMR2 ,1);
		 if (Edge == RISING ){
			 CLR_BIT (TIMx -> CCER, CC3P);
		}else if (Edge == FALLING)
		{
			SET_BIT (TIMx -> CCER, CC3P);
		}
	}else if (Channel == TIM_Channel4){
	
		SET_BIT (TIMx -> CCMR1 ,9);
		CLR_BIT (TIMx -> CCMR1 ,8);
		 if (Edge == RISING ){
			 CLR_BIT (TIMx -> CCER, CC4P);
		}else if (Edge == FALLING)
		{
			SET_BIT (TIMx -> CCER, CC4P);
		}
		
	}
	/*Filtered Timer Input 1 (TI1FP1)*/
	SET_BIT(TIMx -> SMCR,4);
	CLR_BIT(TIMx -> SMCR,5);
	SET_BIT(TIMx -> SMCR,6);
	/*Reset Mode - Rising edge of the selected trigger input (TRGI) reinitializes the counter
and generates an update of the registers.*/
	CLR_BIT(TIMx -> SMCR,0);
	CLR_BIT(TIMx -> SMCR,1);
	SET_BIT(TIMx -> SMCR,2);
	/*Capture enabled.*/
	SET_BIT (TIMx -> CCER ,CC1E);
	SET_BIT (TIMx -> CCER ,CC2E);
}

void Tim_setForcedoutputMode(TIM_t *TIMx, channel_t Channel,edge_t Edge){
	if (Channel == TIM_Channel1){
		/*CC1 channel is configured as output*/
		CLR_BIT(TIMx -> CCMR1 , 0);
		CLR_BIT(TIMx -> CCMR1 , 0);
		if (Edge == RISING){
			SET_BIT (TIMx -> CCMR1 ,4);
			CLR_BIT (TIMx -> CCMR1 ,5);
			SET_BIT (TIMx -> CCMR1 ,6);
			
		}else if (Edge == FALLING){
			CLR_BIT (TIMx -> CCMR1 ,4);
			CLR_BIT (TIMx -> CCMR1 ,5);
			SET_BIT (TIMx -> CCMR1 ,6);
		}
	}else if   (Channel == TIM_Channel2){
		/*CC2 channel is configured as output*/
		CLR_BIT(TIMx -> CCMR1 , 8);
		CLR_BIT(TIMx -> CCMR1 , 9);
		if (Edge == RISING){
			SET_BIT (TIMx -> CCMR1 ,12);
			CLR_BIT (TIMx -> CCMR1 ,13);
			SET_BIT (TIMx -> CCMR1 ,14);
			
		}else if (Edge == FALLING){
			CLR_BIT (TIMx -> CCMR1 ,12);
			CLR_BIT (TIMx -> CCMR1 ,13);
			SET_BIT (TIMx -> CCMR1 ,14);
		}
	}else if   (Channel ==TIM_Channel3){
		/*CC3 channel is configured as output*/
		CLR_BIT(TIMx -> CCMR2 , 0);
		CLR_BIT(TIMx -> CCMR2 , 1);
		if (Edge == RISING){
			SET_BIT (TIMx -> CCMR2 ,4);
			CLR_BIT (TIMx -> CCMR2 ,5);
			SET_BIT (TIMx -> CCMR2 ,6);
			
		}else if (Edge == FALLING){
			CLR_BIT (TIMx -> CCMR2 ,4);
			CLR_BIT (TIMx -> CCMR2 ,5);
			SET_BIT (TIMx -> CCMR2 ,6);
		}
	}else if   (Channel ==TIM_Channel4){
		/*CC4 channel is configured as output*/
		CLR_BIT(TIMx -> CCMR2 , 8);
		CLR_BIT(TIMx -> CCMR2 , 9);
		if (Edge == RISING){
			SET_BIT (TIMx -> CCMR2 ,12);
			CLR_BIT (TIMx -> CCMR2 ,13);
			SET_BIT (TIMx -> CCMR2 ,14);
			
		}else if (Edge == FALLING){
			CLR_BIT (TIMx -> CCMR2 ,12);
			CLR_BIT (TIMx -> CCMR2 ,13);
			SET_BIT (TIMx -> CCMR2 ,14);
		}
	}
	
	
}
void Tim_voidOutputCompareMode(TIM_t *Timx){
	
}
/******************************************************************************/
void Tim_setPWMmode(TIM_t * TIMx ,channel_t Channel,PWM_t Mode, counter_m CounterMode,uint32 pulse){
	SET_BIT (TIMx -> EGR,UG);
	if (Channel == TIM_Channel1)
	{
		/*enable PWM mode 1*/
		CLR_BIT(TIMx -> CCMR1,4);
		SET_BIT(TIMx -> CCMR1,5);
		SET_BIT(TIMx -> CCMR1,6);
		/*enable pre load*/
		SET_BIT ( TIMx -> CCMR1,OC1PE);
		TIMx -> CCR1 =pulse;
	
	}else if 
	(Channel == TIM_Channel2)
	{
		CLR_BIT(TIMx -> CCMR1,12);
		SET_BIT(TIMx -> CCMR1,13);
		SET_BIT(TIMx -> CCMR1,14);
		SET_BIT ( TIMx -> CCMR1,OC2PE);
		TIMx -> CCR2 = pulse;
	}else if (Channel == TIM_Channel3)
	{
		CLR_BIT(TIMx -> CCMR2,4);
		SET_BIT(TIMx -> CCMR2,5);
		SET_BIT(TIMx -> CCMR2,6);
		SET_BIT ( TIMx -> CCMR2,OC3PE);
		TIMx -> CCR3 = pulse;
	}else if 
	(Channel == TIM_Channel4)
	{
		CLR_BIT(TIMx -> CCMR2,12);
		SET_BIT(TIMx -> CCMR2,13);
		SET_BIT(TIMx -> CCMR2,14);
		SET_BIT ( TIMx -> CCMR2,OC4PE);
		TIMx -> CCR1 =pulse;
	}
	uint32 Local = TIMx -> ARR;
	if ( Mode == EdgeAligned_Mode){
		
		Tim_setCounterMode(TIMx,CounterMode);
	}else if ( Mode == CenterAligned_Mode){
			Tim_setCounterMode(TIMx,Center_Aligned);
	}
	
	
	
}
void Tim_set_Interrupt(TIM_t *TIMx,TIM_Update_INT_State intState)
{
	switch(intState)
	{
	case Disable_Interrupt:
		CLR_BIT(TIMx -> DIER,UIE);
		break;
	case Enable_Interrupts:
		SET_BIT(TIMx -> DIER,UIE);
		break;
	default:
		break;
	}
}	
void Tim_setBusyWait(TIM_t *TIMx,uint32 ticks, uint32 ticksTybe)
{
	/*Assign ticks to load register*/
	TIMx->ARR = ticks * ticksTybe;
	/*Start timer*/
	SET_BIT(TIMx -> CR1,CEN);
	/*Wait until busy wait flag is raised */
	while(GET_BIT(TIMx -> SR,UIF) == 0);
	/*Stop timer*/
	CLR_BIT(TIMx -> CR1,CEN);
	/*Clear Timer registers*/
	TIMx->ARR = 0;
	/*Clear interrupt flag*/
	CLR_BIT(TIMx -> SR,UIF);
}

void Tim_setIntervalSingle  (TIM_t *TIMx, uint32 ticks, uint32 ticksTybe, void (*pFuncPtr)(void) )
{
	/*Stop timer*/
	CLR_BIT(TIMx->CR1,CEN);
	/*Clear Timer registers*/
	TIMx->ARR = 0;
	/*Assign ticks to load register*/
	TIMx->ARR = ticks * ticksTybe ;
	/* Assign callBack function */
	Timer_CallBack = pFuncPtr;
	/* Set Mode to Single */
	TIM_SET_INTERVAL_MODE(TIM_SINGLE_INTERVAL_MODE);
	/*Enable Timer interrupt*/
	SET_BIT(TIMx->DIER,UIE);
	/*Start timer*/
	SET_BIT(TIMx->CR1,CEN);
}

void TIM_setIntervalPeriodic(TIM_t *TIMx,uint32 ticks ,uint32 ticksTybe , void (* pFuncPtr) (void))
{
	/*Assign ticks to load register*/
	TIMx->ARR = ticks * ticksTybe ;
	/*Assign the function to the callback function */
	Timer_CallBack = pFuncPtr;
	/* Set Mode to Single */
	TIM_SET_INTERVAL_MODE(TIM_PERIODIC_INTERVAL_MODE);
	/*Enable Timer interrupt*/
	SET_BIT(TIMx->DIER,UIE);
	/*Start the counter*/
	SET_BIT(TIMx->CR1,CEN);
}
void TIM1_UP_IRQHandler (void)
{
	if(TIM_GET_INTERVAL_MODE() == TIM_SINGLE_INTERVAL_MODE)
	{
		/*Disable Timer interrupt*/
		CLR_BIT(TIM1 -> DIER ,UIE);
		/*Stop the counter*/
		CLR_BIT(TIM1 ->CR1 ,CEN);
		/*Clear timer registers*/
		TIM1->ARR = 0;
	}
	else
	{
		/*do nothing*/
	}

	/*Execute callback function*/
	Timer_CallBack();

	/*Clear interrupt flag*/
	CLR_BIT(TIM1->SR,UIF);
}
