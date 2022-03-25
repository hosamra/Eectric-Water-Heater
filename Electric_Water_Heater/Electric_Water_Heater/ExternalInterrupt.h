/*
 * ExternalInterrupt.h
 *
 * Created: 3/26/2022 12:02:34 AM
 *  Author: User
 */ 


#ifndef EXTERNALINTERRUPT_H_
#define EXTERNALINTERRUPT_H_

#include "Micro_config.h"
#include "Common_Macros.h"
#include "Std_Types.h"

void ExternalINT_Init(uint8 INTNumber ,uint8 trigger );
void ExternalINT_SetCallBack(uint8 INTNumber , void(*CALLBACK)(void));

#define EXINT0 0
#define EXINT1 1
#define EXINT2 2

#define LOW_LEVEL 0
#define ANY_CHANGE 1
#define FALLLING_EDGE 2
#define RISING_EDGE  3




#endif /* EXTERNALINTERRUPT_H_ */