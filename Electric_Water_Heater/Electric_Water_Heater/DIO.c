/*
 * DIO.c
 *
 * Created: 3/25/2022 12:41:46 AM
 *  Author: User
 */ 


#include "DIO.h"

void SetPinDirection(uint8 PORT , uint8 PIN , uint8 DIRECTION)
{
	if(PORT == DIOA)
	{
		if(DIRECTION == DIO_OUTPUT) Set_Bit(DDRA,PIN);
		else Clear_Bit(DDRA,PIN);
	}
	else if(PORT == DIOB)
	{
		if(DIRECTION == DIO_OUTPUT) Set_Bit(DDRB,PIN);
		else Clear_Bit(DDRB,PIN);
	}
	else if(PORT == DIOC)
	{
		if(DIRECTION == DIO_OUTPUT) Set_Bit(DDRC,PIN);
		else Clear_Bit(DDRC,PIN);
	}
	else if(PORT == DIOD)
	{
		if(DIRECTION == DIO_OUTPUT) Set_Bit(DDRD,PIN);
		else Clear_Bit(DDRD,PIN);
	}
}

void SetPinValue(uint8 PORT , uint8 PIN , uint8 Value)
{
	if(PORT == DIOA)
	{
		if(Value == DIO_HIGH) Set_Bit(PORTA,PIN);
		else Clear_Bit(PORTA,PIN);
	}
	else if(PORT == DIOB)
	{
		if(Value == DIO_HIGH) Set_Bit(PORTB,PIN);
		else Clear_Bit(PORTB,PIN);
	}
	else if(PORT == DIOC)
	{
		if(Value == DIO_HIGH) Set_Bit(PORTC,PIN);
		else Clear_Bit(PORTC,PIN);
	}
	else if(PORT == DIOD)
	{
		if(Value == DIO_HIGH) Set_Bit(PORTD,PIN);
		else Clear_Bit(PORTD,PIN);
	}
}
