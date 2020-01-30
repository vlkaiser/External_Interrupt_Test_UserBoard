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
#include <Peripherals.h>

/* GLOBALS */

/* Prototypes */


 /******************************************************************************************************
 * @fn					- 
 * @brief				- 
 * @param[in]			- void
 * @return				- void
 *
 * @note				- 
 ******************************************************************************************************/

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

	}
}