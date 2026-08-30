/******************************************************************************
	event.h (PostScript side version)
	
	CONFIDENTIAL
	Copyright (c) 1992 NeXT Computer, Inc. as an unpublished work.
	All Rights Reserved.

	Created jpasqua 22 Sept 1992

	Modified:
******************************************************************************/

#ifndef _I386_DEV_EVENT_
#define _I386_DEV_EVENT_

#import <bsd/dev/event.h>	/* Portable event defs */
/*
 * Device-dependent bits within event.flags
 * (The bits probably won't change, but may not be supported by all hardware)
 *
 * Bletch!  This stuff is also defined in dpsclient/event.h!
 * That's totally inappropriate for such machine dependent
 * stuff.  I guarantee we can't support this for all possible
 * keyboards. (Hint: What do NX_NEXTLCMDKEYMASK and
 * NX_NEXTRCMDKEYMASK mean on the keyboards with a single
 * Command bar?)
 */

#ifndef NX_NEXTCTLKEYMASK
#define	NX_NEXTCTLKEYMASK	0x00000001
#endif

#ifndef NX_NEXTLSHIFTKEYMASK
#define	NX_NEXTLSHIFTKEYMASK	0x00000002
#endif

#ifndef NX_NEXTRSHIFTKEYMASK
#define	NX_NEXTRSHIFTKEYMASK	0x00000004
#endif

#ifndef NX_NEXTLCMDKEYMASK
#define	NX_NEXTLCMDKEYMASK	0x00000008
#endif

#ifndef NX_NEXTRCMDKEYMASK
#define	NX_NEXTRCMDKEYMASK	0x00000010
#endif

#ifndef NX_NEXTLALTKEYMASK
#define	NX_NEXTLALTKEYMASK	0x00000020
#endif

#ifndef NX_NEXTRALTKEYMASK
#define	NX_NEXTRALTKEYMASK	0x00000040
#endif

/* NX_STYLUSPROXIMITYMASK	0x00000080	RESERVED */
/* NX_NONCOALSESCEDMASK		0x00000100	RESERVED */


#endif _I386_DEV_EVENT_

