/* 
 * Copyright (c) 1991 NeXT Computer, Inc.
 *
 * HISTORY
 * 14-May-90  Gregg Kellogg (gk) at NeXT
 *	Created.
 *
 */

/*
 *  NOTE:
 *
 *	This file specifies obsolete API.  It is provided for compatibility
 *	only.
 */

#ifndef _KERN_INTERNAL_US_TIMER_H
#define	_KERN_INTERNAL_US_TIMER_H

#import <mach/boolean.h>
#import <sys/time.h>
#import <mach/mach_types.h>
#import <kernserv/ns_timer.h>

#if	KERNEL
void us_timer_init(void);
void us_timeout(func proc, vm_address_t arg, struct timeval *tvp, int pri);
void us_abstimeout(func proc, vm_address_t arg, struct timeval *tvp, int pri);
boolean_t us_untimeout(func proc, vm_address_t arg);
void microtime(struct timeval * tvp);
void microboot(struct timeval * tvp);
void delay(unsigned int n);
void us_delay(unsigned usecs);
#endif	KERNEL
#endif	_KERN_INTERNAL_US_TIMER_H
