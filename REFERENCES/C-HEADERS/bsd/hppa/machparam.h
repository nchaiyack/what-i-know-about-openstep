/* 
 * Copyright (c) 1993 NeXT, Inc. All rights reserved.
 *
 * HISTORY
 *
 * 12-Jul-93 Mac Gillon at NeXT
 *	Created from i386 version.
 */ 

#ifndef	_HPPA_MACHPARAM_
#define	_HPPA_MACHPARAM_

#import <mach/vm_param.h>

/*
 * Machine dependent 'constants'.
 */
#define	NBPG	PAGE_SIZE	/* bytes/page */
#define	PGOFSET	(NBPG-1)	/* byte offset into page */
#define	PGSHIFT	PAGE_SHIFT	/* LOG2(NBPG) */

#define	CLSIZE			1
#define	CLSIZELOG2		0

/* FIXME - we may not need this */

#define SSIZE		4		/* initial stack size/NBPG */
#define SINCR		4		/* increment of stack/NBPG */
#define USIZE		3 		/* number of ptes needed to map uarea */
    	    	    		    	/* USIZE must be sizeof(struct u)  */
    	    	    	    		/* rounded up to nearest page + 1 */

#define STACKSIZE 4			/* pages in kernel stack */
#define	UPAGES	(USIZE+STACKSIZE)	/* total pages in u-area */
					/* red zone is beyond this */

/*
 * Some macros for units conversion
 */
/* Core clicks (NeXT_page_size bytes) to segments and vice versa */
#define	ctos(x)	(x)
#define	stoc(x)	(x)

/* clicks to bytes */
#define	ctob(x)	((x) << PGSHIFT)

/* bytes to clicks */
#define	btoc(x)	((((unsigned)(x)+PGOFSET) >> PGSHIFT))

/*
 * Decode privilege level for HP Precision Architecture.
 */
#define PC_PRIV_MASK    3
#define PC_PRIV_KERN    0
#define PC_PRIV_USER    3

#define USERMODE(ssp)	(((((struct pcb_entry_state *)ssp)->es_pcoq_front) & PC_PRIV_MASK) != PC_PRIV_KERN)
#define BASEPRI(ssp)	(((struct pcb_entry_state *)ssp)->es_eiem == SPL0)

#if	defined(KERNEL) || defined(STANDALONE)
#define	DELAY(n) us_spin(n)

#else	defined(KERNEL) || defined(STANDALONE)
#define	DELAY(n)	{ register int N = (n); while (--N > 0); }
#endif	defined(KERNEL) || defined(STANDALONE)

#endif	_HPPA_MACHPARAM_
