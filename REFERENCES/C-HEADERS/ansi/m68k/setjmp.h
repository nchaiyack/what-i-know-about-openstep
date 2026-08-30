/* Copyright (c) 1992, NeXT Computer, Inc.  All rights reserved.
 *
 *	File:	setjmp.h
 *
 *	Declaration of setjmp routines and data structures.
 */

#ifndef _ANSI_M68K_SETJMP_H
	#define _ANSI_M68K_SETJMP_H

	#include <standards.h>

	#if !defined(__STRICT_ANSI__) && !defined(_POSIX_SOURCE)
		/*
		 * WARNING: the first portion of this must match a
		 *          struct sigcontext
		 */
		#define	JB_ONSTACK	0
		#define	JB_SIGMASK	1
		#define	JB_SP		2
		#define	JB_PC		3
		#define	JB_PS		4
		#define JB_D0		5
		/* from here on down, independent of struct sigcontext */
		#define	JB_D2		6
		#define	JB_D3		7
		#define	JB_D4		8
		#define	JB_D5		9
		#define	JB_D6		10
		#define	JB_D7		11
		#define	JB_A2		12
		#define	JB_A3		13
		#define	JB_A4		14
		#define	JB_A5		15
		#define	JB_A6		16
		#define	JB_FP2		17
		#define	JB_FP3		20
		#define	JB_FP4		21
		#define	JB_FP5		26
		#define	JB_FP6		29
		#define	JB_FP7		32
		#define	JB_FPCR		35
		#define	JB_FPSR		36
		#define	JB_FPIAR	37
		#define	JB_MAGIC	38
		#define	JB_NREGS	(JB_MAGIC+1)

		#define	JB_MAGICNUM	0xbeeffeed

		#if !defined(LOCORE) && !defined(ASSEMBLER)
			typedef int jmp_buf[JB_NREGS];

			#ifndef __STRICT_BSD__
				extern int setjmp(jmp_buf env);
				extern int _setjmp(jmp_buf env);
				#ifdef	__GNUC__
					extern volatile void \
						longjmp(jmp_buf env, int val);
					extern volatile void \
						_longjmp(jmp_buf env, int val);
				#else
					extern void \
						longjmp(jmp_buf env, int val);
					extern void \
						_longjmp(jmp_buf env, int val);
				#endif /* __GNUC__ */
			#endif /* __STRICT_BSD__ */
		#endif /* !LOCORE && !ASSEMBLER */
	#else /* ! __STRICT_ANSI__ && ! _POSIX_SOURCE */
		/*
		 * WARNING: the first portion of this must match a struct
		 *	    sigcontext
		 */
		#define	_SJB_ONSTACK	0
		#define	_SJB_SIGMASK	1
		#define	_SJB_SP		2
		#define	_SJB_PC		3
		#define	_SJB_PS		4
		#define _SJB_D0		5
		/* from here on down, independent of struct sigcontext */
		#define	_SJB_D2			6
		#define	_SJB_D3			7
		#define	_SJB_D4			8
		#define	_SJB_D5			9
		#define	_SJB_D6			10
		#define	_SJB_D7			11
		#define	_SJB_A2			12
		#define	_SJB_A3			13
		#define	_SJB_A4			14
		#define	_SJB_A5			15
		#define	_SJB_A6			16
		#define	_SJB_FP2		17
		#define	_SJB_FP3		20
		#define	_SJB_FP4		21
		#define	_SJB_FP5		26
		#define	_SJB_FP6		29
		#define	_SJB_FP7		32
		#define	_SJB_FPCR		35
		#define	_SJB_FPSR		36
		#define	_SJB_FPIAR		37
		#define _SJB_USE_SIGMASK	38
		#define	_SJB_MAGIC		39
		#define	_SJB_NREGS	(_SJB_MAGIC+1)

		#define	_SJB_MAGICNUM	0xdeafbeef
		#if !defined(LOCORE) && !defined(ASSEMBLER)
			typedef int jmp_buf[39];

			#ifdef __STDC__
				extern int setjmp(jmp_buf env);
				extern int _setjmp(jmp_buf env);
				extern void longjmp(jmp_buf env, int val);
				extern void _longjmp(jmp_buf env, int val);
			#else
				extern int setjmp();
				extern int _setjmp();
				extern void longjmp();
				extern void _longjmp();
			#endif /* __STDC__ */

			#ifdef _POSIX_SOURCE
				typedef int sigjmp_buf[_SJB_NREGS];
				#ifdef __STDC__
					extern void \
					    siglongjmp(sigjmp_buf env, int val);
					extern int \
					sigsetjmp(sigjmp_buf env, int savemask);
				#else
					extern void siglongjmp();
					extern int sigsetjmp();
				#endif /* __STDC__ */
			#endif /* _POSIX_SOURCE */
			
		#endif /* !LOCORE && !ASSEMBLER */
	#endif /* ! __STRICT_ANSI__ && ! _POSIX_SOURCE */
#endif /* _ANSI_M68K_SETJMP_H */
