/* 	Copyright (c) 1991 NeXT Computer, Inc.  All rights reserved. 
 *
 * generalFuncs.h - General purpose driverkit functions.
 *
 * HISTORY
 * 18-Apr-91    Doug Mitchell at NeXT
 *      Created. 
 */
 
#import <mach/mach_types.h>
#import <driverkit/return.h>
#import <kernserv/clock_timer.h>
#import <driverkit/driverTypes.h>

/*
 * These are opaque to the user.
 */
typedef void  *IOThread;
typedef void (*IOThreadFunc)(void *arg);

/*
 * Memory allocation functions. Both may block.
 */
void *IOMalloc(int size);
void IOFree(void *p, int size);

/*
 * Memory copy
 */
void IOCopyMemory(void *from, void *to, unsigned int numBytes, 
	unsigned int bytesPerTransfer);
 
/*
 * Thread and task functions.
 */
/*
 * Start a new thread starting execution at fcn with argument arg.
 */
IOThread IOForkThread(IOThreadFunc fcn, void *arg);

/*
 * Alter the scheduler priority of a thread started with IOForkThread().
 */
IOReturn IOSetThreadPriority(IOThread thread, int priority);

IOReturn IOSetThreadPolicy(IOThread thread, int policy);

/*
 * Suspend a thread started with IOForkThread().
 */
void IOSuspendThread(IOThread thread);

/*
 * Resume a thread started by IOForkThread().
 */
void IOResumeThread(IOThread thread);

/*
 * Terminate exceution of current thread. Does not return.
 */
volatile void IOExitThread();

/*
 * Sleep for indicated number of milliseconds.
 */
void IOSleep(unsigned milliseconds);

/*
 * Spin for indicated number of microseconds.
 */
void IODelay(unsigned microseconds);

/*
 * Call function fcn with argument arg in specified number of seconds.
 * WARNING: The kernel version of this function does the callback in
 * 	    the kernel task's context, not the IOTask context.
 */
void IOScheduleFunc(IOThreadFunc fcn, void *arg, int seconds);

/*
 * Cancel callout requested in IOScheduleFunc().
 */
void IOUnscheduleFunc(IOThreadFunc fcn, void *arg);

/*
 * Obtain current time in ns.
 */
void IOGetTimestamp(ns_time_t *nsp);

/*
 * Log a printf-style string to console.
 */
void IOLog(const char *format, ...)
__attribute__((format(printf, 1, 2)));

/*
 * Panic (if in the kernel) or dump core (if user space).
 * FIXME - this should be a volatile, but panic() isn't...
 */
void IOPanic(const char *reason);

/*
 * Convert a integer constant (typically a #define or enum) to a string
 * via an array of IONamedValue.
 */
const char *IOFindNameForValue(int value, 
	const IONamedValue *namedValueArray);

/*
 * Convert a string to an int via an array of IONamedValue. Returns
 * IO_R_SUCCESS of string found, else returns IO_R_INVALIDARG.
 */
IOReturn IOFindValueForName(const char *string, 
	const IONamedValue *regValueArray,
	int *value);				/* RETURNED */

/*
 * Transfer control to the debugger.
 */
 
void IOBreakToDebugger(void);

/*
 * Convert between size and a power-of-two alignment.
 */
IOAlignment IOSizeToAlignment(unsigned int size);
unsigned int IOAlignmentToSize(IOAlignment align);

/*
 * One-time only init for this module.
 */
void IOInitGeneralFuncs();
