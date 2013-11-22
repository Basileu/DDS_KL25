/* ###################################################################
**     Filename    : ProcessorExpert.c
**     Project     : ProcessorExpert
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2013-11-15, 14:57, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file ProcessorExpert.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup ProcessorExpert_module ProcessorExpert module documentation
**  @{
*/         
/* MODULE ProcessorExpert */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "Bit1.h"
#include "BitIoLdd1.h"
#include "DA1.h"
#include "PIT.h"
#include "EInt1.h"
#include "ExtIntLdd1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

#include <math.h>
#include "arm_math.h"

#include "table.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

float y;
float sinArg;
unsigned int dacOut;
unsigned int i;
unsigned int *ptr;
unsigned int temp1;
float rad;

static LDD_TDeviceData *MyDacPtr;

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */

void delay(unsigned int cnt)
{
	while((--cnt) > 1)
	{
		asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
		asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
	}
}

void calcTable(void)
{
	unsigned int i;
	// 1. Calc delta
	// Delta  = (Fout * N) / Fsampling
	Delta = (Fout * NrSteps) / 100000;
	
	// 2. Calc step : S = N/D
	step = 1000 / Delta;
	
	// 3. Calc table size
	tableSize = step * Delta;

	// 4. Generate table
	  for(i=0;i<tableSize;i++)
	  {
		  temp1 = i*360;
		  sinArg = (float)((float)temp1/(float)tableSize) ;
		  rad = (float)((3.14159265358979 * sinArg) / (float)180);
		  y = arm_sin_f32(rad);
		  dacOut = (float)(2048 + (float)(y * (float)2048));
		  if(dacOut > 4095)
			  dacOut = 4095;
		  sineTable[i] = dacOut;
	  }	
	  
	  // 6. Calc new fsample
	  newPeriod = 1/Fout;
	  newSlotPeriod = newPeriod / step;
	  newSlotPeriod *= 1000000; // scale to us 
	  
//	  if(newSlotPeriod > Tsample)
//	  {
//		  deltaPeriodSample = newSlotPeriod - Tsample;
//	  }
//	  else
//	  {
//		  deltaPeriodSample = Tsample - newSlotPeriod;
//	  }
		
//	  deltaPeriodSample /= Tosc;
	  loadPIT = newSlotPeriod/Tosc - 1;
	  // 5. adjust Fsample
	  /* PIT_LDVAL0: TSV=0xC7 */
	  PIT_LDVAL0 = PIT_LDVAL_TSV(loadPIT);                                   
	  /* PIT_LDVAL1: TSV=0 */
	  PIT_LDVAL1 = PIT_LDVAL_TSV(0x00);   
	
}
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  
  MyDacPtr = DA1_Init(NULL);                                            /* Initialization of DA1 component */
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  
  ptr = (unsigned int*) 0x4003F000;
  
  
//  Bit1_ClrVal();
//  Bit1_SetVal();
//  Bit1_ClrVal();
  
  for(i=0;i<NrSteps;i++)
  {
	  temp1 = i*360;
	  sinArg = (float)((float)temp1/(float)NrSteps) ;
	  rad = (float)((3.14159265358979 * sinArg) / (float)180);
	  y = arm_sin_f32(rad);
	  dacOut = (float)(2047 + (float)(y * (float)2047));
	  if(dacOut > 4095)
		  dacOut = 4095;
	  sineTable[i] = dacOut;
  }
//  Bit1_SetVal();
//  Bit1_ClrVal();
//  Bit1_SetVal();
//  
  PIT_Init();
  tableSize = 1000;
  Fout = 100;
  doCalc = 0;
  Delta = 1;
  while(1)
  {
	  if(doCalc == 1)
	  {
		  doCalc = 0;
		  calcTable();
	  }
//	  Bit1_SetVal();
//	  delay(100);
//	  Bit1_ClrVal();
//	  delay(100);
  }
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END ProcessorExpert */
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
