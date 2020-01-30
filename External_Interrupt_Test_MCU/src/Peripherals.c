/*
 * Peripheral.c
 *
 * Created: 1/30/2020 6:13:43 PM
 *  Author: VKaiser
 */ 
 #include "asf.h"
#include <Peripherals.h>

 void SysTick_Handler(void)
 {
	 // Your code goes here
 }

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
	config_extint_chan.detection_criteria = EXTINT_DETECT_BOTH;
	
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
	bool button_pin_state = port_pin_get_input_level(BUTTON_0_PIN);
	port_pin_set_output_level(LED_0_PIN, button_pin_state);
 }

void sys_config(void)
{
 	configure_extint_channel(); 	configure_extint_callbacks();
 	system_interrupt_enable_global();
}