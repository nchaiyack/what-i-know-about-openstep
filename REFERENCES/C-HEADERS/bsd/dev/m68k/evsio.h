/******************************************************************************
	evsio.h
	Ioctl calls for the events status driver
	Leovitch 09Dec88
	
	Copyright 1988 NeXT, Inc.
	
	Modified:
	
	24Aug89 Ted  ANSI prototyping.
	07Mar90 Ted  Added Morris' new EVSIOCADS ioctl.
	22May90 Ted  Added wait cursor-related ioctls.
	22Dec90 Ted  Added EVSIOSADB and EVSIOCADB, autodim brightness ioctls.
	11Oct91 mpaque Added status and autodim control ioctls. 
******************************************************************************/

#ifndef _M68K_DEV_EVSIO_
#define _M68K_DEV_EVSIO_

#import <sys/ioctl.h>
/*
 * We have both client and server API definitions for event structures.
 * What's actually used in these ioctl() calls are common to both sides.
 * Other things may differ.  When we build the Kit wrapper around these ioctls,
 * in the hope that they will go away in Release 4.0, we need to use the client
 * event API.  Hence this switch...
 */
#if !defined(_DO_NOT_IMPORT_EVENTS_)
#import <bsd/dev/m68k/event.h>
#endif
#import <bsd/dev/ev_types.h>	/* Public type definitions. */

/* For backwards source compatability */
#ifndef MAXMOUSESCALINGS
/* Maximum length of SetMouseScaling arrays */
#define MAXMOUSESCALINGS NX_MAXMOUSESCALINGS
#endif MAXMOUSESCALINGS

struct evsioPoint {
    short x, y;
};

/* Data structures for private low level API */
struct evsioLLEvent {
    int type;
    struct evsioPoint location;
    NXEventData data;
};

typedef struct evsioLLEvent _NXLLEvent;

/*
 * Glue for the current ioctl call implementation of NXEventSystemInfo.
 * THIS WILL GO AWAY
 */
struct _NXEventSystemInfo_ioctl
{
	int			flavor;	/* Flavor of info request */
	NXEventSystemInfoType	data;	/* Address of data in user space */
	unsigned int		size;	/* Size of data in ints */
};


/* General ioctls - PRIVATE API */

#define EVSIOLLPE _IOW('e', 2, struct evsioLLEvent) /* Low-level Post Event */

/* Post Event for ptr device.  This should update the cursor position. */
#define EVSIOPTRLLPE _IOW('e', 3, struct evsioLLEvent)

/* Keyboard-related ioctls */

#define EVSIOSKR  _IOW('e', 10, int)	/* SetKeyRepeat */
#define EVSIOCKR  _IOR('e', 11, int)	/* CurrentKeyRepeat */
#define EVSIOSIKR _IOW('e', 12, int)	/* SetInitialKeyRepeat */
#define EVSIOCIKR _IOR('e', 13, int)	/* CurrentInitialKeyRepeat */
#define EVSIOSKM  _IOW('e', 14, struct evsioKeymapping)
					/* SetKeyMapping */
#define	EVSIOCKM  _IOWR('e', 15, struct evsioKeymapping)
					/* CurrentKeyMapping */
#define	EVSIOCKML _IOR('e', 16, int)	/* CurrentKeyMappingLength */
#define EVSIORKBD _IO('e', 17)		/* ResetKeyboard */

/* WaitCursor-related ioctls */

#define EVSIOSWT _IOW('e', 40, int)	/* SetWaitThreshold */
#define EVSIOCWT _IOR('e', 41, int)	/* CurrentWaitThreshold */
#define EVSIOSWS _IOW('e', 42, int)	/* SetWaitSustain */
#define EVSIOCWS _IOR('e', 43, int)	/* CurrentWaitSustain */
#define EVSIOSWFR _IOW('e', 44, int)	/* SetWaitFrameRate */
#define EVSIOCWFR _IOR('e', 45, int)	/* CurrentWaitFrameRate */

/* Mouse-related ioctls */

#define	EVSIOSCT  _IOW('e', 70, int)	/* SetClickTime */
#define	EVSIOCCT  _IOR('e', 71, int)	/* CurrentClickTime */
#define	EVSIOSCS  _IOW('e', 72, struct evsioPoint) /* SetClickSpace */
#define	EVSIOCCS  _IOR('e', 73, struct evsioPoint) /* CurrentClickSpace */
#define	EVSIOSMS  _IOW('e', 74, struct evsioMouseScaling) /* SetMouseScaling */
#define	EVSIOCMS  _IOR('e', 75, struct evsioMouseScaling) /* CurrentMouseScaling */
#define EVSIORMS  _IO('e', 76)		/* ResetMouse */
#define EVSIOSADT _IOW('e', 77, int)	/* SetAutoDimTime */
#define EVSIOCADT _IOR('e', 78, int)	/* CurrentAutoDimTime */
#define EVSIOSMH  _IOW('e', 79, int)	/* SetMouseHandedness */
#define EVSIOCMH  _IOR('e', 80, int)	/* CurrentMouseHandedness */
#define EVSIOSMBT _IOW('e', 81, int)	/* SetMouseButtonsTied */
#define EVSIOCMBT _IOR('e', 82, int)	/* CurrentMouseButtonsTied */
#define EVSIOCADS _IOR('e', 83, int)	/* AutoDimmed */
#define EVSIOGADT _IOR('e', 84, int)	/* GetAutoDimTime */
#define EVSIOGDADT _IOR('e', 85, int)	/* GetDeltaAutoDimTime */
#define EVSIOSADS _IOW('e', 86, int)	/* Force AutoDimmed on or off */
#define EVSIOIDLE _IOR('e', 87, int)	/* Used by NXIdleTime */

/* Device control ioctls.  Note that these set the current value
   but do not affect parameter RAM.  */

#define EVSIOSB	  _IOW('e', 100, int)	/* Set Brightness */
#define EVSIOCB	  _IOR('e', 101, int)	/* Current Brightness */
#define EVSIOSA	  _IOW('e', 102, int)	/* Set Attenuation */
#define EVSIOCA   _IOR('e', 103, int)	/* Current Attenuation */
#define EVSIOSADB _IOW('e', 104, int)	/* Set AutoDim Brightness */
#define EVSIOCADB _IOR('e', 105, int)	/* Current AutoDim Brightness */

/*
 * Device status ioctl.  This will go away in the next major release, with the 
 * rest of these ioctls.
 */
#define	EVSIOINFO  _IOWR('e', 106, struct _NXEventSystemInfo_ioctl)

#endif _M68K_DEV_EVSIO_
