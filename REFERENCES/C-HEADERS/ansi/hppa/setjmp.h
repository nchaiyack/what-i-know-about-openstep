/* Copyright (c) 1992 NeXT Computer, Inc.  All rights reserved.
 *
 *	File:	setjmp.h
 *
 *	Declaration of setjmp routines and data structures.
 */
#ifndef _ANSI_HPPA_SETJMP_H
#define _ANSI_HPPA_SETJMP_H

#import <bsd/hppa/signal.h>

struct _jmp_buf {
	/* Kernel state preserved by setjmp/longjmp. */
	struct sigcontext	sigcontext;

	/* Callee-saved registers preserved by setjmp/longjmp (r3 - r18). */
	unsigned long csr[16];

	/* gb (cthread state, doesn't really need to be saved */
	unsigned long gb;

	/* return pointer. */
	unsigned long rp;

	/* return value (used by longjmp) */
	unsigned long rval;

	/* setjmp vs. _setjmp (setjmp == 1, _setjmp == 0) */
	unsigned was_setjmp;

	/* Stack pointer. */
	unsigned long sp;

	/* Magic number for sanity check. */
	unsigned long magic;
	/* Floating point status & control register */
	double fpscr[4] __attribute__((aligned(8)));

	/* Callee-saved floating point registers (fr12 - fr21). */
	double fpr[10] __attribute__((aligned(8)));

};

/* Magic number used to verify jmp_buf validity. */

#define	_JMP_BUF_MAGICNUM	0xfadedfad

/* ANSI X3.159-1989 requires `jmp_buf' to be an array type. */

typedef	struct _jmp_buf jmp_buf[1];

/* ANSI X3.159-1989 requires `setjmp.h' to define the macro `setjmp'. */
#ifdef __STDC__
#ifndef setjmp
#define setjmp(env) setjmp(env)
#endif  /*setjmp */
#endif  /* __STDC__ */

/* External routines. */

extern int setjmp(jmp_buf env);
extern int _setjmp(jmp_buf env);

extern void longjmp(jmp_buf env, int val);
extern void _longjmp(jmp_buf env, int val);

#endif /* _ANSI_HPPA_SETJMP_H */
