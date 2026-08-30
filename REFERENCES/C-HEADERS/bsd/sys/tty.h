/* 
 * Mach Operating System
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)tty.h	7.1 (Berkeley) 6/4/86
 */

/*HISTORY
 *  7-Jan-93  Mac Gillon (mgillon) at NeXT
 *	Integrated POSIX support
 */

#ifndef	_SYS_TTY_H_
#define	_SYS_TTY_H_

#import <sys/types.h>
#import <sys/ttychars.h>
#import <sys/ttydev.h>
#import <sys/ioctl.h>

/*
 * A clist structure is the head of a linked list queue
 * of characters.  The characters are stored in blocks
 * containing a link and CBSIZE (param.h) characters. 
 * The routines in tty_subr.c manipulate these structures.
 */
struct clist {
	int	c_cc;		/* character count */
	char	*c_cf;		/* pointer to first char */
	char	*c_cl;		/* pointer to last char */
};

/*
 * Per-tty structure.
 *
 * Should be split in two, into device and tty drivers.
 * Glue could be masks of what to echo and circular buffer
 * (low, high, timeout).
 */
struct tty {
	union {
		struct {
			struct	clist T_rawq;
			struct	clist T_canq;
		} t_t;
#define	t_rawq	t_nu.t_t.T_rawq		/* raw characters or partial line */
#define	t_canq	t_nu.t_t.T_canq		/* raw characters or partial line */
		struct {
			struct	buf *T_bufp;
			char	*T_cp;
			int	T_inbuf;
			int	T_rec;
		} t_n;
#define	t_bufp	t_nu.t_n.T_bufp		/* buffer allocated to protocol */
#define	t_cp	t_nu.t_n.T_cp		/* pointer into the ripped off buffer */
#define	t_inbuf	t_nu.t_n.T_inbuf	/* number chars in the buffer */
#define	t_rec	t_nu.t_n.T_rec		/* have a complete record */
	} t_nu;
	struct	clist t_outq;		/* device */
	int	(*t_oproc)();		/* device */
	struct	proc *t_rsel;		/* tty */
	struct	proc *t_wsel;
				caddr_t	T_LINEP;	/* ### */
	caddr_t	t_addr;			/* ??? */
	dev_t	t_dev;			/* device */
	int	t_flags;		/* some of both */
	int	t_state;		/* some of both */
	short	t_pgrp;			/* tty */
	char	t_delct;		/* tty */
	char	t_line;			/* glue */
	char	t_col;			/* tty */
	char	t_ispeed, t_ospeed;	/* device */
	char	t_rocount, t_rocol;	/* tty */
	struct	ttychars t_chars;	/* tty */
	struct	winsize t_winsize;	/* window size */
	int	t_spec[8];		/* cooked mode accelerator */
	void	*t_ldisc_data;		/* for custom line disciplines */
/* be careful of tchars & co. */
#ifndef	NO_T_CHARS_DEFINES
#define	t_erase		t_chars.tc_erase
#define	t_kill		t_chars.tc_kill
#define	t_intrc		t_chars.tc_intrc
#define	t_quitc		t_chars.tc_quitc
#define	t_startc	t_chars.tc_startc
#define	t_stopc		t_chars.tc_stopc
#define	t_eofc		t_chars.tc_eofc
#define	t_brkc		t_chars.tc_brkc
#define	t_suspc		t_chars.tc_suspc
#define	t_dsuspc	t_chars.tc_dsuspc
#define	t_rprntc	t_chars.tc_rprntc
#define	t_flushc	t_chars.tc_flushc
#define	t_werasc	t_chars.tc_werasc
#define	t_lnextc	t_chars.tc_lnextc
#endif	NO_T_CHARS_DEFINES
};

#define	TTIPRI	28
#define	TTOPRI	29

/* limits */
#define	NSPEEDS	32
#define	TTMASK	31
#define	OBUFSIZ	100
#ifdef KERNEL
short	tthiwat[NSPEEDS], ttlowat[NSPEEDS], tthog[NSPEEDS];
#define	TTHIWAT(tp)	tthiwat[(tp)->t_ospeed&TTMASK]
#define	TTLOWAT(tp)	ttlowat[(tp)->t_ospeed&TTMASK]
#define	TTYHOG(tp)	1024
extern	struct ttychars ttydefaults;
#endif

/* internal state bits */
#define	TS_TIMEOUT	0x00000001	/* delay timeout in progress */
#define	TS_WOPEN	0x00000002	/* waiting for open to complete */
#define	TS_ISOPEN	0x00000004	/* device is open */
#define	TS_FLUSH	0x00000008	/* outq has been flushed during DMA */
#define	TS_CARR_ON	0x00000010	/* software copy of carrier-present */
#define	TS_BUSY		0x00000020	/* output in progress */
#define	TS_ASLEEP	0x00000040	/* wakeup when output done */
#define	TS_XCLUDE	0x00000080	/* exclusive-use flag against open */
#define	TS_TTSTOP	0x00000100	/* output stopped by ctl-s */
#define	TS_HUPCLS	0x00000200	/* hang up upon last close */
#define	TS_TBLOCK	0x00000400	/* tandem queue blocked */
#define	TS_RCOLL	0x00000800	/* collision in read select */
#define	TS_WCOLL	0x00001000	/* collision in write select */
#define	TS_NBIO		0x00002000	/* tty in non-blocking mode */
#define	TS_ASYNC	0x00004000	/* tty in async i/o mode */
#define	TS_ONDELAY	0x00008000	/* device is open; software copy of 
 					 * carrier is not present */
/* state for intra-line fancy editing work */
#define	TS_BKSL		0x00010000	/* state for lowercase \ work */
#define	TS_QUOT		0x00020000	/* last character input was \ */
#define	TS_ERASE	0x00040000	/* within a \.../ for PRTRUB */
#define	TS_LNCH		0x00080000	/* next character is literal */
#define	TS_TYPEN	0x00100000	/* retyping suspended input (PENDIN) */
#define	TS_CNTTB	0x00200000	/* counting tab width; leave FLUSHO alone */
#define	TS_EXTPROC	0x00400000	/* external processing of data */
#define	TS_INPUTFULL	0x00800000	/* hint to dev to throttle input */
#define	TS_INPUTAVAIL	0x01000000	/* driver has buffered data */
#if	NeXT
#define	TS_OUTPUTBUSY	0x02000000	/* output in progress (was TS_BUSY) */
#define	TS_OUTPUTFULL	0x04000000	/* output buffers full */
#endif	NeXT

#define	TS_LOCAL	(TS_BKSL|TS_QUOT|TS_ERASE|TS_LNCH|TS_TYPEN|TS_CNTTB)

/* define partab character types */
#define	ORDINARY	0
#define	CONTROL		1
#define	BACKSPACE	2
#define	NEWLINE		3
#define	TAB		4
#define	VTAB		5
#define	RETURN		6

/*
 * Flags on character passed to ttyinput
 */
#define TTY_CHARMASK    0x000000ff      /* Character mask */
#define TTY_QUOTE       0x00000100      /* Character quoted */
#define TTY_ERRORMASK   0xff000000      /* Error mask */
#define TTY_FE          0x01000000      /* Framing error or BREAK condition */
#define TTY_PE          0x02000000      /* Parity error */

/*
 * Structure for Posix termios
 */
struct nty {
	struct	tty *t;			/* associated tty structure */
	struct nty *t_nforw;		/* link to next nty structure */
#if POSIX_KERN
	struct session *t_session;	/* point to current session */
	struct pgrp *t_posix_pgrp;	/* point to foreground pgrp, if any */
#endif /* POSIX_KERN */
	long	t_pflags;		/* for termios, see below */
	u_char	t_quote;
	u_char	t_min;
	u_char	t_time;
};
struct nty *ttynty();


#define TP_ECHONL	0x00000002
#define TP_ECHOK	0x00000004
#define TP_ISIG		0x00000008
#define TP_IEXTEN	0x00000010
#define TP_ALTWERASE	0x00000020

#define TP_CSIZE	0x00000300
#define TP_CS5		0x00000000
#define TP_CS6		0x00000100
#define TP_CS7		0x00000200
#define TP_CS8		0x00000300
#define TP_CSTOPB	0x00000400
#define TP_CREAD	0x00000800
#define TP_PARENB	0x00001000
#define TP_CLOCAL	0x00008000
#define TP_CSTOPB110	0x00010000

#define TP_IGNBRK	0x00020000
#define TP_BRKINT	0x00040000
#define TP_IGNPAR	0x00080000
#define TP_PARMRK	0x00100000
#define TP_INPCK	0x00200000
#define TP_ISTRIP	0x00400000
#define TP_INLCR	0x00800000
#define TP_IGNCR	0x01000000
#define TP_ICRNL	0x02000000
#define TP_IXON		0x04000000
#define TP_IMAXBEL	0x08000000

#define TP_OPOST	0x10000000
#define TP_ONLCR	0x20000000

/*
 * We don't want TP_ICRNL or TP_ONLCR because we want CRMOD
 * to have the original behavior by default.
 * Most of the other flags are set up for cooked mode.
 * They are overridden by RAW, CBREAK, LITOUT, PASS8, and PASS8OUT.
 * The rest are just compatible behavior.
 */
#define TP_DEFAULT \
	(TP_ECHOK|TP_ISIG|TP_IEXTEN|\
	 TP_CS7|TP_CREAD|TP_PARENB|TP_CSTOPB110|\
	 TP_BRKINT|TP_INPCK|TP_IXON|TP_IMAXBEL|\
	 TP_OPOST)
#define NTYDEFAULTS(np) (\
	(np)->t_pflags = TP_DEFAULT, \
	(np)->t_quote = '\\', \
	(np)->t_min = 1, \
	(np)->t_time = 0)

#if POSIX_KERN
#import <sys/proc.h>
/*
 * Is tp controlling terminal for p
 */
#define isctty(p, px, np)   ((px)->p_session == (np)->t_session && \
                         (p)->p_flag&SCTTY)
#endif /* POSIX_KERN */

#endif	_SYS_TTY_H_

