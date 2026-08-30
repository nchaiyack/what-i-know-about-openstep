/* 
 * Copyright (c) 1990 NeXT, Inc.
 *
 * HISTORY
 * 21-May-91  Gregg Kellogg (gk) at NeXT
 *	Separated into public and private parts.
 *
 * 22-Jan-90  Gregg Kellogg (gk) at NeXT
 *	Created
 */ 

#ifndef	_M68K_AUTOCONF_H_
#define	_M68K_AUTOCONF_H_

/*
 * Setup the system to run on the current machine.
 *
 * Configure() is called at boot time and initializes the bus device tables.
 * Available devices are determined (from possibilities mentioned
 * in ioconf.c), and the drivers are initialized.
 */

#import <sys/types.h>
#import <mach/mach_types.h>


int install_polled_intr (int which, int (*intr)());
int install_scanned_intr (int which, int (*intr)(), void *arg);
int uninstall_polled_intr(int which, int (*intr)());
int uninstall_scanned_intr(int which);
caddr_t map_addr(register caddr_t addr, int size);
caddr_t ioaccess (vm_offset_t phys, vm_offset_t virt, vm_size_t size);

#endif	_M68K_AUTOCONF_H_
