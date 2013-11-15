/* ###################################################################
**     Filename    : Events.c
**     Project     : ProcessorExpert
**     Processor   : MKL25Z128VLK4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2013-10-24, 17:13, # CodeGen: 26
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         EInt1_OnInterrupt - void EInt1_OnInterrupt(void);
**         Cpu_OnNMIINT      - void Cpu_OnNMIINT(void);
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
#include "common.h"
#include "sine.h"

#ifdef __cplusplus
extern "C" {
#endif 

unsigned char *p1 = (unsigned char*) 0x4003710C;
unsigned char *p2 = (unsigned char*) 0x4003711C;

/* User includes (#include below this line is not maintained by Processor Expert) */

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
  /* Write your code here ... */
}

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
**     Interrupt handler : PIT1_ISR
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
PE_ISR(PIT1_ISR)
{
	static unsigned int i = 0;
	unsigned int valDAC;
	unsigned int limit;
	
//	limit  = 1000 - Delta;
	*p1 |=1u; // Clear PIT Timer0 ISR flag
//	incDelta = 1;
	//*p2 |=1u;

//	*ptr = OutputData[i];
//    i+=1;
//    if(i>9)
//    	i=0;	

//	*ptr =  table[i];
	//*ptr =  trueTri[i];
	
	
    i+=Delta;
    valDAC = i >>18;
    
    //*ptr =  table[valDAC];
    *ptr =  sineTable[valDAC];
    
    //if(i>limit)
    //if(i>1023)
    //	i=0;
    
//    asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
//    asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
//    asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
		  //Bit1_SetVal();
		  //delay(10);
		  //Bit1_ClrVal();
		  //delay(10);
	
//    *ptr = table[i];//(unsigned int)SinusOutputData[i];
//    i+=1;
//    if(i>1023)
//    	i=0;	
}

/*
** ===================================================================
**     Interrupt handler : TPM0_ISR
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
PE_ISR(TPM0_ISR)
{
	
}


/*
** ===================================================================
**     Event       :  EInt2_OnInterrupt (module Events)
**
**     Component   :  EInt2 [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void EInt2_OnInterrupt(void)
{
	static int cnt = 0;
	
  /* Write your code here ... */


	  cnt ++;
	  if(cnt>=2)
	  {
		  cnt = 0;
//		  if(Delta == 1)
//		  {
//			  Delta+=9;
//		  }
//		  else
//			  Delta+=10;
		  //Delta *= 2;
		  Bit1_SetVal();
		  delay(100);
		  Bit1_ClrVal();
		  delay(100);		
		  
		  fout += 1000;
		  
		  //if(fout = 20000)
			//  fout = 100;
		  
		  Delta = (fout * 4294967296) / 100000;
		  
		  
//		  if(Delta >= 512)
//			  Delta = 1;
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
