/*
 * Copyright (c) 1994 NeXT Computer, Inc.
 *
 * HISTORY
 *
 * 21-Apr-1994 Mac Gillon at NeXT
 *	Created.
 */

#ifndef	_SPARC_SIGNAL_
#define	_SPARC_SIGNAL_ 1

#ifndef __ASSEMBLER__

/*
 * Information pushed on stack when a signal is delivered.
 * This is used by the kernel to restore state following
 * execution of the signal handler.  It is also made available
 * to the handler to allow it to properly restore state if
 * a non-standard exit is performed.
 */
#define SPARC_MAXREGWINDOW  31  /* max usable windows in sparc */

struct  sigcontext {
    int sc_onstack;     /* sigstack state to restore */
    int sc_mask;        /* signal mask to restore */
    int sc_sp;          /* sp to restore */
    int sc_pc;          /* pc to retore */
    int sc_npc;         /* next pc to restore */
    int sc_psr;         /* psr to restore */
    int sc_g1;          /* register that must be restored */
    int sc_o0;
    int sc_wbcnt;       /* number of outstanding windows */
    char    *sc_spbuf[SPARC_MAXREGWINDOW]; /* sp's for each wbuf */
    int sc_wbuf[SPARC_MAXREGWINDOW][16]; /* window save buf */
};
#endif  /* __ASSEMBLER__ */

#endif /* _SPARC_SIGNAL_ */

