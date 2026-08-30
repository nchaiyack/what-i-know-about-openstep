/*
 * Copyright (c) 1994 NeXT Computer, Inc.
 *
 * SPARC Family:	Machine dependent exception codes.
 *
 * HISTORY
 *
 * 21-Apr-1994 Mac Gillon at NeXT
 *	Created.
 */
 
#ifndef	_MACH_SPARC_EXCEPTION_H_
#define	_MACH_SPARC_EXCEPTION_H_


/*
 *	EXC_BAD_ACCESS
 *	Note: do not conflict with kern_return_t values returned by vm_fault
 */

/* to avoid clash with the kern_return.h values */
#define EXC_SPARC_BAD_ACCESS(x)		(0x300+x)

#define EXC_SPARC_TEXT_FAULT	EXC_SPARC_BAD_ACCESS(0x01)
/* same value for TEXT_ERROR */ 
#define EXC_SPARC_WIN_OVERFLOW	EXC_SPARC_BAD_ACCESS(0x02)
#define EXC_SPARC_WIN_UNDERFLOW	EXC_SPARC_BAD_ACCESS(0x03)
#define EXC_SPARC_ALIGNMENT	EXC_SPARC_BAD_ACCESS(0x04)
#define EXC_SPARC_DATA_FAULT	EXC_SPARC_BAD_ACCESS(0x05)
/* same value for DATA_ERROR */
#define EXC_SPARC_DATA_STORE	EXC_SPARC_BAD_ACCESS(0x06)
#define EXC_SPARC_DATA_MISS	EXC_SPARC_BAD_ACCESS(0x07)
#define EXC_SPARC_TEXT_MISS	EXC_SPARC_BAD_ACCESS(0x08)

#define	EXC_SPARC_BUS_HWERR	EXC_SPARC_BAD_ACCESS(0x09)
			/* misc hardware error (e.g. timeout) */
#define	EXC_SPARC_BUS_ALIGN	EXC_SPARC_BAD_ACCESS(0x0A)	
			/* hardware alignment error */
#define	EXC_SPARC_SEGV_NOMAP	EXC_SPARC_BAD_ACCESS(0x0B)	
			/* no mapping at the fault address */
#define	EXC_SPARC_SEGV_PROT	EXC_SPARC_BAD_ACCESS(0x0C)		
			/* access exceeded protections */
#define	EXC_SPARC_OBJERR	EXC_SPARC_BAD_ACCESS(0x0D)	
			/* object returned errno value */
#define EXC_SPARC_FP_DISABLED	EXC_SPARC_BAD_ACCESS(0x0E)
#define EXC_SPARC_CP_DISABLED	EXC_SPARC_BAD_ACCESS(0x0F)

/*
 *	EXC_BAD_INSTRUCTION
 */

#define EXC_SPARC_BAD_INST(x)		(0x500+x)

#define	EXC_SPARC_ILL_STACK		EXC_SPARC_BAD_INST(0x01)	
					/* bad stack */
#define	EXC_SPARC_ILL_ILLINSTR_FAULT	EXC_SPARC_BAD_INST(0x02	)
					/* illegal instruction fault */
#define	EXC_SPARC_ILL_PRIVINSTR_FAULT	EXC_SPARC_BAD_INST(0x03	)
					/* privileged instruction fault */



#define EXC_SPARC_UNIMP_INSTR		T_UNIMP_INSTR
#define EXC_SPARC_PRIV_INSTR		T_PRIV_INSTR
#define EXC_SPARC_UNIMP_FLUSH		T_UNIMP_FLUSH

/*
 *	EXC_ARITHMETIC
 */

#define EXC_SPARC_BAD_ARITH(x)		(0x600+x)

#define EXC_SPARC_FPE_INTOVF_TRAP	EXC_SPARC_BAD_ARITH(0x04)
					/* integer overflow */
#define EXC_SPARC_FPE_STARTSIG_TRAP	EXC_SPARC_BAD_ARITH(0x05)
					/* process using fp */
#define EXC_SPARC_FPE_INTDIV_TRAP	EXC_SPARC_BAD_ARITH(0x06)
					/* integer divide by zero */
#define EXC_SPARC_FPE_FLTINEX_TRAP	EXC_SPARC_BAD_ARITH(0x07)
					/* [floating inexact result] */
#define EXC_SPARC_FPE_FLTDIV_TRAP	EXC_SPARC_BAD_ARITH(0x08)
					/* [floating divide by zero] */
#define	EXC_SPARC_FPE_FLTUND_TRAP	EXC_SPARC_BAD_ARITH(0x09)
					/* [floating underflow] */
#define	EXC_SPARC_FPE_FLTOPERR_TRAP	EXC_SPARC_BAD_ARITH(0x0A)
					/* [floating operand error] */
#define	EXC_SPARC_FPE_FLTOVF_TRAP	EXC_SPARC_BAD_ARITH(0x0B)
					/* [floating overflow] */


#define EXC_SPARC_CP_EXCEPTION		T_CP_EXCEPTION
#define EXC_SPARC_FP_EXCEPTION		T_FP_EXCEPTION
#define EXC_SPARC_TAG_OVERFLOW	T_TAG_OVERFLOW
#define EXC_SPARC_IDIV0		T_IDIV0

/*
 *	EXC_BREAKPOINT
 */

#define EXC_SPARC_BREAKPOINT1	T_BREAKPOINT

/*
 *	EXC_SOFTWARE
 */

#define EXC_SPARC_SYSCALL	T_SYSCALL
#define EXC_SPARC_DIV0		T_DIV0
#define EXC_SPARC_FLUSH_WIN	T_FLUSH_WINDOWS
#define EXC_SPARC_CLEAN_WIN	T_CLEAN_WINDOWS
#define EXC_SPARC_RANGE_CHECK	T_RANGE_CHECK
#define EXC_SPARC_FIX_ALIGN	T_FIX_ALIGN
#define EXC_SPARC_INT_OVERFLOW	T_INT_OVERFLOW
#define EXC_SPARC_GETCC		T_GETCC
#define EXC_SPARC_SETCC		T_SETCC

#define EXC_SPARC_BAD_USYSCALL	0x700

#define EXC_SPARC_DEBUG		0x800

#endif	_MACH_SPARC_EXCEPTION_H_
