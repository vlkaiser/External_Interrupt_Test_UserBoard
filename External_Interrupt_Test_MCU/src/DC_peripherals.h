/*
 * Peripherals.h
 *
 * Created: 1/30/2020 6:16:20 PM
 *  Author: VKaiser
 */ 


#ifndef PERIPHERALS_H_
#define PERIPHERALS_H_

#include "main.h"

/* Prototypes */
void sys_config(void);

void IOPanel_Powerup(void);
void config_IO_Panel(void);

void configure_extint_EStop(void);

void configure_extint_channel(void);
void configure_extint_callbacks(void);
void extint_detection_callback(void);

void extint_detection_callback_estop(void);



/* the Data Packing of these structs mean that uint32s should come before uint8s or bytes could be lost */
 /**********************************************************************
 * @struct				- write_cmds [motor_Cmd]
 * @brief				- Command status structure to Motor controller boards
 *
 * @param[in]			- N/A
 * @return				- void
 *
 * @note				- Initialization
 **********************************************************************/
	struct write_cmds
	{
		uint32_t encLocMoveTo;
		uint8_t cmdID;
		
	};
	struct write_cmds wr_cmds;

/**********************************************************************
 * @struct				- read_cmds [motorAxis]
 * @brief				- Status message structure for communicating with
 *						- Motor controller boards
 *
 * @param[in]			- N/A
 * @return				- void
 *
 * @note				- Initialization
 **********************************************************************/	
	struct read_cmds
	{
		uint32_t encoderLoc;	
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

		uint8_t lastCmdRxd;
		uint8_t lastCmdStatus;
		uint8_t ID;
		uint8_t config;
		uint8_t status;
		uint8_t motorStatus;
	};

	struct read_cmds rx_cmds;
	struct read_cmds new_rx_cmds;




#endif /* PERIPHERALS_H_ */