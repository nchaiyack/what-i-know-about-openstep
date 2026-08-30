/* asm_help.h Created Wed Jun 28 14:08:07 PDT 1995 by mwatson */

/*
 * dynamic/PIC macros for routines which reference external symbols
 */

#if defined(__DYNAMIC__)
#define PICIFY(var)	\
	movl	pc@(L ## var ## $non_lazy_ptr-.),a0

#define CALL_EXTERN_AGAIN(func)	\
	PICIFY(func)		; \
	jbsr	a0@

#define NON_LAZY_STUB(var)	\
.non_lazy_symbol_pointer	; \
L ## var ## $non_lazy_ptr:	; \
.indirect_symbol var		; \
.long 0				; \
.text

#define CALL_EXTERN(func)	\
        CALL_EXTERN_AGAIN(func)	; \
        NON_LAZY_STUB(func)

#define	BRANCH_EXTERN(func)	\
        PICIFY(func)		; \
        jmp	a0@		; \
        NON_LAZY_STUB(func)

#define PUSH_EXTERN(var)	\
	PICIFY(var)		; \
	movl	a0@, sp@-	; \
	NON_LAZY_STUB(var)

#define REG_TO_EXTERN(reg, var)	\
	PICIFY(var)			; \
	movl	reg, a0@		;\
	NON_LAZY_STUB(var)

#define EXTERN_TO_REG(var, reg)				\
	movl	pc@(L ## var ## $non_lazy_ptr-.),reg	;\
	NON_LAZY_STUB(var)

#else
#define BRANCH_EXTERN(func)		jmp	func
#define PUSH_EXTERN(var)		movl	var, sp@-
#define CALL_EXTERN(func)		jsr	func
#define CALL_EXTERN_AGAIN(func)		jsr	func
#define REG_TO_EXTERN(reg, var)	movl	reg, var
#define EXTERN_TO_REG(var, reg)		lea	var, reg
#endif
