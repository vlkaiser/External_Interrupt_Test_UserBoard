/*
 * Peripherals.h
 *
 * Created: 1/30/2020 6:16:20 PM
 *  Author: VKaiser
 */ 


#ifndef PERIPHERALS_H_
#define PERIPHERALS_H_

#include "main.h"

#pragma pack(1)		//define 1 byte boundaries instead of 4 byte

	struct write_cmds
	{
		uint8_t cmdID;
		uint32_t encLocMoveTo;
	};
	struct write_cmds wr_cmds;
	

	struct read_cmds
	{
	uint8_t lastCmdRxd;
	uint8_t lastCmdStatus;
	uint8_t ID;
	uint8_t config;
	uint8_t status;
	uint8_t motorStatus;
	uint16_t encoderLoc;
	/*
	uint32_t voltage5V;
	uint32_t current5V;
	uint32_t peakCurrent5V;
	uint32_t voltage24V;
	uint32_t current24V;
	uint32_t peakCurrent24V;
	uint32_t voltage400V;		//future
	uint32_t current400V;		//future
	uint32_t peakCurrent400V;	//future

	uint32_t pcbTemp;
	*/
	};

	struct read_cmds rx_cmds;
	struct read_cmds new_rx_cmds;


/* Prototypes */
void sys_config(void);

void configure_extint_channel(void);
void configure_extint_callbacks(void);
void extint_detection_callback(void);


#endif /* PERIPHERALS_H_ */