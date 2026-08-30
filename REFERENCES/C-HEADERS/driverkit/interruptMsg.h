/* 	Copyright (c) 1991 NeXT Computer, Inc.  All rights reserved. 
 *
 * interruptMsg.h - Interrupt message defintion.
 *
 * HISTORY
 * 04-Apr-91    Doug Mitchell at NeXT
 *      Created. 
 */

#import <mach/message.h>

/*
 * Interrupt message sent by kernel to device-specific handler.
 */
typedef struct {

	msg_header_t	header;		// standard message header 
	
} IOInterruptMsg;

/*
 * Values for IOInterruptMsg.header.
 */
#define IO_INTERRUPT_MSG_ID_BASE	0x232323

#define IO_TIMEOUT_MSG			(IO_INTERRUPT_MSG_ID_BASE + 0)
#define IO_COMMAND_MSG			(IO_INTERRUPT_MSG_ID_BASE + 1)
/*
 * Next 16 reserved for multiple interrupt sources per device.
 */
#define IO_DEVICE_INTERRUPT_MSG		(IO_INTERRUPT_MSG_ID_BASE + 2)
#define IO_DEVICE_INTERRUPT_MSG_FIRST	(IO_DEVICE_INTERRUPT_MSG)
#define IO_DEVICE_INTERRUPT_MSG_LAST	(IO_DEVICE_INTERRUPT_MSG_FIRST + 15)
#define IO_DMA_INTERRUPT_MSG		(IO_DEVICE_INTERRUPT_MSG_LAST + 1)
#define IO_FIRST_UNRESERVED_INTERRUPT_MSG	\
					(IO_DMA_INTERRUPT_MSG + 1)
