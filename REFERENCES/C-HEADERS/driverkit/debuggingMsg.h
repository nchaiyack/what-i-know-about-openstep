/* 	Copyright (c) 1991 NeXT Computer, Inc.  All rights reserved. 
 *
 * debuggingMsg.h - exported interface to driver debugging module (DDM) 
 *		  server. This interface is used by Apps like Viewers 
 *		  and other modules which must collect and/or analyze 
 *		  DDM data (as opposed to those modules which generate 
 *		  DDM data).
 *
 * HISTORY
 * 22-Feb-91    Doug Mitchell at NeXT
 *      Created. 
 */

#import <mach/message.h>
#import <kernserv/clock_timer.h>

/*
 * Message format for communicating with DDM server.
 */
#define IO_DDM_STRING_LENGTH	128

typedef struct {
	msg_header_t 	header;			// standard header 
	msg_type_t	argType;		// describes args
	unsigned	index;			// index into 
						// IODebuggingMasks[] or
						// actual log array 
	unsigned	maskValue;	
	unsigned	status;			// I/O result
	
	/*
	 * TBD - can't pass long longs in mach message (yet).
	 * As of 30 Nov. 92, all IODebuggingMsg's contain 32 bits of
	 * microseconds in timestampLowInt, stored big-endian.
	 */
	unsigned	timestampHighInt;
	unsigned	timestampLowInt;
	int		cpuNumber;
	msg_type_t	stringType;		// describes string
	char		string[IO_DDM_STRING_LENGTH];
} IODDMMsg;

/*
 * Values for IODebuggingMsg.header.msg_id.
 */
#define IO_DDM_MSG_BASE			0x545454
#define IO_LOCK_DDM_MSG			(IO_DDM_MSG_BASE + 0)	
					// freeze state of DDM
#define IO_UNLOCK_DDM_MSG		(IO_DDM_MSG_BASE + 1)	
					// unfreeze state of DDM
#define IO_GET_DDM_ENTRY_MSG		(IO_DDM_MSG_BASE + 2)	
					// get a DDM string 
#define IO_SET_DDM_MASK_MSG		(IO_DDM_MSG_BASE + 3)	
					// set IODDMMasks
#define IO_CLEAR_DDM_MSG		(IO_DDM_MSG_BASE + 4)	
					// clear DDM log
							
/*
 * Values for IODebuggingMsg.status.
 */
#define IO_DDM_SUCCESS		0
#define IO_NO_DDM_BUFFER	1		// no entry at specified
						// 	offset
#define IO_BAD_DDM_INDEX	2		// invalid index

/*
 * Extract an unsigned long long from msg->timestampHighInt and
 * msg.timestampLowInt.
 */
static inline ns_time_t IONsTimeFromDDMMsg(IODDMMsg *msg)
{
	ns_time_t ns;
	
	ns = ((unsigned long long)(msg->timestampHighInt)) << 32;
	ns += msg->timestampLowInt;
	return ns;
}

