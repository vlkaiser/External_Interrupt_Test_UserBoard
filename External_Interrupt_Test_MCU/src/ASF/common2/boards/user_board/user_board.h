/**
 * \file
 *
 * \brief User board definition template
 *
 */

 /* This file is intended to contain definitions and configuration details for
 * features and devices that are available on the board, e.g., frequency and
 * startup time for an external crystal, external memory devices, LED and USART
 * pins.
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef USER_BOARD_H
#define USER_BOARD_H

#include <conf_board.h>
#include <compiler.h>

#ifdef __cplusplus
extern "C" {
#endif
/**
 * \ingroup group_common_boards
 * \defgroup samd20_xplained_pro_group SAM D20 Xplained Pro board
 *
 * @{
 */

void system_board_init(void);

/**
 * \defgroup samd20_xplained_pro_features_group Features
 *
 * Symbols that describe features and capabilities of the board.
 *
 * @{
 */

/** Name string macro */
#define BOARD_NAME                "SAMD20_XPLAINED_PRO"
#define ROBOT_SCAN	1
//#define XPLAINED_PRO	1

#ifdef ROBOT_SCAN

/** \name Resonator definitions *  @{ */
	#define BOARD_FREQ_SLCK_XTAL      (32768U)
	#define BOARD_FREQ_SLCK_BYPASS    (32768U)
	#define BOARD_FREQ_MAINCK_XTAL    0 /* Not Mounted */
	#define BOARD_FREQ_MAINCK_BYPASS  0 /* Not Mounted */
	#define BOARD_MCK                 CHIP_FREQ_CPU_MAX
	#define BOARD_OSC_STARTUP_US      15625
	/** @} */

	#define LED_MCU_GREEN				PIN_PA19
	#define LED_MCU_ORANGE				PIN_PA18

	#define LED_PWR_RED_PIN				PIN_PA05
	#define LED_PWR_GREEN_PIN			PIN_PA06
	#define LED_MEAS_WHITE_PIN			PIN_PB14
	#define LED_STOP_RED_PIN			PIN_PB15

/** Number of on-board LEDs */
	#define LED_COUNT                 4

	#define PB_PWR_PIN					PIN_PB00
	//#define PB_PWR_EIC_PIN				PIN_PB00A_EIC_EXTINT0
	//#define PB_PWR_EIC_MUX				MUX_PB00A_EIC_EXTINT0
	//#define PB_PWR_EIC_PINMUX			PINMUX_PB00A_EIC_EXTINT0
	//#define PB_PWR_EIC_LINE				00

	#define PB_MEAS_PIN					PIN_PB01
	//#define PB_MEAS_EIC_PIN				PIN_PB01A_EIC_EXTINT1
	//#define PB_MEAS_EIC_MUX				MUX_PB01A_EIC_EXTINT1
	//#define PB_MEAS_EIC_PINMUX			PINMUX_PB01A_EIC_EXTINT1
	//#define PB_MEAS_EIC_LINE			01

	#define PB_ESTOP_PIN				PIN_PB02
	#define PB_ESTOP_EIC_PIN			PIN_PB02A_EIC_EXTINT2
	#define PB_ESTOP_EIC_MUX			MUX_PB02A_EIC_EXTINT2
	#define PB_ESTOP_EIC_PINMUX			PINMUX_PB02A_EIC_EXTINT2
	#define PB_ESTOP_EIC_LINE			02

	/** Number of on-board Buttons */
	#define BUTTON_COUNT 3


	
	//IO Panel Stop, Measure, Power
	//Status LED GN/OR


#endif

#ifdef XPLAINED_PRO
	/** \name Resonator definitions *  @{ */
	#define BOARD_FREQ_SLCK_XTAL      (32768U)
	#define BOARD_FREQ_SLCK_BYPASS    (32768U)
	#define BOARD_FREQ_MAINCK_XTAL    0 /* Not Mounted */
	#define BOARD_FREQ_MAINCK_BYPASS  0 /* Not Mounted */
	#define BOARD_MCK                 CHIP_FREQ_CPU_MAX
	#define BOARD_OSC_STARTUP_US      15625
	/** @} */

	/** \name LED0 definitions  *  @{ */
	#define LED0_PIN                  PIN_PA14
	#define LED0_ACTIVE               false
	#define LED0_INACTIVE             !LED0_ACTIVE
	/** @} */

	/** Number of on-board LEDs */
	#define LED_COUNT                 1
	#define LED0					LED0_PIN
	
	/** \name SW0 definitions *  @{ */
	#define SW0_PIN                   PIN_PA15
	#define SW0_ACTIVE                false
	#define SW0_INACTIVE              !SW0_ACTIVE
	#define SW0_EIC_PIN               PIN_PA15A_EIC_EXTINT15
	#define SW0_EIC_MUX               MUX_PA15A_EIC_EXTINT15
	#define SW0_EIC_PINMUX            PINMUX_PA15A_EIC_EXTINT15
	#define SW0_EIC_LINE              15
	/** @} */

	/** Number of on-board buttons */
	#define BUTTON_COUNT 1

	/**
	 * \name Button #0 definitions
	 *
	 * Wrapper macros for SW0, to ensure common naming across all Xplained Pro
	 * boards.
	 *
	 *  @{ */
	#define BUTTON_0_NAME             "SW0"
	#define BUTTON_0_PIN              SW0_PIN
	#define BUTTON_0_ACTIVE           SW0_ACTIVE
	#define BUTTON_0_INACTIVE         SW0_INACTIVE
	#define BUTTON_0_EIC_PIN          SW0_EIC_PIN
	#define BUTTON_0_EIC_MUX          SW0_EIC_MUX
	#define BUTTON_0_EIC_PINMUX       SW0_EIC_PINMUX
	#define BUTTON_0_EIC_LINE         SW0_EIC_LINE
	/** @} */


	#define LED_PWR_RED_PIN				PIN_PA05
	#define LED_PWR_GREEN_PIN			PIN_PA20
	#define LED_MEAS_WHITE_PIN			PIN_PA21
	#define LED_STOP_RED_PIN			PIN_PB15

	#define PB_PWR_PIN					PIN_PB05
	//#define PB_PWR_EIC_PIN				PIN_PB05A_EIC_EXTINT5
	//#define PB_PWR_EIC_MUX				MUX_PB05A_EIC_EXTINT5
	//#define PB_PWR_EIC_PINMUX			PINMUX_PB05A_EIC_EXTINT5
	//#define PB_PWR_EIC_LINE				05

	#define PB_MEAS_PIN					PIN_PB06
	//#define PB_MEAS_EIC_PIN				PIN_PB06A_EIC_EXTINT6
	//#define PB_MEAS_EIC_MUX				MUX_PB06A_EIC_EXTINT6
	//#define PB_MEAS_EIC_PINMUX			PINMUX_PB06A_EIC_EXTINT6
	//#define PB_MEAS_EIC_LINE			06

	#define PB_ESTOP_PIN				PIN_PB07
	#define PB_ESTOP_EIC_PIN			PIN_PB07A_EIC_EXTINT7
	#define PB_ESTOP_EIC_MUX			MUX_PB07A_EIC_EXTINT7
	#define PB_ESTOP_EIC_PINMUX			PINMUX_PB07A_EIC_EXTINT7
	#define PB_ESTOP_EIC_LINE			07

	/**
	 * \name LED #0 definitions
	 *
	 * Wrapper macros for LED0, to ensure common naming across all Xplained Pro
	 * boards.
	 *
	 *  @{ */
	#define LED_0_NAME                "LED0 (yellow)"
	#define LED_0_PIN                 LED0_PIN
	#define LED_0_ACTIVE              LED0_ACTIVE
	#define LED_0_INACTIVE            LED0_INACTIVE
	#define LED0_GPIO 				  LED0_PIN
	/** @} */

#endif //XPLAINED PRO

/* UNIVERSAL */

#define LED_ACTIVE					TRUE
#define LED_INACTIVE				FALSE

#define PB_ACTIVE					FALSE
#define PB_INACTIVE					!PB_ACTIVE

/* Interrupt Definitions */
#define BUTTON_PWR_PIN				PB_PWR_PIN
#define BUTTON_PWR_EIC_PIN			PB_PWR_EIC_PIN
#define BUTTON_PWR_EIC_MUX			PB_PWR_EIC_MUX
#define BUTTON_PWR_EIC_PINMUX		PB_PWR_EIC_PINMUX
#define BUTTON_PWR_EIC_LINE			PB_PWR_EIC_LINE
/* @ */
#define BUTTON_MEAS_PIN				PB_MEAS_PIN
#define BUTTON_MEAS_EIC_PIN			PB_MEAS_EIC_PIN
#define BUTTON_MEAS_EIC_MUX			PB_MEAS_EIC_MUX
#define BUTTON_MEAS_EIC_PINMUX		PB_MEAS_EIC_PINMUX
#define BUTTON_MEAS_EIC_LINE		PB_MEAS_EIC_LINE
/* @ */
#define BUTTON_ESTOP_PIN			PB_ESTOP_PIN
#define BUTTON_ESTOP_EIC_PIN		PB_ESTOP_EIC_PIN
#define BUTTON_ESTOP_EIC_MUX		PB_ESTOP_EIC_MUX
#define BUTTON_ESTOP_EIC_PINMUX		PB_ESTOP_EIC_PINMUX
#define BUTTON_ESTOP_EIC_LINE		PB_ESTOP_EIC_LINE







/**
 * \brief Turns off the specified LEDs.
 *
 * \param led_gpio LED to turn off (LEDx_GPIO).
 *
 * \note The pins of the specified LEDs are set to GPIO output mode.
 */
#define LED_Off(led_gpio)     port_pin_set_output_level(led_gpio,true)

/**
 * \brief Turns on the specified LEDs.
 *
 * \param led_gpio LED to turn on (LEDx_GPIO).
 *
 * \note The pins of the specified LEDs are set to GPIO output mode.
 */
#define LED_On(led_gpio)      port_pin_set_output_level(led_gpio,false)

/**
 * \brief Toggles the specified LEDs.
 *
 * \param led_gpio LED to toggle (LEDx_GPIO).
 *
 * \note The pins of the specified LEDs are set to GPIO output mode.
 */
#define LED_Toggle(led_gpio)  port_pin_toggle_output_level(led_gpio)

#ifdef __cplusplus
}
#endif

#endif // USER_BOARD_H
