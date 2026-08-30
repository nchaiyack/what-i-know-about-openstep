/* Copyright (c) 1991 NeXT Computer, Inc.  All rights reserved.
 *
 *	File:	architecture/hppa/pseudo_inst.h
 *	Author:	Josh Doenias, NeXT Computer, Inc.
 *
 *	This header file defines assembler pseudo-instruction macros for
 *	for the HP PA-RISC architecture.
 *
 *	NOTE: This is obviously only useful to include in assembly
 *	code source.
 *
 * HISTORY
 * 05-Aug-93  Josh Doenias (josh@next.com)
 *	Created.
 */

#ifndef	_ARCH_HPPA_PSEUDO_INST_H_
#define	_ARCH_HPPA_PSEUDO_INST_H_
#ifdef	__ASSEMBLER__

/*
 * Pseudo instruction definitions
 */

/*
 * ldi32	IMMED,%rD
 *
 * Load 32-bit immediate into rD
 */
.macro	ldi32				// ldi32	immed,reg
.if	$n != 2
	.abort	"invalid operands of li32"
.endif
.abs	__is_abs,$0
.if	!__is_abs
	ldil	L`$0,$1
	ldo	R`$0($1),$1
.elseif	$0 == 0
	add	%r0,%r0,$1
.elseif	($0 & 0xffffc000) == 0
	ldo	$0(%r0),$1
.elseif	($0 & 0x7ff) == 0
	ldil	$0,$1
.else
	ldil	L`$0,$1
	ldo	R`$0($1),$1
.endif
.endmacro
 
#endif	__ASSEMBLER__

#endif	_ARCH_HPPA_PSEUDO_INST_H_
