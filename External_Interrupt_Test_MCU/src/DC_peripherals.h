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

#ifdef XPLAINED_PRO
	void configure_extint_channel(void);
#endif

void configure_extint_callbacks(void);
void extint_detection_callback(void);

void extint_detection_callback_estop(void);








#endif /* PERIPHERALS_H_ */