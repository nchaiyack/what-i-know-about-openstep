/*
 *	File:	<midi/midi_driver.h>
 *	Author:	David Jaffe
 *	Copyright (C) 1991, NeXT Computer, Inc.
 *
 *      MIDI driver typedefs, defines, and functions
 */


#ifndef _MIDI_DRIVER_
#define _MIDI_DRIVER_

#import <mach/kern_return.h>
#import <mach/message.h>
#import <mach/port.h>

/* Each event consists of a byte and a time stamp. */
typedef struct {
    int time;             /* Absolute time in quanta */
    unsigned char byte;   /* The byte */
} MIDIRawEvent;

/* MIDI_MAX_EVENT is the maximum number of events that can be
 * sent to or received from the driver in a single package. 
 */
#define MIDI_MAX_EVENT 100
   
/* MIDI_MAX_MSG_SIZE is the maximum size of the message you
 * can receive from the driver. 
 */
#define MIDI_MAX_MSG_SIZE 1024  // More than enough

/* Clock modes */
#define MIDI_CLOCK_MODE_INTERNAL 0
#define MIDI_CLOCK_MODE_MTC_SYNC 1

/* error codes */
#define MIDI_ERROR_BUSY 100
#define MIDI_ERROR_NOT_OWNER 101
#define MIDI_ERROR_QUEUE_FULL 102
#define MIDI_ERROR_BAD_MODE 103
#define MIDI_ERROR_UNIT_UNAVAILABLE 104
#define MIDI_ERROR_ILLEGAL_OPERATION 105
#define MIDI_ERROR_UNKNOWN_ERROR 106

/* exception codes */
#define MIDI_EXCEPTION_MTC_STOPPED 1
#define MIDI_EXCEPTION_MTC_STARTED_FORWARD 2
#define MIDI_EXCEPTION_MTC_STARTED_REVERSE 3

/* Defines for system ignores. */
#define MIDI_IGNORE_CLOCK	 0x0100
#define MIDI_IGNORE_START	 0x0400
#define MIDI_IGNORE_CONTINUE	 0x0800
#define MIDI_IGNORE_STOP	 0x1000
#define MIDI_IGNORE_ACTIVE	 0x4000
#define MIDI_IGNORE_RESET	 0x8000
#define MIDI_IGNORE_REAL_TIME    0xdd00  /* All of the above */

#define MIDI_PORT_A_UNIT 0
#define MIDI_PORT_B_UNIT 1

/* Reply function types. */
typedef void (*MIDIDataReplyFunction)
    (port_t replyPort, short unit, MIDIRawEvent *events, unsigned int count);
typedef void (*MIDIAlarmReplyFunction)
    (port_t replyPort, int requestedTime, int actualTime);
typedef void (*MIDIExceptionReplyFunction)
    (port_t replyPort, int exception);
typedef void (*MIDIQueueReplyFunction)
    (port_t replyPort, short unit);

/* Struct for passing reply functions to mididriver library. */
typedef struct _MIDIReplyFunctions {
    MIDIDataReplyFunction dataReply;
    MIDIAlarmReplyFunction alarmReply;
    MIDIExceptionReplyFunction exceptionReply;
    MIDIQueueReplyFunction queueReply;
} MIDIReplyFunctions;

/******* Managing ownership of the driver ********/
extern kern_return_t 
    MIDIBecomeOwner(port_t driver, port_t owner);
extern kern_return_t 
    MIDIReleaseOwnership(port_t driver, port_t owner);

/*** Claiming a particular serial port (ownership of driver required) *****/
extern kern_return_t 
    MIDIClaimUnit(port_t driver, port_t owner, short unit);
extern kern_return_t 
    MIDIReleaseUnit(port_t driver, port_t owner, short unit);

/******** Controlling the clock ****************/
extern kern_return_t 
    MIDISetClockMode(port_t driver, port_t owner, short synchUnit, int mode);
extern kern_return_t 
    MIDISetClockQuantum(port_t driver, port_t owner, int microseconds);
extern kern_return_t 
    MIDISetClockTime(port_t driver, port_t owner, int time);
extern kern_return_t 
    MIDIGetClockTime(port_t driver, port_t owner, int *time);
extern kern_return_t 
    MIDIGetMTCTime(port_t driver, port_t owner, short *format, short *hours, short *minutes, short *seconds, short *frames);
extern kern_return_t 
    MIDIStartClock(port_t driver, port_t owner);
extern kern_return_t 
    MIDIStopClock(port_t driver, port_t owner);

/****************** Requesting asynchronous messages *******************/
extern kern_return_t 
    MIDIRequestData(port_t driver, port_t owner, short unit, port_t replyPort);
extern kern_return_t 
    MIDIRequestAlarm(port_t driver, port_t owner, port_t replyPort, int time);
extern kern_return_t 
    MIDIRequestExceptions(port_t driver, port_t owner, port_t exceptionPort);
extern kern_return_t 
    MIDIRequestQueueNotification(port_t driver, port_t owner, short unit, port_t notificationPort, int size);

/****************** Receiving asynchronous messages *******************/
extern kern_return_t 
    MIDIAwaitReply(port_t ports, MIDIReplyFunctions *funcs, int timeout);

#define MIDI_NO_TIMEOUT (-1)

extern kern_return_t 
    MIDIHandleReply(msg_header_t *msg,MIDIReplyFunctions *funcs);

/****************** Writing MIDI data to the driver *********************/
extern kern_return_t 
    MIDISendData(port_t driver, port_t owner, short unit, MIDIRawEvent *data, unsigned int count);
extern kern_return_t 
    MIDIGetAvailableQueueSize(port_t driver, port_t owner, short unit, int *size);
extern kern_return_t 
    MIDIClearQueue(port_t driver, port_t owner, short unit);
extern kern_return_t 
    MIDIFlushQueue(port_t device_port, port_name_t owner_port, short unit);

/********************* Filtering MIDI system real time messages. *************/
extern kern_return_t 
    MIDISetSystemIgnores(port_t driver, port_t owner, short unit, unsigned int ignoreBits);

#endif _MIDI_DRIVER_
