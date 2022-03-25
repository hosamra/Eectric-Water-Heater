/*
 * Electric_Water_Heater.c
 *
 * Created: 3/25/2022 12:39:10 AM
 * Author : Hosam
 */ 


#include "DIO.h"
#include "ADC.h"
#include "myTimers.h"
#include "ExternalInterrupt.h"
#include "EEPROM.h"
#include "APP_CONFIG.h"

#include "SevenSegment.h"



void display_temp(uint8 number);
uint8 read_temp();
void TempAVG();
void set_mode();
void ON_OFF_Button();
void timer1Interrupt();

uint8 TIMER1_OVERFLOW = 0;
uint8 SetModeOVERFLOW =0;
uint8 TEMPArray_index =0;
uint8 seven_segment_pins[7]={0,1,2,3,4,5,6};
uint8 temp[10];
uint8 AVG_tmep;
uint8 REQUIRED_TEMP = 60; // default value 
uint8 STARTFLAG = 1;
uint8 SETMODEFLAG=0;

//buttons flags
uint8 UP_BUTTON_FLAG=1;
uint8 DOWN_BUTTON_FLAG=1;

uint8  HEATING=0;
uint8  ON_OFF_STATE =0;

int main(void)
{
	/* seven segment*/
	Init_SevenSegment(LSEVENSEGMENTPORT,seven_segment_pins); // initialize Left seven segment
	Init_SevenSegment(RSEVENSEGMENTPORT,seven_segment_pins); // initialize right seven segment
	
	/* temp sensor */
	SetPinDirection(DIOA,7,DIO_INPUT); //A7 is input for ADC
	ADC_Init(); // initialize ADC
	
	/*up and down buttons (set temperature) */
	SetPinDirection(UP_BUTTON,DIO_INPUT); // initialize up button
	SetPinValue(UP_BUTTON,DIO_HIGH); //INPUT PULLUP
	SetPinDirection(DOWN_BUTTON,DIO_INPUT); // initialize down button
	SetPinValue(DOWN_BUTTON,DIO_HIGH); //INPUT PULLUP
	
	SetPinDirection(DIOD,HEATING_LED,DIO_OUTPUT); //heating led pin as output
	
	ExternalINT_Init(EXINT2 , FALLLING_EDGE); //External interrupt for ON/OFF button
	ExternalINT_SetCallBack(EXINT2,ON_OFF_Button); //Set EXTINT2 callBcck for ON/OFF button
	
	/* TIMER1 */
	//start_timer1_CTCMode(12500,TIMER_8PS); //compare match occurs every 100 ms
	//Timer1EnableCTCInterrupt(timer1Interrupt);
	
	/* clear seven segment */
	SevenSegmentDiplayOFF(RSEVENSEGMENTPORT,seven_segment_pins);
	SevenSegmentDiplayOFF(LSEVENSEGMENTPORT,seven_segment_pins);
	
	/* init EEPROM*/
	EEOpen();
	EEWriteByte(REQUIRED_TEMP_ADDRESS,REQUIRED_TEMP);
	
	
    
    while (1) 
    {
		if (ON_OFF_STATE)
		{
		
		/* UP button is pressed */
		if (Bit_Is_Clear(PINB,6)  && UP_BUTTON_FLAG) 
		{
			UP_BUTTON_FLAG=0;
			if(STARTFLAG==1)
			{
				STARTFLAG=0;
				SETMODEFLAG=1;
				
				set_mode(); //enter set mode
			}
		}
		
		/* down button is pressed */
		if (Bit_Is_Clear(PINB,7)  && DOWN_BUTTON_FLAG) 
		{
			DOWN_BUTTON_FLAG=0;
			if(STARTFLAG==1)
			{
				STARTFLAG=0;
				SETMODEFLAG=1;
				set_mode(); //enter set mode
			}
		}
		
		/*Check wheather to turn on heater or cooler */
		if(AVG_tmep<REQUIRED_TEMP){
			if ( (REQUIRED_TEMP-AVG_tmep) >= 5 )
			{
				HEATING=1; //turn on heater
			}
		}
		else
		{
			if ( (AVG_tmep-REQUIRED_TEMP) >= 5 )
			{
				HEATING=0; // turn on cooler
			}
		}
		
		if (Bit_Is_Set(PINB,6)) UP_BUTTON_FLAG=1;
		if (Bit_Is_Set(PINB,7)) DOWN_BUTTON_FLAG=1;
		
		}	
	}
		
}


void display_temp(uint8 number){
	uint8 digit;
		
		digit = number%10; // get right digit
		number= number/10;
		SevenSegmentDeisplay(RSEVENSEGMENTPORT,seven_segment_pins,digit); //display the right digit
		digit = number%10; // get left digit
		SevenSegmentDeisplay(LSEVENSEGMENTPORT,seven_segment_pins,digit); //display the left digit
}
	
uint8 read_temp()
	{
		uint8 t;
		t = (ADC_read(7)*4.88 ) /10;
		return t;
	}
	
void TempAVG()
{
	uint16 sum=0;
	for(uint8 i = 0 ; i<10 ; i++)
	{
		sum+= temp[i];
	}
	AVG_tmep = sum/10;
}
	
	
void set_mode()
	{
		while(SETMODEFLAG)
		{
			display_temp(REQUIRED_TEMP);
			
			//Increase required temp
			if(Bit_Is_Clear(PINB,6) && UP_BUTTON_FLAG) 
			{
				if(REQUIRED_TEMP<71) REQUIRED_TEMP+=5;
				SetModeOVERFLOW=0; // count 5s again to exit set mode
				UP_BUTTON_FLAG=0;
			}
			
			//decrease required temp
			if (Bit_Is_Clear(PINB,7) && DOWN_BUTTON_FLAG) 
			{
				if(REQUIRED_TEMP>39)REQUIRED_TEMP-=5;
				SetModeOVERFLOW=0; // count 5s again to exit set mode
				DOWN_BUTTON_FLAG=0;
			}
			
			if (Bit_Is_Set(PINB,6)) UP_BUTTON_FLAG=1;
			if (Bit_Is_Set(PINB,7)) DOWN_BUTTON_FLAG=1;
		}
		
	}
	
void ON_OFF_Button()
{
	ON_OFF_STATE = !ON_OFF_STATE;
	
	if (ON_OFF_STATE)
	{
		REQUIRED_TEMP = EEReadByte(REQUIRED_TEMP_ADDRESS);
		/*timer 1 init*/
		start_timer1_CTCMode(12500,TIMER_8PS); //compare match occurs every 100 ms
		Timer1EnableCTCInterrupt(timer1Interrupt);
	}
	else
	{
		/* clear seven segment */
		SevenSegmentDiplayOFF(RSEVENSEGMENTPORT,seven_segment_pins);
		SevenSegmentDiplayOFF(LSEVENSEGMENTPORT,seven_segment_pins);
		
		//reset system
		stop_timer1_CTCMode();
		STARTFLAG = 1;
		SETMODEFLAG=0;
		UP_BUTTON_FLAG=1;
		DOWN_BUTTON_FLAG=1;
		if(EEWriteByte(REQUIRED_TEMP_ADDRESS,REQUIRED_TEMP))
		REQUIRED_TEMP=0;
	}
}
	
	
	void timer1Interrupt()
	{
		/* New temperature reading*/
		temp[TEMPArray_index] = read_temp(); //read temp every 100 ms
		if (TEMPArray_index<9) TEMPArray_index++; //increase array index;
		else				   TEMPArray_index=0;	// reset index
		
		if(HEATING)
		{
			SetPinValue(DIOD,HEATING_LED, !Bit_Is_Set(PIND,HEATING_LED) ); //BLINK HEATING LED
		}
		else
		{
			SetPinValue(DIOD,HEATING_LED, DIO_HIGH ); //turn on HEATING LED (COOLING)
		}
		
		/* update temperature*/
		if (TEMPArray_index==0 && SETMODEFLAG ==0)
		{
			TempAVG();
			display_temp(AVG_tmep);
		}
		
		
		if(SETMODEFLAG)
		{
			TIMER1_OVERFLOW++;
			SetModeOVERFLOW++;
			
			/* blink display*/
			if(TIMER1_OVERFLOW == 10)
			{
				SevenSegmentDiplayOFF(RSEVENSEGMENTPORT,seven_segment_pins); //turn off right 7S
				SevenSegmentDiplayOFF(LSEVENSEGMENTPORT,seven_segment_pins); // turn off left 7s
				_delay_ms(10);
				TIMER1_OVERFLOW=0;
			}
			
			if (SetModeOVERFLOW ==50)
			{
				SETMODEFLAG=0; //Exit set mode
				SetModeOVERFLOW=0;
				SevenSegmentDiplayOFF(RSEVENSEGMENTPORT,seven_segment_pins); //turn off right 7S
				SevenSegmentDiplayOFF(LSEVENSEGMENTPORT,seven_segment_pins); // turn off left 7s
			}	
		}
	}
	
	

