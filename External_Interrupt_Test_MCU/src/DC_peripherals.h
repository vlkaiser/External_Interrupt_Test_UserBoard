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

void configure_extint_channel(void);
void configure_extint_callbacks(void);
void extint_detection_callback(void);


#endif /* PERIPHERALS_H_ */