/* 
 * HISTORY
 * 05-Mar-89  Avadis Tevanian, Jr. (avie) at NeXT
 *	Make MAXDSIZ infinity.
 *
 * 12-Aug-87  John Seamons (jks) at NeXT
 *	Ported to NeXT.
 */ 

#ifndef	_BSD_I386_VMPARAM_H_
#define	_BSD_I386_VMPARAM_H_ 1

#import <sys/resource.h>


/*
 * Virtual memory related constants, all in bytes
 */
#ifndef DFLDSIZ
#define	DFLDSIZ		(6*1024*1024)		/* initial data size limit */
#endif
#ifndef MAXDSIZ
#define	MAXDSIZ		(RLIM_INFINITY)		/* max data size */
#endif
#ifndef	DFLSSIZ
#define	DFLSSIZ		(512*1024)		/* initial stack size limit */
#endif
#ifndef	MAXSSIZ
#define	MAXSSIZ		MAXDSIZ			/* max stack size */
#endif
#ifndef	DFLCSIZ
#define DFLCSIZ		(0)			/* initial core size limit */
#endif
#ifndef	MAXCSIZ
#define MAXCSIZ		(RLIM_INFINITY)		/* max core size */
#endif	MAXCSIZ

#endif	_BSD_I386_VMPARAM_H_
