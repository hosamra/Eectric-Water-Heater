/*
 * DIO.h
 *
 * Created: 3/25/2022 12:43:37 AM
 *  Author: User
 */ 


#ifndef DIO_H_
#define DIO_H_
#include "Common_Macros.h"
#include "Std_Types.h"
#include <avr/io.h>


void SetPinDirection(uint8 PORT , uint8 PIN , uint8 DIRECTION);
void SetPinValue(uint8 PORT , uint8 PIN , uint8 Value);

#include "Common_Macros.h"
#include "Std_Types.h"

#define DIO_OUTPUT 1
#define DIO_INPUT  0

#define DIO_HIGH 1
#define DIO_LOW 0

#define DIOA 0
#define DIOB 1
#define DIOC 2
#define DIOD 3

#endif /* DIO_H_ */