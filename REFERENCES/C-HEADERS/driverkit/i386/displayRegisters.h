/* 	Copyright (c) 1992 NeXT Computer, Inc.  All rights reserved. 
 *
 * displayRegisters.h - i386-specific register helpers
 *
 *
 * HISTORY
 * 03 Aug 93	Scott Forstall
 *      Created. 
 */

#import <driverkit/i386/ioPorts.h>

static inline unsigned char IOReadRegister(
	IOEISAPortAddress port,
	unsigned char index)
// Description:	Read register at port and index.  Return the
//		current value of the register.
{
    outb(port, index);
    return(inb(port + 1));
}

static inline void IOWriteRegister(
	IOEISAPortAddress port,
	unsigned char index,
	unsigned char value)
// Description:	Write value to register at port and index.
{
    outb(port, index);
    outb(port + 1, value);
}

static inline void IOReadModifyWriteRegister(
	IOEISAPortAddress port,
	unsigned char index,
	unsigned char protect,
	unsigned char value)
// Description:	Read-modify-write.
//		Read register at port and index.  Change value while
//		retaining protect bits.
{
    unsigned char val = IOReadRegister(port, index);
    IOWriteRegister(port, index, (val & protect) | value);
}

