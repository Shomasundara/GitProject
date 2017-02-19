/******************************************************
 * 
 *  Title      :Creating leapfrogging timer using timer 
 *              compare method for simple scheduling.
 *  By	       :Somusundram
 *  Date       :16 January 2017
 *
 *  Comments   :
 *
 *  Revision History
 *  
 * ***************************************************
 *  Version	    Record		  Person
 *
 *  0.1 	Created C file		Somusundram
 *
 *
 *
 *****************************************************/


/*****************************************************/
/*		    PREPROCESSOR		     */
/*****************************************************/

#include <avrio.h>
#include <avr/interrupt.h>
#include <stdint.h>

/*****************************************************/
/*		     DEFINES			     */
/*****************************************************/

#define         LD_SEQ		(4)
#define         CNT_VAL		(0)

#define 	LED_ON		(PORTB |= (1<<PB0))
#define         LED_OFF		(PORTB &=~(1<<PB0))
#define         LED_TOG	        (PORTB ^= (1 << PB0))

/*****************************************************/
/*		     GLOBAL VAR			     */
/*****************************************************/

typedef struct 
{
   uint8_t	tick:3u;
   uint8_t      Cnt :5u;

}Seq_t;

Seq_t Sequence = {LD_SEQ,CNT_VAL};


/*****************************************************/
/*                   HANDLER COMP-A		     */
/*****************************************************/

ISR(TIMER1_COMPA_vect)
{
  ++Sequence.Cnt;
  
  if(Sequence.Cnt >= 60u)  			//1mS X 60 = 1 Sec.
  {
    LED_TOG;
    Sequence.Cnt = CNT_VAL;
  }
 
}

/*****************************************************/
/*                   HANDLER COMP-B		     */
/*****************************************************/

ISR(TIMER1_COMPB_vect)
{    
      
}

/*****************************************************/
/*                   TIMER COMP INIT		     */
/*****************************************************/

static void init_Timer(void)
{
   TCCR1A = (1<<CS11)|(1<<CS10);		//Assign Prscl = 64				
   TCCR1B = (1<<CS12);       			//Assign PrScl = 256
   OCR1A = 250;					//Preset to tick at 1 mSec = 16MHz/64 = 250KHz. T = 1/f ~ 4mS
   OCR1B = 500;					//Preset to tick at Nth?m?Sec?
   TIMSK |= (1<<OC1E1A) | (1<<OC1E1B);		//Set Comp A and B
}


/*****************************************************/
/*                   I/0 INIT		     	     */
/*****************************************************/

static void init_Pins(void)
{ 
  DDRB |= (1<<PB0);					//Set PB0 as output
  DDRC |= (1<<PC0) | (1<<PC1) | (1<<PC2) | (1<<PC3);	//Set PC0 to 3 as output
}

/*****************************************************/
/*			MAIN			     */
/*****************************************************/


void setup()
{    

   cli();
   
   init_Pins();
   init_Timer();

   sei();
		 
}


void loop()
{
  
  //This runs at 1KHz generated from Timer-0 (8bit)
  
}














