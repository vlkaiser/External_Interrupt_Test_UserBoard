/*
 * Sercom.h
 *
 * Created: 1/31/2020 9:16:43 AM
 *  Author: VKaiser
 */ 


#ifndef SERCOM_H_
#define SERCOM_H_

#include "main.h"


 /*
  * Global Variables
  */
#define MAX_RX_BUFFER_LENGTH	256
#define I2C_SLAVE_ADDRESS		0x18
#define I2C_DATA_LENGTH			10
#define I2C_TIMEOUT				10

__vo uint8_t rx_buffer[MAX_RX_BUFFER_LENGTH];

struct i2c_master_module i2c_master_instance; 
struct i2c_master_config config_i2c_master;
struct i2c_master_packet write_packet;
struct i2c_master_packet read_packet;

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



void configure_i2c_master(void);
void i2c_write_complete_callback(struct i2c_master_module *const module);
void i2c_read_complete_callback(struct i2c_master_module *const module);
void configure_i2c_callbacks(void);
/*
int8_t i2c_slWrite(uint8_t i2c_addr, uint8_t *write_buffer, uint8_t len);
int8_t i2c_slRead(uint8_t i2c_addr, uint8_t *read_buffer, uint8_t len);
*/
int8_t i2c_Write(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *write_buffer, uint8_t len);
int8_t i2c_Read(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *read_buffer, uint8_t len);

int8_t i2c_slWriteA(uint8_t i2c_addr, uint8_t *write_buffer, uint8_t len);
int8_t i2c_slReadA(uint8_t i2c_addr, uint8_t *read_buffer, uint8_t len);



#endif /* SERCOM_H_ */