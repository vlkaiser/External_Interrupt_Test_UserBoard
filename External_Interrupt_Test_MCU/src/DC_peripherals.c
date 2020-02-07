/*
 * Peripheral.c
 *
 * Created: 1/30/2020 6:13:43 PM
 *  Author: VKaiser
 */ 
#include <DC_peripherals.h>

/*********** SLAVE MCU TEST ************/
	//uint8_t slaveADDR = 0x1A;
	//uint8_t slcfgReg = 0x0;
	//#define DATA_LENGTH	5	
	//uint8_t	slwr_buffer[DATA_LENGTH] = {0x5A, 0x5B, 0x5C, 0x5D, 0x5E };
	//uint8_t slrd_buffer[DATA_LENGTH];
	
/***************************************/

/******************************************************************************************************
 * @fn					- configure_extint_channel
 * @brief				- Configure button0 as external interrupt
 * @param[in]			- void
 * @return				- void
 *
 * @note				- 
 ******************************************************************************************************/
#ifdef XPLAINED_PRO
void configure_extint_channel(void)
{
	struct extint_chan_conf config_extint_chan;
	extint_chan_get_config_defaults(&config_extint_chan);
	
	config_extint_chan.gpio_pin = BUTTON_0_EIC_PIN;
	config_extint_chan.gpio_pin_mux = BUTTON_0_EIC_MUX;
	config_extint_chan.gpio_pin_pull = EXTINT_PULL_UP;
	config_extint_chan.detection_criteria = EXTINT_DETECT_RISING;
	
	extint_chan_set_config(BUTTON_0_EIC_LINE, &config_extint_chan);
}#endif
/**********************************************************************
 * @fn					- configure_extint_EStop 
 * @brief				- Config EStop PB on NM IO Panel as interrupt
 *
 * @param[in]			- N/A
 * @return				- void
 *
 * @note				- Initialization - configuration
 **********************************************************************/
void configure_extint_EStop(void)
{
	struct extint_chan_conf config_extint_estop;
	extint_chan_get_config_defaults(&config_extint_estop);
	
	config_extint_estop.gpio_pin = BUTTON_ESTOP_PIN;
	config_extint_estop.gpio_pin_mux = BUTTON_ESTOP_EIC_MUX;
	config_extint_estop.gpio_pin_pull = EXTINT_PULL_UP;
	config_extint_estop.detection_criteria = EXTINT_DETECT_FALLING;
	
	extint_chan_set_config(BUTTON_ESTOP_EIC_LINE, &config_extint_estop);
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
	#ifdef XPLAINED_PRO
		extint_register_callback(extint_detection_callback, BUTTON_0_EIC_LINE, EXTINT_CALLBACK_TYPE_DETECT);
		extint_chan_enable_callback(BUTTON_0_EIC_LINE, EXTINT_CALLBACK_TYPE_DETECT);
	#endif

	extint_register_callback(extint_detection_callback_estop, BUTTON_ESTOP_EIC_LINE, EXTINT_CALLBACK_TYPE_DETECT);
	extint_chan_enable_callback(BUTTON_ESTOP_EIC_LINE, EXTINT_CALLBACK_TYPE_DETECT);
}

/******************************************************************************************************
 * @fn					- extint_detection_callback
 * @brief				- Callback routine triggered on interrupt
 * @param[in]			- void
 * @return				- void
 *
 * @note				- 
 ******************************************************************************************************/
#ifdef XPLAINED_PRO
void extint_detection_callback(void)
{
	delay_ms(10);
	bool button_pin_state = port_pin_get_input_level(BUTTON_0_PIN);
	port_pin_set_output_level(LED_0_PIN, button_pin_state);
	
	//i2c_slWriteA(I2C_SLAVE_ADDRESS, (uint8_t *)&wr_cmds, sizeof(wr_cmds));				//i2c_read_request_callback
	//wr_cmds.cmdID = 0xAA;
	//i2c_slReadA(I2C_SLAVE_ADDRESS, (uint8_t *)&rx_cmds, sizeof(rx_cmds));				//i2c_write_request_callback
	
	i2c_slWriteA(I2C_SLAVE_ADDRESS, (uint8_t *)&wr_cmds, sizeof(wr_cmds));				//i2c_read_request_callback
	wr_cmds.cmdID = 0xFF;		
 }
 #endif

/**********************************************************************
 * @fn					- extint_detection_callback_estop
 * @brief				- IO Panel EStop PB Interrupt callback
 *
 * @param[in]			- N/A
 * @return				- void
 *
 * @note				- Interrupt Handler - code executed when interrupt occurs
 **********************************************************************/
void extint_detection_callback_estop(void)
{
	int i = 10;

	bool button_pin_state = port_pin_get_input_level(BUTTON_ESTOP_PIN);
	button_pin_state = !button_pin_state;

	port_pin_set_output_level(LED_STOP_RED_PIN, TRUE);

	// ToDo: Send Emergency Stop 
	wr_cmds.cmdID = ESTP;
	wr_cmds.encLocMoveTo = posSTOP;
	i2c_slWriteA(I2C_SLAVE_ADDRESS, (uint8_t *)&wr_cmds, sizeof(wr_cmds));				//i2c_read_request_callback
	

	while( i > 0 )
	{
		//ESTOP is full stop shutdown for now
		port_pin_toggle_output_level(LED_STOP_RED_PIN);
		delay_ms(100);
		i--;
	}
	clear_wrCMDS();

	do{
	i2c_slReadA(I2C_SLAVE_ADDRESS, (uint8_t *)&rx_cmds, sizeof(rx_cmds));
	delay_ms(500);
	}while(rx_cmds.status != dRDY);
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

/**********************************************************************
 * @fn					- config_IO_LEDS
 * @brief				- Configure Nelson Miller IO Panel Leds
 *
 * @param[in]			- N/A
 * @return				- void
 *
 * @note				- Initialization
 **********************************************************************/
 void config_IO_Panel(void)
 {
	 struct port_config pin_conf;
	 port_get_config_defaults(&pin_conf);

	 //TODO: LED CONFIG

	 pin_conf.direction  = PORT_PIN_DIR_OUTPUT;
	 //pin_conf.input_pull = PORT_PIN_PULL_DOWN;

	 #ifdef ROBOT_BOARD
		 port_pin_set_config(LED_MCU_GREEN, &pin_conf);
		 port_pin_set_output_level(LED_MCU_GREEN, LED_INACTIVE);
		 port_pin_set_output_level(LED_MCU_GREEN, LED_ACTIVE);

		 port_pin_set_config(LED_MCU_ORANGE, &pin_conf);
		 port_pin_set_output_level(LED_MCU_ORANGE, LED_INACTIVE);
	 #endif

	 pin_conf.direction  = PORT_PIN_DIR_OUTPUT;
	 pin_conf.input_pull = PORT_PIN_PULL_DOWN;

	 port_pin_set_config(LED_PWR_GREEN_PIN, &pin_conf);					//yes works with PWR_G TP
	 port_pin_set_output_level(LED_PWR_GREEN_PIN, TRUE );
	  port_pin_set_output_level(LED_PWR_GREEN_PIN, LED_INACTIVE);

	 port_pin_set_config(LED_PWR_RED_PIN, &pin_conf);
	 port_pin_set_output_level(LED_PWR_RED_PIN, LED_ACTIVE);
	 port_pin_set_output_level(LED_PWR_RED_PIN, LED_INACTIVE);

	 port_pin_set_config(LED_MEAS_WHITE_PIN, &pin_conf);
	 port_pin_set_output_level(LED_MEAS_WHITE_PIN, LED_ACTIVE);
	 port_pin_set_output_level(LED_MEAS_WHITE_PIN, LED_INACTIVE);

	 port_pin_set_config(LED_STOP_RED_PIN, &pin_conf);
  	 port_pin_set_output_level(LED_STOP_RED_PIN, LED_ACTIVE);
	 port_pin_set_output_level(LED_STOP_RED_PIN, LED_INACTIVE);

	 pin_conf.direction  = PORT_PIN_DIR_INPUT;
	 pin_conf.input_pull = PORT_PIN_PULL_UP;

	 port_pin_set_config(BUTTON_MEAS_PIN, &pin_conf);
	 port_pin_set_config(BUTTON_PWR_PIN, &pin_conf);

 }

/**********************************************************************
 * @fn					- IOPanel_Powerup
 * @brief				- Sets powerup state of IO panel LEDs
 * @param[in]			- 
 * @return				- void
 *+
 * @note				- 
 **********************************************************************/
void IOPanel_Powerup(void)
{
	#ifdef ROBOT_BOARD
		port_pin_set_output_level(LED_MCU_GREEN, LED_ACTIVE);
	#endif

	port_pin_set_output_level(LED_PWR_RED_PIN, LED_ACTIVE);
	port_pin_set_output_level(LED_PWR_GREEN_PIN, LED_INACTIVE);
	port_pin_set_output_level(LED_MEAS_WHITE_PIN, LED_INACTIVE);
	port_pin_set_output_level(LED_STOP_RED_PIN, LED_INACTIVE);
	delay_ms(500);
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
	config_IO_Panel();

	#ifdef  XPLAINED_PRO
		configure_extint_channel();
	#endif
 	 	configure_extint_callbacks();
 	
	//configure_extint_PWR();	//configure_extint_Measure();	configure_extint_EStop();
	
	system_interrupt_enable_global();

	configure_i2c_master();
	
	IOPanel_Powerup();

		wr_cmds.cmdID = 0xFF;
		wr_cmds.encLocMoveTo = 0xA1A2A3A4;		// little endian

}