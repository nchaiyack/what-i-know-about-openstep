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

/*
 *	SPL definitions
 */

#ifndef	_KERNSERV_HPPA_SPL_H_
#define	_KERNSERV_HPPA_SPL_H_



/* Defines for intrtab style */
/* defines for style */
#define 	BSD_INTR_STYLE	1			/* BSD style driver connection */
#define		DKIT_INTR_STYLE	2			/* Driverkit style interrupt */
#define		EISA_INTR_STYLE	4			/* EISA interrutp nums */
#define		SECONDLASI_INTR_STYLE	8	/* second lasi intr numbers */

/*
 * spl routines 
 */
 

#ifndef __ASSEMBLER__
extern int splx(int	spl);
#endif __ASSEMBLER__

#define splusclock()	splhigh()
#define spldma()		splhigh()
#define splsched()		splhigh()
#define splclock()		splhigh()

#define spldev()		splbio()
#define splvm()			splbio()
#define splscc()		splbio()
#define splimp()		splbio()
#define splnet()		splbio()
#define spltty()		splbio()
#define spln(ipl)		splx(ipl)

#define splsoftclock	spl0()

/*
 * the following IPL* are used with curipl(), which returns the current SPL
 * level. 
 */

#ifndef __ASSEMBLER__
extern int curipl(void);
extern unsigned int ipltospl(unsigned int ipl);
#endif

#define IPLHIGH         7

#define IPLUSCLOCK      6
#define IPLSCHED        6
#define IPLCLOCK        6
#define IPLDMA          6

#define IPLSCC          3
#define IPLBIO          3
#define IPLIMP          3
#define IPLVM           3
#define IPLNET          3
#define IPLDEVICE		3
#define IPLTTY          3

#define IPLSOFTCLOCK	0	// IPL0

#endif	_KERNSERV_HPPA_SPL_H_
