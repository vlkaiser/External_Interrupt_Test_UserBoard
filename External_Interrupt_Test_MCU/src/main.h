/*
 * main.h
 *
 * Created: 1/31/2020 9:44:19 AM
 *  Author: VKaiser
 */ 


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


#endif /* MAIN_H_ */