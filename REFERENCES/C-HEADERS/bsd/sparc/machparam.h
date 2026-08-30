/* 
 * Copyright (c) 1994 NeXT, Inc. All rights reserved.
 *
 * HISTORY
 *
 * 21-Apr-1994 Mac Gillon at NeXT
 *	Created from i386 version.
 */ 

#ifndef	_SPARC_MACHPARAM_
#define	_SPARC_MACHPARAM_

#import <mach/vm_param.h>

/*
 * Machine dependent 'constants'.
 */
#define	NBPG	PAGE_SIZE	/* bytes/page */
#define	PGOFSET	(NBPG-1)	/* byte offset into page */
#define	PGSHIFT	PAGE_SHIFT	/* LOG2(NBPG) */

#define	CLSIZE			1
#define	CLSIZELOG2		0

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


#if	defined(KERNEL) || defined(STANDALONE)
#define	DELAY(n) us_spin(n)

#else	defined(KERNEL) || defined(STANDALONE)
#define	DELAY(n)	{ register int N = (n); while (--N > 0); }
#endif	defined(KERNEL) || defined(STANDALONE)

/*
 * The following symbols are required for the Sun4m architecture.
 *	OPENPROMS	# Open Boot Prom interface
 */
#define	OPENPROMS

#endif	_SPARC_MACHPARAM_
