/*
 *	File:	spl.h
 *	Author:	Avadis Tevanian, Jr.
 *
 *	Define inline macros for spl routines.
 *	
 * HISTORY
 * 21-May-91  Gregg Kellogg (gk) at NeXT
 *	Moved public portion to exported directory.
 *
 * 14-May-90  Gregg Kellogg (gk) at NeXT
 *	Changed SPLCLOCK from 6 to 3, as much scheduling code expects
 *	splclock() == splsched().  Added splusclock().
 *
 * 19-Jun-89  Mike DeMoney (mike) at NeXT
 *	Modified to allow spl assertions in spl_measured.h
 */

#ifndef	_KERNSERV_SPARC_SPL_H_
#define	_KERNSERV_SPARC_SPL_H_

extern int spl7(void);

extern int splhigh(void);

extern int splusclock(void);
extern int splsched(void);

extern int spl6(void);
extern int spl5(void);

extern int splclock(void);
extern int splimp(void);
extern int splvm(void);
extern int splbio(void);
extern int spldevice(void);
extern int spltty(void);

extern int spl4(void);
extern int spl3(void);

extern int spl2(void);
extern int spl1(void);

extern int splsoftclock(void);
extern int splnet(void);

extern int spl0(void);
		    
extern int splx(int	ipl);

/* ipltospl() is defined in psl.h */

extern int curipl(void);

#define IPLHIGH         10
#define IPLUSCLOCK      10
#define IPLSCHED        10
#define IPLCLOCK        9
#define IPLVM           9
#define IPLBIO          9
#define IPLIMP          9
#define IPLDEVICE	9
#define IPLTTY          9
#define IPLSOFTCLOCK	1
#define IPLNET		1

#endif	_KERNSERV_SPARC_SPL_H_
