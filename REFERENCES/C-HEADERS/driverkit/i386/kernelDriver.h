/* 	Copyright (c) 1991 NeXT Computer, Inc.  All rights reserved. 
 *
 * i386/kernelDriver.h - i386 kernel-only driverkit functions.
 *
 * HISTORY
 * 1-Apr-93    Doug Mitchell at NeXT
 *      Created. 
 */

#ifdef	KERNEL

/*
 * Allocate memory guranteed to be in the low 16 megabytes of physical 
 * memory. Used when performing DMA which must deal with only 24 bits 
 * of address.
 *
 * Zero will also be returned if no low memory can be allocated. 
 *
 * Memory allocated by IOMallocLow() must be freed by IOFreeLow(). 
 */
void *IOMallocLow(int size);
void IOFreeLow(void *p, int size);

#endif	KERNEL
