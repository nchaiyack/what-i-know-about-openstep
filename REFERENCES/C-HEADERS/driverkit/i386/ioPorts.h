/*
 * Copyright (c) 1993 NeXT Computer, Inc.
 *
 * Primatives for IO port access.
 *
 * HISTORY
 *
 * 16Feb93 David E. Bohman at NeXT
 *	Created.
 */

#ifndef _DRIVERKIT_I386_IOPORTS_
#define _DRIVERKIT_I386_IOPORTS_

#import <driverkit/i386/driverTypes.h>

static __inline__
unsigned char
inb(
    IOEISAPortAddress	port
)
{
    unsigned char	data;
    
    asm volatile(
    	"inb %1,%0"
	
	: "=a" (data)
	: "d" (port));
	
    return (data);
}
 
static __inline__
unsigned short
inw(
    IOEISAPortAddress	port
)
{
    unsigned short	data;
    
    asm volatile(
    	"inw %1,%0"
	
	: "=a" (data)
	: "d" (port));
	
    return (data);
}

static __inline__
unsigned long
inl(
    IOEISAPortAddress	port
)
{
    unsigned long	data;
    
    asm volatile(
    	"inl %1,%0"
	
	: "=a" (data)
	: "d" (port));
	
    return (data);
}

static __inline__
void
outb(
    IOEISAPortAddress	port,
    unsigned char	data
)
{
    static int		xxx;

    asm volatile(
    	"outb %2,%1; lock; incl %0"
	
	: "=m" (xxx)
	: "d" (port), "a" (data), "0" (xxx)
	: "cc");
}

static __inline__
void
outw(
    IOEISAPortAddress	port,
    unsigned short	data
)
{
    static int		xxx;

    asm volatile(
    	"outw %2,%1; lock; incl %0"
	
	: "=m" (xxx)
	: "d" (port), "a" (data), "0" (xxx)
	: "cc");
}

static __inline__
void
outl(
    IOEISAPortAddress	port,
    unsigned long	data
)
{
    static int		xxx;

    asm volatile(
    	"outl %2,%1; lock; incl %0"
	
	: "=m" (xxx)
	: "d" (port), "a" (data), "0" (xxx)
	: "cc");
}
#endif	_DRIVERKIT_I386_IOPORTS_
