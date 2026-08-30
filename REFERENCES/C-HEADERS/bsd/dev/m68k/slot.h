/* 
 * HISTORY
 * 27-May-89  Avadis Tevanian, Jr. (avie) at NeXT, Inc.
 *	Created.
 */

#ifndef	_M68K_DEV_SLOT_
#define	_M68K_DEV_SLOT_

#define SLOTSIZE	0x10000000		/* each physical slot is
						   really two of these */
#define SLOTCOUNT	4

#define	SLOTIOCGADDR	_IOR('s', 0, int)	/* get address of slot space */
#define	SLOTIOCDISABLE	_IO('s', 3)		/* disable translation */

#endif	_M68K_DEV_SLOT_
