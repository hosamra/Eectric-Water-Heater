/*
 * myTimers.h
 *
 * Created: 22/07/2021 10:56:05
 *  Author: Hosam
 */ 


#ifndef MYTIMERS_H_
#define MYTIMERS_H_
#include "Micro_config.h"
#include "Common_Macros.h"
#include "Std_Types.h"

//timer0
void start_timer0_normalMode(unsigned char TCNTValue , unsigned char prescalerValue);
void start_timer0_CTCMode(unsigned char OCR0Value , unsigned char prescalerValue);
void stop_timer0_NormalLMode();
void stop_timer0_CTCMode();
void timer0_squareWave(unsigned char OCR0Value , unsigned char prescalerValue);

//timer2
void start_timer2_normalMode(unsigned char TCNTValue , unsigned char prescalerValue);
void start_timer2_CTCMode(unsigned char OCR2Value , unsigned char prescalerValue);
void stop_timer2_NormalLMode();
void stop_timer2_CTCMode();

//TIMER1
void start_timer1_normalMode(int TCNTValue , unsigned char prescalerValue);
void start_timer1_CTCMode(uint16 OCRValue , unsigned char prescalerValue);
void Timer1EnableCTCInterrupt();
void stop_timer1_NormalLMode();
void stop_timer1_CTCMode();

#define STOP_TIMER 0
#define TIMER_NOPS 1
#define TIMER_8PS  2
#define TIMER_16PS 3




#endif /* MYTIMERS_H_ */