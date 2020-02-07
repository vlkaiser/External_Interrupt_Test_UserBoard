/*
 * TypeDefs.h
 *
 * Created: 1/31/2020 9:43:52 AM
 *  Author: VKaiser
 */ 


#ifndef TYPEDEFS_H_
#define TYPEDEFS_H_

#define __vo		volatile

#define UINT8   	unsigned char
#define UINT16   	unsigned short
#define UINT32   	unsigned long

#define INT8   		signed char
#define INT16   	signed short
#define INT32   	signed long

#define	BOOL		UINT8

#define	TRUE		1
#define FALSE		0

#define	SET			ENABLE
#define RESET		DISABLE

/***** Command ID Abstractions *****/

// Commands Sent: cmdID
#define PWR_UP		0xAA
#define PWR_DWN		0x66
#define MEAS_ST		0x10
#define ESTP		0xFF

// Commands Sent: encLocMoveTo //
#define posHome		0xACCE55ED
#define posEnd		0x0B501E7E
#define posStart	0xFEEDFEED
#define posSTOP		0xDECEA5ED

/********** Command Response **********/
//cmd Status
#define dWAIT		0xBE
#define dRDY		0x60

//cmd encoderloc
#define endPwrUp	0x1D1D1700
#define endPwrDown	0x11223344
#define endMeas		0x88AA88EE
#define endESTOP	0xDEADDEAD

//Commands Received:

// encoderLoc
// voltage5V
// current5V
// peakCurrent5V
// voltage24V
// current24V
// peakCurrent24V
// voltage400V
// current400V
// peakCurrent400V
// pcbTemp
// lastCmdRxd
// lastCmdStatus

// ID
#define		motorX		0xA1
#define		motorY		0xB1
#define		motorZ		0xC1

// config

// status
#define	motorRDY	0x01
#define	motorBSY	0x00

// motorStatus

/**************************************/


#endif /* TYPEDEFS_H_ */