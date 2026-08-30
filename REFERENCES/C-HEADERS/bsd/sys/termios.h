/*
 * Copyright (c) 1988, 1989 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)termios.h	7.22 (Berkeley) 5/7/91
 */

/*
 *  termios structure
 */
#ifndef _TERMIOS_H_
#define _TERMIOS_H_

/* 
 * Special Control Characters 
 *
 * Index into c_cc[] character array.
 *
 *	Name	     Subscript	Enabled by 
 */
#define	VEOF		0				/* ICANON */
#define	VEOL		1				/* ICANON */
#define	VERASE		2				/* ICANON */
#define VKILL		3				/* ICANON */
#define VINTR		4				/* ISIG */
#define VQUIT		5				/* ISIG */
#define VSUSP		6				/* ISIG */
#define VSTART		7				/* IXON, IXOFF */
#define VSTOP		8				/* IXON, IXOFF */
#define VMIN		9				/* !ICANON */
#define VTIME		10				/* !ICANON */

#if defined(_NEXT_SOURCE)
#define VWERASE 	11				/* ICANON */
#define VREPRINT 	12				/* ICANON */
#define VLNEXT		13				/* IEXTEN */
#define VDISCARD	14				/* IEXTEN */
#define VDSUSP		15				/* ISIG */
#define VQUOTE		16				/* ICANON */
#endif 	/* _NEXT_SOURCE */

#define	NCCS		17

/*
 * Input flags - software input processing
 */
#define	IGNBRK		0x00000001	/* ignore BREAK condition */
#define	BRKINT		0x00000002	/* map BREAK to SIGINTR */
#define	IGNPAR		0x00000004	/* ignore (discard) parity errors */
#define	PARMRK		0x00000008	/* mark parity and framing errors */
#define	INPCK		0x00000010	/* enable checking of parity errors */
#define	ISTRIP		0x00000020	/* strip 8th bit off chars */
#define	INLCR		0x00000040	/* map NL into CR */
#define	IGNCR		0x00000080	/* ignore CR */
#define	ICRNL		0x00000100	/* map CR to NL (ala CRMOD) */
#define	IXON		0x00000200	/* enable output flow control */
#define	IXOFF		0x00000400	/* enable input flow control */

#if defined(_NEXT_SOURCE)
#define	IXANY		0x00000800	/* any char will restart after stop */
#define IMAXBEL		0x00002000	/* ring bell on input queue full */
#endif	 /* _NEXT_SOURCE */

/*
 * Output flags - software output processing
 */
#define	OPOST		0x00000001	/* enable following output processing */
#if defined(_NEXT_SOURCE)
#define ONLCR		0x00000002	/* map NL to CR-NL (ala CRMOD) */
	/* use the same bits as old delay flags */
#define	NLDELAY		0x00000300	/* \n delay */
#define		NL0	0x00000000
#define		NL1	0x00000100	/* tty 37 */
#define		NL2	0x00000200	/* vt05 */
#define		NL3	0x00000300
#define	TBDELAY		0x00000c00	/* horizontal tab delay */
#define		TAB0	0x00000000
#define		TAB1	0x00000400	/* tty 37 */
#define		TAB2	0x00000800
#define	XTABS		0x00000c00	/* expand tabs on output */
#define	CRDELAY		0x00003000	/* \r delay */
#define		CR0	0x00000000
#define		CR1	0x00001000	/* tn 300 */
#define		CR2	0x00002000	/* tty 37 */
#define		CR3	0x00003000	/* concept 100 */
#define	VTDELAY		0x00004000	/* vertical tab delay */
#define		FF0	0x00000000
#define		FF1	0x00004000	/* tty 37 */
#define	BSDELAY		0x00008000	/* \b delay */
#define		BS0	0x00000000
#define		BS1	0x00008000
#define	ALLDELAY	(NLDELAY|TBDELAY|CRDELAY|VTDELAY|BSDELAY)
#endif	/* _NEXT_SOURCE */

/*
 * Control flags - hardware control of terminal
 */
#if defined(_NEXT_SOURCE)
#define	CIGNORE		0x00000001	/* ignore control flags */
#endif	/* _NEXT_SOURCE */

#define CSIZE		0x00000300	/* character size mask */
#define     CS5		    0x00000000	    /* 5 bits (pseudo) */
#define     CS6		    0x00000100	    /* 6 bits */
#define     CS7		    0x00000200	    /* 7 bits */
#define     CS8		    0x00000300	    /* 8 bits */
#define CSTOPB		0x00000400	/* send 2 stop bits */
#define CREAD		0x00000800	/* enable receiver */
#define PARENB		0x00001000	/* parity enable */
#define PARODD		0x00002000	/* odd parity, else even */
#define HUPCL		0x00004000	/* hang up on last close */
#define CLOCAL		0x00008000	/* ignore modem status lines */

#if defined(_NEXT_SOURCE)
#define CSTOPB110	0x00010000
#define PAR0		0x00020000	/* Space parity */
#define PAR1		0x00040000	/* Mark parity */
#endif	/* _NEXT_SOURCE */


/* 
 * "Local" flags - dumping ground for other state
 *
 * Warning: some flags in this structure begin with
 * the letter "I" and look like they belong in the
 * input flag.
 */

#if defined(_NEXT_SOURCE)
#define	ECHOKE		0x00000001	/* visual erase for line kill */
#endif	/* _NEXT_SOURCE */

#define	ECHOE		0x00000002	/* visually erase chars */
#define	ECHOK		0x00000004	/* echo NL after line kill */
#define ECHO		0x00000008	/* enable echoing */
#define	ECHONL		0x00000010	/* echo NL even if ECHO is off */
#define	ICANON		0x00000020	/* canonicalize input lines */
#define	ISIG		0x00000040	/* enable signals INTR, QUIT, [D]SUSP */
#define	IEXTEN		0x00000080	/* enable DISCARD and LNEXT */

#if defined(_NEXT_SOURCE)
#define	ECHOCRT		0x00000100	/* visual erase mode for crt */
#define	ECHOPRT		0x00000200	/* visual erase mode for hardcopy */
#define ECHOCTL  	0x00000400	/* echo control chars as ^(Char) */
#define ALTWERASE	0x00000800	/* use alternate WERASE algorithm */
#define	MDMBUF		0x00100000	/* flow control output via Carrier */
#endif	/* _NEXT_SOURCE */

#define TOSTOP		0x00400000	/* stop background jobs from output */

#if defined(_NEXT_SOURCE)
#define XLCASE		0x04000000
#define XEUCBKSP	0x08000000
#endif	/* _NEXT_SOURCE */

#define	NOFLSH		0x80000000	/* don't flush after interrupt */

typedef unsigned long	tcflag_t;
typedef unsigned char	cc_t;
typedef char		speed_t;

struct termios {
	tcflag_t	c_iflag;	/* input flags */
	tcflag_t	c_oflag;	/* output flags */
	tcflag_t	c_cflag;	/* control flags */
	tcflag_t	c_lflag;	/* local flags */
	cc_t		c_cc[NCCS];	/* control chars */
	speed_t		c_ispeed;	/* input speed */
	speed_t		c_ospeed;	/* output speed */
};

/* 
 * Commands passed to tcsetattr() for setting the termios structure.
 */
#define	TCSANOW		0		/* make change immediate */
#define	TCSADRAIN	1		/* drain output, then change */
#define	TCSAFLUSH	2		/* drain output, flush input */

#if defined(_NEXT_SOURCE)
#define TCSASOFT	0x10		/* flag - don't alter h.w. state */
#endif	/* _NEXT_SOURCE */

/*
 * Standard speeds
 */
#import <sys/ttydev.h>

#ifndef KERNEL

#ifdef __STDC__
speed_t	cfgetispeed(const struct termios *);
speed_t	cfgetospeed(const struct termios *);
int	cfsetispeed(struct termios *, int);
int	cfsetospeed(struct termios *, int);
int	tcdrain(int);
int	tcflow(int, int);
int	tcflush(int, int);
int	tcgetattr(int, struct termios *);
int	tcsendbreak(int, int);
int	tcsetattr(int, int, const struct termios *);

#if defined(_NEXT_SOURCE)
void	cfmakeraw(struct termios *);
void	cfsetspeed(struct termios *, int);
#endif	/* _NEXT_SOURCE */
#endif /* __STDC__ */

#define	TCIFLUSH	1
#define	TCOFLUSH	2
#define TCIOFLUSH	3
#define	TCOOFF		1
#define	TCOON		2
#define TCIOFF		3
#define TCION		4

#endif /* !KERNEL */

/*
 * END OF PROTECTED INCLUDE.
 */
#endif /* !_TERMIOS_H_ */
