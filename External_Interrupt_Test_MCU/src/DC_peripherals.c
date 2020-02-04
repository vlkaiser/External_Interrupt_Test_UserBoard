/*
 * Peripheral.c
 *
 * Created: 1/30/2020 6:13:43 PM
 *  Author: VKaiser
 */ 
#include <DC_peripherals.h>

/*********** SLAVE MCU TEST ************/
	//uint8_t slaveADDR = 0x1A;
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
 * @fn					- configure_extint_channel
 * @brief				- Configure button0 as external interrupt
 * @param[in]			- void
 * @return				- void
 *
 * @note				- 
 ******************************************************************************************************/
void configure_extint_channel(void)
{
	struct extint_chan_conf config_extint_chan;
	extint_chan_get_config_defaults(&config_extint_chan);
	
	config_extint_chan.gpio_pin = BUTTON_0_EIC_PIN;
	config_extint_chan.gpio_pin_mux = BUTTON_0_EIC_MUX;
	config_extint_chan.gpio_pin_pull = EXTINT_PULL_UP;
	config_extint_chan.detection_criteria = EXTINT_DETECT_RISING;
	
	extint_chan_set_config(BUTTON_0_EIC_LINE, &config_extint_chan);
}
/******************************************************************************************************
 * @fn					- configure_extint_callbacks
 * @brief				- Link external interrupt to callback routine
 * @param[in]			- void
 * @return				- void
 *
 * @note				- 
 ******************************************************************************************************/
void configure_extint_callbacks(void)
{
	extint_register_callback(extint_detection_callback, BUTTON_0_EIC_LINE, EXTINT_CALLBACK_TYPE_DETECT);
	extint_chan_enable_callback(BUTTON_0_EIC_LINE, EXTINT_CALLBACK_TYPE_DETECT);
}

/******************************************************************************************************
 * @fn					- extint_detection_callback
 * @brief				- Callback routine triggered on interrupt
 * @param[in]			- void
 * @return				- void
 *
 * @note				- 
 ******************************************************************************************************/
void extint_detection_callback(void)
{
	delay_ms(10);
	bool button_pin_state = port_pin_get_input_level(BUTTON_0_PIN);
	port_pin_set_output_level(LED_0_PIN, button_pin_state);
	
	i2c_slWrite(I2C_SLAVE_ADDRESS, (uint8_t *)&wr_cmds, sizeof(wr_cmds));	//i2c_read_request_callback
	//delay_ms(100);
	//i2c_Read(slaveADDR, slcfgReg, slrd_buffer, DATA_LENGTH);		//i2c_write_request_callback
	//i2c_Read(I2C_SLAVE_ADDRESS, slcfgReg, (uint8_t *)&rx_cmds, sizeof(rx_cmds));		//i2c_write_request_callback
	//i2c_slRead(slaveADDR, slrd_buffer, DATA_LENGTH);				//i2c_write_request_callback

	i2c_slRead(I2C_SLAVE_ADDRESS, (uint8_t *)&rx_cmds, sizeof(rx_cmds));				//i2c_write_request_callback
			
 }

  /******************************************************************************************************
 * @fn					- SysTick_Handler
 * @brief				- SysTick handler interrupt override
 * @param[in]			- void
 * @return				- void
 *
 * @note				- 
 ******************************************************************************************************/
void SysTick_Handler(void)
{
	// Your code goes here
}


 /******************************************************************************************************
 * @fn					- sys_config
 * @brief				- Calls all the config functions (called from main.c)
 * @param[in]			- void
 * @return				- void
 *
 * @note				- 
 ******************************************************************************************************/
void sys_config(void)
{

 	configure_extint_channel(); 	configure_extint_callbacks();
 	system_interrupt_enable_global();

	configure_i2c_master();

		wr_cmds.cmdID = 0xFF;
		wr_cmds.encLocMoveTo = 0xA1A2A3A4;		// little endian

}