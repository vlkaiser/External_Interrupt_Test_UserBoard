/*
 * main.h
 *
 * Created: 1/31/2020 9:44:19 AM
 *  Author: VKaiser
 */ 

 /**************** SYSTEM NOTES *****************************
 * Robot Card:
 * I2C A (Command Bus / Device Control / Data) 
 *		SCL: P17 (PA08) - SERCOM0 PAD0 / alt: SERCOM2 PAD0
 *		SDA: P18 (PA09)	- SERCOM0 PAD1 / alt: SERCOM2 PAD1
 *
 * I2C B (Service Bus / Engineering Data)
 *		SCL: P36 (PA17) - SERCOM1 PAD1 / alt: SERCOM3 PAD1
 *		SDA: P35 (PA16) - SERCOM1 PAD0 / alt: SERCOM3 PAD0
 *
 * I2C C ( )
 *		SCL: P29 (PA12) - SERCOM2 PAD0 / alt: SERCOM4 PAD0
 *		SDA: P30 (PA13) - SERCOM2 PAD1 / alt: SERCOM4 PAD1
 *
 * IO Panel Button (Interrupts) Pullup 10K to VDDMCU
 *		Power:		P61	PB00
 *		Measure:	P62	PB01
 *		Stop:		P63	PB02
 *	
 * IO Panel LEDs
 *		Power	  (Red): P14	PA05
 *		Power	(Green): P15	PA06
 *		Measure (White): P27	PB14
 *		Stop	  (Red): P28	PB15
 *
 * STATUS LEDS
 *		GREEN	: P38	PA19
 *		ORANGE	: P37	PA18
 *
 * STROBE
 *		P6	PB05
 *
 * SPARE01
 *		P3	PA02
 *
 * SPARE02
 *		P4	PA03
 *
 * GPIO11
 *		P31	PA14
 * 
 * RESET
 *		P52	~RESETN
 *
 * UART
 *		TX: P11	PB08 - alt: SERCOM4 PAD0
 *		RX: P12	PB09 - alt: SERCOM4 PAD1
 *
 ********************************************************/


#ifndef MAIN_H_
#define MAIN_H_

#include <asf.h>
#include "user_board.h"
#include "DC_TypeDefs.h"
#include "DC_peripherals.h"
#include "DC_sercom.h"
#include "stdio.h"
#include "string.h"

#pragma pack(1)		//define 1 byte boundaries instead of 4 byte

void sensorRead(uint8_t* rd_buf);
void clear_wrCMDS(void);

#endif /* MAIN_H_ */