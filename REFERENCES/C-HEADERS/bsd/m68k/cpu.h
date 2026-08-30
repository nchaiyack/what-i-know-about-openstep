/*	@(#)cpu.h	1.0	11/09/86	(c) 1986 NeXT	*/

/* 
 * HISTORY
 * 21-May-91  Gregg Kellogg (gk) at NeXT
 *	Public version.
 *
 * 26-Mar-91  Gregg Kellogg (gk) at NeXT
 *	Externallized all variable declarations.
 *
 * 09-Nov-86  John Seamons (jks) at NeXT
 *	Ported to NeXT.
 */ 

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)cpu.h	7.1 (Berkeley) 6/5/86
 */
#ifndef	_M68K_CPU_
#define	_M68K_CPU_

#ifndef	__ASSEMBLER__
/* 
 *  We use these types in the definitions below and hence ought to include them
 *  directly to aid new callers (even if our caller is likely to have already
 *  done so).
 */
#import <bsd/sys/types.h>
#endif	__ASSEMBLER__

#ifndef	__ASSEMBLER__
#ifdef	KERNEL_BUILD
#import <cpus.h>
#else	KERNEL_BUILD
#import <mach/features.h>
#endif	KERNEL_BUILD
#endif	__ASSEMBLER__

/*
 * Hardware revisions
 */
#if	KERNEL || STANDALONE

#ifndef	__ASSEMBLER__
extern u_short	dma_chip;
extern u_char	cpu_rev;
extern u_char	cpu_clk;
extern u_char	machine_type;			/* see scr.h for values */
extern u_char	board_rev;
extern u_char	cpu_type;
extern u_char	mon_rev;
#endif	__ASSEMBLER__

/* cpu_type values */
#define	MC68030		0
#define	MC68040		1

#endif	KERNEL || STANDALONE

#ifndef	__ASSEMBLER__
#if	NCPUS > 1
static inline int cpu_number(void)
{
	register ret;

	asm volatile ("movc	msp,%0" : "=da" (ret));
	return (ret);
}
#else	NCPUS > 1
#define	cpu_number()		(0)
#endif	NCPUS > 1
#endif	__ASSEMBLER__
			

#endif	_M68K_CPU_
