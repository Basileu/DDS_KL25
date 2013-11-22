/* ###################################################################
**     Filename    : Events.c
**     Project     : ProcessorExpert
**     Processor   : MKL25Z128VLK4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2013-11-15, 14:57, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"
#include "table.h"

#ifdef __cplusplus
extern "C" {
#endif 

unsigned char *p1 = (unsigned char*) 0x4003710C;
unsigned char *p2 = (unsigned char*) 0x4003711C;

/* User includes (#include below this line is not maintained by Processor Expert) */

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MKL25Z128LK4]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Interrupt handler : ISR_PIT
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
PE_ISR(ISR_PIT)
{
	static unsigned int i = 0;

	
	*p1 |=1u; // Clear PIT Timer0 ISR flag
	
	i+=Delta;
	if(i>tableSize-1)
		i = 0;
	
	*ptr = sineTable[i];
	
//	  Bit1_SetVal();
//	  delay(10);
//	  Bit1_ClrVal();
//	  delay(10);
	  
}



/*
** ===================================================================
**     Event       :  EInt1_OnInterrupt (module Events)
**
**     Component   :  EInt1 [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void EInt1_OnInterrupt(void)
{
	static unsigned char cnt;
  /* Write your code here ... */
	  /* Write your code here ... */
			  Bit1_SetVal();
			  delay(10);
			  Bit1_ClrVal();
			  delay(10);
			  cnt++;
			  if(cnt > 2)
			  {
				  doCalc = 1;
				  cnt = 0;
				  //Fout += 100;
				  Fout = 19300;
			  }
				  
			  
}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.08]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
