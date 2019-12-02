/*
 * Basic External Interrupt (SW0) to turn on LED (LED0) 
 * SAMD20J18 USERBOARD new project
 */
#include <asf.h>

void configure_extint_channel(void);

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

int main (void)
{
	system_init();
	configure_extint_channel();	
	while (1)
	{

		if (extint_chan_is_detected(BUTTON_0_EIC_LINE)) {
			// Do something in response to EXTINT edge detection
			
			bool button_pin_state = port_pin_get_input_level(BUTTON_0_PIN);
			port_pin_set_output_level(LED_0_PIN, button_pin_state);
			extint_chan_clear_detected(BUTTON_0_EIC_LINE);
		}

	}
}