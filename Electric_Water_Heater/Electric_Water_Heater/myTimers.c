/*
 * myTimers.c
 *
 * Created: 22/07/2021 10:38:55
 *  Author: HOSAM
 */ 
#include "myTimers.h"

static void(*Timer1CTC_CALLBACK)(void);

//timer0
//TCCR0= [FOC0 - WGM00 - COM01 - COM00 - WGM01 - CS02 - CS01 - CS00 ]
//TIFR = [ OCF2 - TOV2 - ICF1 - OCF1A - OCF1B - TOV1 - OCF0 - TOV0]

void start_timer0_normalMode(unsigned char TCNTValue , unsigned char prescalerValue){
	TCNT0 = TCNTValue;
	
	switch (prescalerValue)
	{
		case 0 : //stopped 
		TCCR0 = 0x00;
		break;
		case 1 : // no prescaler
		TCCR0 = 0X01; //CS12 = 0 , CS11=0 , CS10=1 ,WGM01=0 , WGM00=0
		break;
		case 2 : // /2
		TCCR0 = 0x02;
		break;
		case 3 : // /64
		TCCR0 = 0x03;
		break;
		case 4 : // /256
		TCCR0 = 0x04;
		break;
		case 5 : ///1024
		TCCR0 = 0x05;
		break;
		case 6 : // external (falling edge)
		TCCR0 = 0x06;
		break;
		case 7 : // external (rising edge)
		TCCR0 = 0x07;
		break;
		default:
		TCCR0 = 0x01;
		break;
			
	}
}

void start_timer0_CTCMode(unsigned char OCR0Value , unsigned char prescalerValue){
	TCNT0 = 0;
	OCR0 = OCR0Value;
	
	switch (prescalerValue)
	{
		case 0 : //stopped
		TCCR0 = 0x00;
		break;
		case 1 : // no prescaler
		TCCR0 = 0X09; //CS12 = 0 , CS11=0 , CS10=1 ,WGM01=1 , WGM00=0
		break;
		case 2 : // /2
		TCCR0 = 0x0a;
		break;
		case 3 : // /64
		TCCR0 = 0x0b;
		break;
		case 4 : // /256
		TCCR0 = 0x0c;
		break;
		case 5 : ///1024
		TCCR0 = 0x0d;
		break;
		case 6 : // external (falling edge)
		TCCR0 = 0x0e;
		break;
		case 7 : // external (rising edge)
		TCCR0 = 0x0f;
		break;
		default:
		TCCR0 = 0x09;
		break;
		
	}
}

void stop_timer0_NormalLMode(){
	TCCR0=0; // stop timer
	TIFR |= (1<<TOV0); // clear TOV0 flag
}

void stop_timer0_CTCMode(){
	TCCR1B=0; // stop timer
	TIFR |= (1<<OCF0); // clear OCF0 flag
}


void timer0_squareWave(unsigned char OCR0Value , unsigned char prescalerValue){
	TCNT0 = 0;
	OCR0 = OCR0Value;
	
	switch (prescalerValue)
	{
		case 0 : //stopped
		TCCR0 = 0x00;
		break;
		case 1 : // no prescaler
		TCCR0 = 0X19; //CS12 = 0 , CS11=0 , CS10=1 ,WGM01=1 , WGM00=0
		break;
		case 2 : // /8
		TCCR0 = 0x1a;
		break;
		case 3 : // /64
		TCCR0 = 0x1b;
		break;
		case 4 : // /256
		TCCR0 = 0x1c;
		break;
		case 5 : ///1024
		TCCR0 = 0x1d;
		break;
		case 6 : // external (falling edge)
		TCCR0 = 0x1e;
		break;
		case 7 : // external (rising edge)
		TCCR0 = 0x1f;
		break;
		default:
		TCCR0 = 0x19;
		break;
		
	}
}




//timer2
//TCCR0= [FOC2 - WGM20 - COM21 - COM20 - WGM21 - CS22 - CS21 - CS20 ]
void start_timer2_normalMode(unsigned char TCNTValue , unsigned char prescalerValue){
	TCNT2 = TCNTValue;
	
	switch (prescalerValue)
	{
		case 0 : //stopped
		TCCR2 = 0x00;
		break;
		case 1 : // no prescaler
		TCCR2 = 0X01; //CS22 = 0 , CS21=0 , CS20=1 ,WGM21=0 , WGM20=0
		break;
		case 2 : // /8
		TCCR2 = 0x02;
		break;
		case 3 : // /32
		TCCR2 = 0x03;
		break;
		case 4 : // /64
		TCCR2 = 0x04;
		break;
		case 5 : // /128
		TCCR2 = 0x05;
		break;
		case 6 : // /256
		TCCR2 = 0x06;
		break;
		case 7 : // /1024
		TCCR2 = 0x07;
		break;
		default:
		TCCR2 = 0x01;
		break;
		
	}
}

void start_timer2_CTCMode(unsigned char OCR2Value , unsigned char prescalerValue){
	OCR2 = OCR2Value;
	
	switch (prescalerValue)
	{
		case 0 : //stopped
		TCCR2 = 0x00;
		break;
		case 1 : // no prescaler
		TCCR2 = 0X09;
		break;
		case 2 : // /8
		TCCR2 = 0x0a;
		break;
		case 3 : // /32
		TCCR2 = 0x0b;
		break;
		case 4 : // /64
		TCCR2 = 0x0c;
		break;
		case 5 : ///128
		TCCR2 = 0x0d;
		break;
		case 6 : // 256
		TCCR2 = 0x0e;
		break;
		case 7 : // 1024
		TCCR2 = 0x0f;
		break;
		default:
		TCCR2 = 0x09;
		break;
		
	}
}

void stop_timer2_NormalLMode(){
	TCCR2=0; // stop timer
	TIFR |= (1<<TOV2); // clear TOV2 flag
}

void stop_timer2_CTCMode(){
	TCCR2=0; // stop timer
	TIFR |= (1<<OCF2); // clear OCF2 flag
}


//TIMER 1
//TCCR1A= [COM1A1 - COM1A0 - COM1B1 - COM1B0 - FOC1A - FOC1B - WGM11 - WGM10 ]
//TCCR1B= [ICNC1 - ICES1 - , - WGM13 - WGM12 - CS12 - CS11 - CS10 ]
void start_timer1_normalMode(int TCNTValue , unsigned char prescalerValue){
	TCNT1 = TCNTValue;
	
	switch (prescalerValue)
	{
		case 0 : //stopped
		TCCR1A = 0x00;
		TCCR1B = 0X00;
		break;
		case 1 : // no prescaler
		TCCR1A = 0x00; // WGM13 = 0 , WGM12 = 0 , WGM11 = 0 WGM10 = 0 (NORMAL MODE)
		TCCR1B = 0X01; //CS12 = 0 , CS11=0 , CS10 =1
		break;
		case 2 : // /8
		TCCR1A = 0x00;
		TCCR1B = 0X02;
		break;
		case 3 : // /64
		TCCR1A = 0x00;
		TCCR1B = 0X03;
		break;
		case 4 : // /256
		TCCR1A = 0x00;
		TCCR1B = 0X04;
		break;
		case 5 : ///1024
		TCCR1A = 0x00;
		TCCR1B = 0X05;
		break;
		case 6 : // external (falling edge)
		TCCR1A = 0x00;
		TCCR1B = 0X06;
		break;
		case 7 : // external (rising edge)
		TCCR1A = 0x00;
		TCCR1B = 0X07;
		break;
		default:
		TCCR1A = 0x00;
		TCCR1B = 0X01;
		break;
		
	}
}

void start_timer1_CTCMode(uint16 OCRValue , unsigned char prescalerValue){
	OCR1A = OCRValue;
	
	switch (prescalerValue)
	{
		case 0 : //stopped
		TCCR1A = 0x00;
		TCCR1B = 0X00;
		break;
		case 1 : // no prescaler
		TCCR1A = 0x00;
		TCCR1B = 0X09; // WGM13 = 0 , WGM12 = 1 , WGM11 = 0 WGM10 = 0 (CTC MODE)
		break;
		case 2 : // /8
		TCCR1A = 0x00;
		TCCR1B = 0X0A;
		break;
		case 3 : // /64
		TCCR1A = 0x00;
		TCCR1B = 0X0B;
		break;
		case 4 : // /256
		TCCR1A = 0x00;
		TCCR1B = 0X0C;
		break;
		case 5 : ///1024
		TCCR1A = 0x00;
		TCCR1B = 0X0D;
		break;
		case 6 : // external (falling edge)
		TCCR1A = 0x00;
		TCCR1B = 0X0E;
		break;
		case 7 : // external (rising edge)
		TCCR1A = 0x00;
		TCCR1B = 0X0F;
		break;
		default:
		TCCR1A = 0x00;
		TCCR1B = 0X09;
		break;
		
	}
}

void Timer1EnableCTCInterrupt(void (*callback)(void) )
{
	Timer1CTC_CALLBACK = callback;
	Set_Bit(TIMSK,4);
	sei();
}

void stop_timer1_NormalLMode(){
	TCCR1B=0; // stop timer
	TIFR |= (1<<TOV1); // clear ocf1a flag
}

void stop_timer1_CTCMode(){
	TCCR1B=0; // stop timer
	TIFR |= (1<<OCF1A); // clear ocf1a flag
}


ISR(TIMER1_COMPA_vect)
{
	Timer1CTC_CALLBACK();
	TIFR |= (1<<OCF1A); // clear ocf1a flag
}

