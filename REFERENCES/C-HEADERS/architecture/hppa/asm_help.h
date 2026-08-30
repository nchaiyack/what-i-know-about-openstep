/* Copyright (c) 1993 NeXT Computer, Inc.  All rights reserved.
 *
 *	File:	architecture/hppa/asm_help.h
 *	Author:	Joshua Doenias, NeXT Computer, Inc.
 *
 *	This header file defines macros useful when writing assembly code
 *	for the HP PA-RISC family processors.
 *
 * HISTORY
 * 9-Aug-93  Joshua Doenias (josh@next.com)
 *	Created.
 *
 * 28-June-95 Matt Watson (mwatson@next.com)
 *	Added dynamic/PIC macros
 *
 * 25-July-95 Umesh Vaishampayan (umeshv@NeXT.com)
 *      Added alignment directive to .non_lazy_symbol_pointer section
 */

#ifndef	_ARCH_HPPA_ASM_HELP_H_
#define	_ARCH_HPPA_ASM_HELP_H_

#ifdef	__ASSEMBLER__

/*  Interesting register aliases */

#define zero	%r0	// architecturally defined to be 0
#define rp	%r2	// return pointer
#define fp	%r4	// frame pointer
#define arg0	%r26	// general args
#define arg1	%r25
#define arg2	%r24
#define arg3	%r23
#define ret0	%r28	// return values
#define ret1	%r29
#define sp	%r30	// stack pointer

#define fdarg0	%fr5	// double arg 0
#define fdarg1	%fr7	// double arg 1
#define fsarg0	%fr4	// float arg 0
#define fsarg1	%fr5	// float arg 1
#define fsarg2  %fr6    // float arg 2
#define fsarg3  %fr7    // float arg 3
#define fret	%fr4    // return val

/* 
 * This is what the hppa stack looks like at the time the function is called.
 * Note that this is set up BY THE CALLER.  The called function only has
 * to set up a frame if it is going to call other functions, or use local
 * space.
 *
 *							High addresses
 * 
 * SP  ----> callee allocates locals here   ( old fp saved here if needed )
 *          +----------------------------+
 * SP-4     |   16 bytes (unused in NS)  |
 *          +----------------------------+
 * SP-20    |       old RP home          |
 *          +----------------------------+
 * SP-24    |     12 byte frame area     |
 *          |    (unused in NEXTSTEP)    |
 *          +----------------------------+
 * SP-36    |        arg 0 home          |
 *          +----------------------------+
 * SP-40    |        arg 1 home          |
 *          +----------------------------+
 *          |        arg 2 home          |
 *          +----------------------------+
 *          |        arg 3 home area     |
 *          +----------------------------+
 * SP-52    | additional args on stack.. |		Low addresses
 *
 *  If a procedure will call another proc, it needs to allocate the above
 *  48 bytes on its stack.  Additional space is allocated for local vars.
 *  The whole shebang is rounded up to a multiple of 64 bytes.
 */
 
/* ARG(n)  offset to argument area.  These are 0 based -- ARG(0) is 
 * the first argument.
 * Note that at the time the procedure is called, only arg words 4 and >
 * are on the stack.  0-3 are in registers, although a homing area is 
 * available for them.
 * In a leaf procedure with no locals, this macro can be used as a stack
 * offset.  In a nested procedure or a leaf with locals declared, this 
 * macro is actually a frame offset.
 */
#define ARG(n)  (((n)*4) - 36)

/* LOCAL_VAR(n)  frame offset to local variable area.  These are 0 based --
 * LOCAL_VAR(0) is the first local word.
 * This is an index into the local argument words.  If the function is putting
 * anything other than words into local storage, it must account for them
 * itself.
 * Also, this macro is only valid if the function has been declared using
 * either LEAF() or NESTED() with a local variable size greater than 0.
 *
 * It can be used as follows:
 *   ldw 	LOCAL_VAR(0)(0,fp), ret0    ; loads first local in return val
 *   stw  	arg0, LOCAL_VAR(0)(0,fp)    ; stores first arg in first local
 */
 
#define LOCAL_VAR(n)  (((n)+1)*4)




/* Macros for building stack frame */


/* Stack is always aligned to 64 bytes */
#define STACK_INCR	64
#define ROUND_TO_STACK(len)			\
	(((len) + STACK_INCR - 1) & ~(STACK_INCR-1))

#define NESTED_FUNCTION_PROLOGUE(localvarsize)			 \
	stw	rp,-20(0,%r30)  				@\
	.set	__framesize,ROUND_TO_STACK(localvarsize+52)	@\
	.set 	__nested_function,1				@\
	copy	fp,%r1						@\
	copy	sp,fp						@\
	stwm	%r1,__framesize(0,sp)

#define LEAF_FUNCTION_PROLOGUE(localvarsize)			\
	.set  __nested_function,0				@\
	.if localvarsize					@\
	  .set __framesize,ROUND_TO_STACK(localvarsize+4)	@\
	  copy  fp,%r1						@\
	  copy	sp,fp						@\
	  stwm	%r1,__framesize(0,sp)				@\
	.else 							@\
	  .set __framesize,0					@\
	.endif

#define FUNCTION_EPILOGUE					\
	.if __nested_function					@\
	   ldw -20(0,fp),rp					@\
	.endif							@\
	.if __framesize						@\
	  bv 0(rp)						@\
	  ldwm -__framesize(0,sp),fp				@\
	.else							@\
	  bv,n 0(rp)						@\
	.endif		
	  
/*
 * LEAF - declare global leaf procedure
 */
#define LEAF(name,localvarsize)					\
	.align 2						@\
	.globl name						@\
name:								@\
	LEAF_FUNCTION_PROLOGUE(localvarsize)
	
/*
 * P_LEAF - declare private leaf procedure
 */
#define P_LEAF(name,localvarsize)				\
	.align 2						@\
name:								@\
	LEAF_FUNCTION_PROLOGUE(localvarsize)


/*
 * NESTED -- declare procedure that invokes other procedures
 */
#define NESTED(name,localvarsize)				\
	.align 2						@\
	.globl name						@\
name:								@\
	NESTED_FUNCTION_PROLOGUE(localvarsize)

/*
 * P_NESTED -- declare private procedure that invokes other procedures
 */
#define P_NESTED(name,localvarsize)				\
	.align 2						@\
name:								@\
	NESTED_FUNCTION_PROLOGUE(localvarsize)

/*
 * END -- mark end of procedure
 */
#define END(name)						\
 	FUNCTION_EPILOGUE

#define	X_NESTED(name, value)				\
	.globl	name					@\
	.set	name,value


/*
 * dynamic/PIC macros for routines which reference external symbols
 */

#if defined(__DYNAMIC__)
#define PICIFY(var)						\
	bl	1f,%r19						@ \
	dep	%r0,31,2,%r19					@ \
1:								@ \
	addil	L`L ## var ## $non_lazy_ptr-1b,%r19		@ \
	ldw	R`L ## var ## $non_lazy_ptr-1b(%r1),%r19

#define CALL_EXTERN_AGAIN(var)	\
	PICIFY(var)		@ \
	ble	0(%sr4,%r19)	@ \
	copy	%r31, rp

#define NON_LAZY_STUB(var)	\
.non_lazy_symbol_pointer	@ \
.align 2			@ \
L ## var ## $non_lazy_ptr:	@ \
.indirect_symbol var		@ \
.long 0				@ \
.text				@ \
.align 2

#define	BRANCH_EXTERN(var)	\
	PICIFY(var)		@ \
	be,n	0(%sr4,%r19)	@ \
	NON_LAZY_STUB(var)

#define CALL_EXTERN(var)	\
	CALL_EXTERN_AGAIN(var)	@ \
	NON_LAZY_STUB(var)

#define REG_TO_EXTERN(reg, var)	\
	PICIFY(var)		@ \
	stw	reg, 0(0,%r19)	@ \
	NON_LAZY_STUB(var)

#else
#define BRANCH_EXTERN(var)		\
	ldil	L` ## var,%r1		@ \
	be,n	R` ## var(%sr4,%r1)

#define CALL_EXTERN(var)		\
	ldil	L` ## var,%r1		@ \
	ble	R` ## var(%sr4,%r1)	@ \
	copy	%r31, rp

#define CALL_EXTERN_AGAIN(var)	\
	CALL_EXTERN(var)

#define REG_TO_EXTERN(reg, var)	\
	ldil L`## var,%r19	@ \
	stw reg, R`## var(%r19)
#endif

#define LONG_CALL(name)	\
    CALL_EXTERN(name)

#endif  __ASSEMBLER__
#endif	_ARCH_HPPA_ASM_HELP_H_
