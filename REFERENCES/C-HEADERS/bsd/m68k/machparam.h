/* 
 * Copyright (c) 1987 NeXT, Inc.
 *
 * HISTORY
 * 21-Nov-88  Avadis Tevanian (avie) at NeXT
 *	Moved assertion definitions to machine independent <kern/assert.h>.
 *
 * 09-Nov-86  John Seamons (jks) at NeXT
 *	Ported to NeXT.
 */ 

#ifndef	_M68K_MACHPARAM_
#define	_M68K_MACHPARAM_

#import <mach/m68k/vm_param.h>

/*
 * Machine dependent constants for NeXT m68k.
 */
#if	KERNEL
#define	NBPG	m68k_page_size		/* bytes/page */
#else	KERNEL
#define	NBPG	M68K_MAX_PAGE_SIZE	/* must be constant for utilities */
#endif	KERNEL
#define	PGOFSET	m68k_page_mask		/* byte offset into page */
#define	PGSHIFT	m68k_page_shift		/* LOG2(NBPG) */

#define	CLSIZE			1
#define	CLSIZELOG2		0
#define	M68K_MIN_CLBYTES	(CLSIZE * M68K_MIN_PAGE_SIZE)

/*
 * Some macros for units conversion
 */
/* Core clicks (m68k_page_size bytes) to segments and vice versa */
#define	ctos(x)	(x)
#define	stoc(x)	(x)

/* clicks to bytes */
#define	ctob(x)	((x) << m68k_page_shift)

/* bytes to clicks */
#define	btoc(x)	((((unsigned)(x)+m68k_page_mask) >> m68k_page_shift))

/*
 * Macros to decode processor status word.
 */
#define	USERMODE(ps)	(((ps) & SR_SUPER) == 0)
#define	BASEPRI(ps)	(((ps) & SR_IPL) == 0)

#if	defined(KERNEL) || defined(STANDALONE)
#define	DELAY(n) delay(n)

#else	defined(KERNEL) || defined(STANDALONE)
#define	DELAY(n)	{ register int N = (n); while (--N > 0); }
#endif	defined(KERNEL) || defined(STANDALONE)

#endif	_M68K_MACHPARAM_
