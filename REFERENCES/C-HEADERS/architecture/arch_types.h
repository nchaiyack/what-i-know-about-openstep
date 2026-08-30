/* 	Copyright (c) 1991 NeXT Computer, Inc.  All rights reserved. 
 *
 * arch_types.h - Common machine-description data types.
 *
 * HISTORY
 * 10-Sep-91    Doug Mitchell at NeXT
 *      Created. 
 */

#ifndef	_ARCHITECTURE_ARCH_TYPES_H_
#define _ARCHITECTURE_ARCH_TYPES_H_

/*
 * DMA channel status values.
 */
typedef unsigned char	IOChannelStatus;
typedef unsigned char	IOUserStatus;

/*
 * Two ways of looking at deviceType.
 */
typedef unsigned int	IODeviceType;
typedef unsigned short	IODeviceIndex;
typedef unsigned short 	IODeviceRevision;

typedef struct {
	IODeviceIndex 		deviceIndex;
	IODeviceRevision 	deviceRevision;
} IODeviceTypeIr;

typedef union {
	IODeviceType 		deviceType;
	IODeviceTypeIr 		deviceTypeIr;
} IODeviceTypeUn;


/*
 * Two ways of looking at slot ID.
 */
typedef	unsigned int	IOSlotId;
typedef struct {		
	unsigned short		valid:1,	// 15 
				console:1,	// 14 - should be 0 (?)
				bootDev:1,	// 13 - should be 0 (?)
				rsvd:3,		// 12..10 - must be 0
				blockId:3,	// 9..7
				prodId:7;	// 6..0
} IOSlotIdMfg;

typedef union {
	IOSlotId		slotId;		// all 32 bits
	struct {
		IOSlotIdMfg	mfgId;		// 31..16
		unsigned short 	boardId;	// 15..0
	} slotIdStr;
} IOSlotIdUn;

#endif	_ARCHITECTURE_ARCH_TYPES_H_
