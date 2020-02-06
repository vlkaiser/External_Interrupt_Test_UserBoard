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
* - Special Setup -					: +2kohm pullups on SDA and SCL (on XPLAINED boards)

*  Header files for all drivers that have been imported from Atmel Software Framework (ASF).
*  Use in conjunction with			: SAMD20 Xplained Pro
*  Wiring Details					: PA08, PA09
* Revision History					:
* 	Date				Author			Notes
* 						vkaiser			- Initial commit
*  Never define (implement) variables or functions in header files!
***************************************************************************************************************************/
#include <main.h>

/* GLOBALS */
bool isNewData;

/******* TEMPERATURE SENSOR TEST ********/
	uint8_t sensorADDR = 0x18;
	uint8_t cfgReg = 0x01;
	uint8_t	wr_buffer[1] = {0xE0};
	uint8_t rd_buffer[2] = {0xAA};

	 
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
	sys_config();	int debounce = 100;	bool pwrState = FALSE;	while (1)
	{
		/* Poll for other button presses - safer than interrupts since the Daughter Card really doesn't do anything else */

		// No Power:
		if(pwrState == FALSE)
		{
			// Only action available is to power up
			if (port_pin_get_input_level(BUTTON_PWR_PIN) == 0)
			{
				bool button_pin_state = port_pin_get_input_level(BUTTON_PWR_PIN);
				button_pin_state = !button_pin_state;

				port_pin_set_output_level(LED_PWR_RED_PIN, FALSE);
				port_pin_set_output_level(LED_PWR_GREEN_PIN, TRUE);

				pwrState = TRUE;
				delay_ms(debounce);
			}
		}
		// Power:
		else
		{
			// Measure:
			if (port_pin_get_input_level(BUTTON_MEAS_PIN) == 0)
			{
				
				if (pwrState == TRUE)
				{
					bool button_pin_state = port_pin_get_input_level(BUTTON_MEAS_PIN);
					button_pin_state = !button_pin_state;

					port_pin_set_output_level(LED_MEAS_WHITE_PIN, TRUE);

					delay_ms(500);
					port_pin_set_output_level(LED_MEAS_WHITE_PIN, FALSE);
					
					delay_ms(debounce);
				}
			}

			// Power Off:
			if (port_pin_get_input_level(BUTTON_PWR_PIN) == 0)
			{

				bool button_pin_state = port_pin_get_input_level(BUTTON_PWR_PIN);
				button_pin_state = !button_pin_state;

				port_pin_set_output_level(LED_PWR_RED_PIN, TRUE);
				port_pin_set_output_level(LED_PWR_GREEN_PIN, FALSE);

				pwrState = FALSE;

				delay_ms(debounce);
			}



		}

		//delay_ms(10);
		//state machine to process data?

	/*
		i2c_Write(sensorADDR, cfgReg, wr_buffer, 1);
		delay_ms(100);
		sensorRead(rd_buffer);
		delay_ms(100);
	*/
		//i2c_slWrite(slaveADDR, slwr_buffer, DATA_LENGTH);				//i2c_read_request_callback
		//delay_ms(100);

	}
}