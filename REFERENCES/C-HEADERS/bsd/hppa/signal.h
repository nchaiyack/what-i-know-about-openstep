/*
 * Copyright (c) 1993 NeXT Computer, Inc.
 *
 * HISTORY
 *
 * 23 Aug 93 Mac Gillon at NeXT
 *	Created from HP version
 */

#ifndef	_HPPA_SIGNAL_
#define	_HPPA_SIGNAL_ 1

#ifndef __ASSEMBLER__

/*
 * Information pushed on stack when a signal is delivered.
 * This is used by the kernel to restore state following
 * execution of the signal handler.  It is also made available
 * to the handler to allow it to properly restore state if
 * a non-standard exit is performed.
 */
struct  sigcontext {
    int		sc_onstack;     /* sigstack state to restore */
    int		sc_mask;        /* signal mask to restore */
	int		sc_pcsq[2];		/* pc space queue */
	int		sc_pcoq[2];		/* pc offset queue */
    int		sc_psw;         /* processor status word */
    int		sc_sp;      	/* stack pointer if sc_regs == NULL */
	void	*sc_regs;		/* (kernel private) saved state */
};
#endif  /* __ASSEMBLER__ */

#define ILL_RESAD_FAULT		0x0     /* reserved addressing fault */
#define ILL_PRIVIN_FAULT	0x1     /* privileged instruction fault */
#define ILL_RESOP_FAULT     	0x2     /* reserved operand fault */
#define	ILL_PRIVREG_FAULT	0x4	/* privileged register fault */
#define BUS_UNALIGNED_FAILED	0x1	/* os assist of unaligned ref failed */
#define BUS_UNALIGNED_SUCCEEDED	0x2	/* os assist of unaligned ref success*/
#define	FPE_OVERFLOW		0x1	/* overflow trap */
#define	FPE_CONDITION		0x2	/* conditional trap  */
#define FPE_ASSIST_FAILED	0x3	/* os assist of instruction failed */
#define FPE_ASSIST_SUCCEEDED	0x4	/* os assist of instruction success */
#define	FPE_EMULATION_FAILED	0x5	/* os emulation of instruction fail */
#define	FPE_EMULATION_SUCCEEDED	0x6	/* os emulation of instruction succes*/

#define SIGCATCHALL 0x400

#endif /* _HPPA_SIGNAL_ */

