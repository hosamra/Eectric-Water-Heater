/*
 * SevenSegment.h
 *
 * Created: 3/25/2022 2:45:07 AM
 *  Author: User
 */ 


#ifndef SEVENSEGMENT_H_
#define SEVENSEGMENT_H_

void Init_SevenSegment(uint8 port, uint8 *pins);
void SevenSegmentDeisplay(uint8 port, uint8 *pins , uint8 number);
void SevenSegmentDiplayOFF(uint8 port, uint8 *pins );



#endif /* SEVENSEGMENT_H_ */