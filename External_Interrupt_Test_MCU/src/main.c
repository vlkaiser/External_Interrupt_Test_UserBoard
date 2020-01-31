 /******************************************************************************************************
 * @fn					- 
 * @brief				- 
 * @param[in]			- void
 * @return				- void
 *
 * @note				- 
 ******************************************************************************************************/

/***************************************************************************************************************************
* Project							: SAMD20 Xplained I2C Master
* Program Name						:
* Author							: vkaiser
* Date Created						: Jan 29 2020
*
* Purpose							: Develop I2C on userboard (I2c Callback ASF)
*
*
* MCU								: ATSAMD20J18
* Language							: C
* Hardware Modifications			: N/A
* Debugger							: EDBG (On-board)
*
* Repo / Revision History			: https://github.com/vlkaiser/
*
* - Special Setup -
*  Header files for all drivers that have been imported from Atmel Software Framework (ASF).
*  Use in conjunction with			: SAMD20 Xplained Pro
*  Wiring Details					: PA08, PA09
* Revision History					:
* 	Date				Author			Notes
* 						vkaiser			- Initial commit
*
***************************************************************************************************************************/
#include <asf.h>
#include <main.h>

/* GLOBALS */

/* Prototypes */

/******* TEMPERATURE SENSOR TEST ********/
	uint8_t sensorADDR = 0x18;
	uint8_t cfgReg = 0x01;
	uint8_t	wr_buffer[1] = {0xE0};
	uint8_t rd_buffer[2] = {0xAA};

	 void sensorRead(uint8_t* rd_buf);
/***************************************/

/*********** SLAVE MCU TEST ************/
	uint8_t slaveADDR = 0x1A;
	uint8_t slcfgReg = 0x0;
	/*
	#define DATA_LENGTH 10
	uint8_t	slwr_buffer[DATA_LENGTH] = {0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0xBA, 0xBB, 0xBC, 0xBD };
	*/
	#define DATA_LENGTH	5	
	uint8_t	slwr_buffer[DATA_LENGTH] = {0x5A, 0x5B, 0x5C, 0x5D, 0x5E };
	uint8_t slrd_buffer[DATA_LENGTH];
	
/***************************************/

 /******************************************************************************************************
 * @fn					- sensorRead
 * @brief				- 
 * @param[in]			- uint8_t* rd_buf
 * @return				- void
 *
 * @note				- 
 ******************************************************************************************************/
 void sensorRead(uint8_t* rd_buf)
 {
	 //uint8_t sensorADDR = 0x18;
	 uint8_t mfgIDReg = 0x06;

	 i2c_Read(sensorADDR, mfgIDReg, rd_buf, 2);	//expected 0x0054

 }


/******************************************************************************************************
 * @fn					- main
 * @brief				- 
 * @param[in]			- void
 * @return				- void
 *
 * @note				- MCU specific definitions in (src->common2->boards) -> user_board.h, init routines in init.c
 *	                    - Peripheral config in Peripherals.c (src)
 *						- EXTINT will fire callback asynchronously. (Button0 press -> interrupt callback -> LED0 toggle)
 ******************************************************************************************************/
int main (void)
{
	system_init();
	sys_config();

	while (1)
	{
	
		i2c_Write(sensorADDR, cfgReg, wr_buffer, 1);
		delay_ms(100);
		sensorRead(rd_buffer);
		delay_ms(100);

		i2c_slWrite(slaveADDR, slwr_buffer, DATA_LENGTH);			//i2c_read_request_callback
		//Missing ACK on WRITE
		
		delay_ms(100);
		i2c_Read(slaveADDR, slcfgReg, slrd_buffer, DATA_LENGTH);		//i2c_write_request_callback
		//SUCCESSFUL READ
		
		delay_ms(100);
	
	}
}