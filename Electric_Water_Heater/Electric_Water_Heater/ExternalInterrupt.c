/*
 * ExternalInterrupt.c
 *
 * Created: 3/26/2022 12:02:04 AM
 *  Author: User
 */ 

#include "ExternalInterrupt.h"

static void (*INT0_CALLBACK)(void)=0;
static void (*INT1_CALLBACK)(void)=0;
static void (*INT2_CALLBACK)(void)=0;

void ExternalINT_Init(uint8 INTNumber ,uint8 trigger )
{
	if (INTNumber == EXINT0)
	{
		Clear_Bit(DDRD , 2);
		Set_Bit(GICR,6);
		MCUCR = (trigger | (MCUCR&0XFD) );
	}
	else if (INTNumber == EXINT1)
	{
		Clear_Bit(DDRD , 3);
		Set_Bit(GICR,7);
		MCUCR = ( (trigger<<2) | (MCUCR&0XF3) );
	}
	else if(INTNumber == EXINT2)
	{
		Clear_Bit(DDRB , 2);
		Set_Bit(PORTB,2); //INTERNAL PULLUP
		Set_Bit(GICR,5);
		if(trigger == FALLLING_EDGE) Clear_Bit(MCUCSR,6);
		else if (trigger == RISING_EDGE) Set_Bit(MCUCSR , 6);
	}
}

void ExternalINT_SetCallBack(uint8 INTNumber , void(*CALLBACK)(void))
{
	switch(INTNumber)
	{
		case EXINT0 :
		INT0_CALLBACK = CALLBACK; 
		break;
		
		case EXINT1 :
		INT1_CALLBACK = CALLBACK;
		break;
		
		case EXINT2 :
		INT2_CALLBACK = CALLBACK;
		break;
		
		default:
		break;
	}
	sei();
}

ISR(INT0_vect)
{
	INT0_CALLBACK();
}

ISR(INT1_vect)
{
	INT1_CALLBACK();
}

ISR(INT2_vect)
{
	INT2_CALLBACK();
}