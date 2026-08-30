/* Copyright (c) 1995 NeXT Computer, Inc.  All rights reserved.
 *
 *	File:	architecture/sparc/asm_help.h
 *	Author:	Umesh Vaishampayan, NeXT Computer, Inc.
 *
 *	This header file defines macros useful when writing assembly code
 *	for the SPARC family processors.
 *
 * HISTORY
 * 21-Jul-95  Umesh Vaishampayan (umeshv@next.com)
 *	Created. [Ported from architecture/hppa/asm_help.h ]
 *
 */

#ifndef	_ARCH_SPARC_ASM_HELP_H_
#define	_ARCH_SPARC_ASM_HELP_H_

#import <architecture/sparc/asm_linkage.h>


#ifdef  __ASSEMBLER__

/*
 * dynamic/PIC macros for routines which reference external symbols
 */

/*
 * the macros assume that %g4 is used as a scratch register
 */

#if defined(__DYNAMIC__)

#define PICIFY(var) \
0: ;\
	call	1f ; \
	sethi	%hi(L ## var ## $non_lazy_ptr - 0b),%g6 ; \
1: ; \
	or	%g6, %lo(L ## var ## $non_lazy_ptr - 0b), %g6 ; \
	ld	[%g6 + %o7], %g6
	
	
#define CALL_EXTERN_AGAIN(var)	\
	PICIFY(var) ; \
	jmpl	%g6,%o7 ; \
	nop


#define NON_LAZY_STUB(var)	\
.non_lazy_symbol_pointer	; \
.align 2			; \
L ## var ## $non_lazy_ptr:	; \
.indirect_symbol var		; \
.long 0				; \
.text				; \
.align 2

#define CERROR		\
	bcc	Lnoerr		; \
	nop			; \
	BRANCH_EXTERN(cerror)	; \
.text				; \
Lnoerr:	nop

#define	BRANCH_EXTERN(var)	\
		mov	%o7,%g4 ; \
        PICIFY(var)		; \
        jmp	%g6	; \
		mov	%g4,%o7 ; \
        NON_LAZY_STUB(var)

#define CALL_EXTERN(var)	\
        CALL_EXTERN_AGAIN(var)	; \
        NON_LAZY_STUB(var)

#define REG_TO_EXTERN(reg, var)	\
	mov	%o7,%g4 ; \
	PICIFY(var) ; \
	mov	%g4,%o7 ; \
	st	reg, [%g6] ; \
    NON_LAZY_STUB(var)

#define LONG_CALL(name)	\
    CALL_EXTERN(name)

#define EXTERN_TO_REG(reg, var) \
	mov	%o7,%g4 ; \
	PICIFY(var) ; \
	mov	%g4,%o7 ; \
	mov	%g6,reg ; \
	NON_LAZY_STUB(var)

#else __DYNAMIC__

#define CERROR	\
	bcc 	Lnoerr					;\
	sethi	%hi(cerror), %g6			;\
	or	%g6, %lo(cerror), %g6	;\
	jmp	%g6				;\
Lnoerr: nop
				
#define BRANCH_EXTERN(var)		\
	sethi	%hi(var), %g6	; \
	or	%g6, %lo(var), %g6	; \
	jmp	%g6 ; \
	nop

#define CALL_EXTERN(var)		\
	call	var ; \
	nop

#define CALL_EXTERN_AGAIN(var)	\
        CALL_EXTERN(var)

#define REG_TO_EXTERN(reg, var)	\
        sethi	%hi(var),%g6	; \
        st	reg, [%g6 + %lo(var)]

#define LONG_CALL(name)	\
    CALL_EXTERN(name)

#define EXTERN_TO_REG(reg, var) \
	set var,reg

#endif	__DYNAMIC__

#endif  __ASSEMBLER__
#endif	_ARCH_SPARC_ASM_HELP_H_
