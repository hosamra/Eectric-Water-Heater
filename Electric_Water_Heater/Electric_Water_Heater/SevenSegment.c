/*
 * SevenSegment.c
 *
 * Created: 3/25/2022 2:08:53 AM
 *  Author: User
 */ 

#include "DIO.h"

static uint8 numbers[10][7]={{0,0,0,0,0,0,1},
						   {1,0,0,1,1,1,1},
						   {0,0,1,0,0,1,0},
						   {0,0,0,0,1,1,0},
						   {1,0,0,1,1,0,0},
				     	   {0,1,0,0,1,0,0},
						   {0,1,0,0,0,0,0},
						   {0,0,0,1,1,1,0},
			               {0,0,0,0,0,0,0},
						   {0,0,0,0,1,0,0}};
			

void Init_SevenSegment(uint8 port, uint8 *pins)
{
	// set 7 segment pins direction
	for(uint8 i = 0 ; i<7 ; i++) SetPinDirection(port,pins[i],DIO_OUTPUT);
}

void SevenSegmentDeisplay(uint8 port, uint8 *pins , uint8 number)
{
	for(uint8 i =0 ; i<7 ; i++)
	{
		SetPinValue(port,pins[i],numbers[number][i]);
	}
	
}

void SevenSegmentDiplayOFF(uint8 port, uint8 *pins )
{
	for(uint8 i =0 ; i<7 ; i++)
	{
		SetPinValue(port,pins[i],1);
	}
	
}