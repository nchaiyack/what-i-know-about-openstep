/* Copyright 1993, NeXT Computer Inc.  WMG 7-Jan-93 */

#ifndef _UTSNAME_H
	#define _UTSNAME_H

	#include <standards.h>

	#ifdef _POSIX_SOURCE
		#define	_SYS_NAMELEN	32

		struct	utsname {
			char	sysname[_SYS_NAMELEN];	/* Name of OS */
							/* implementation */
			char	nodename[_SYS_NAMELEN];	/* Name of this node */
							/* in a network */
			char	release[_SYS_NAMELEN];	/* Release level of */
							/* OS implementation */
			char	version[_SYS_NAMELEN];	/* Version level of */
							/* OS implementation */
			char	machine[_SYS_NAMELEN];	/* Hardware name */
		};

		#if !POSIX_KERN
			#ifdef __STDC__
				extern int uname(struct utsname *name);
			#else
				extern int uname();
			#endif	/* __STDC__ */
		#endif	/* !POSIX_KERN */
	#endif  /* _POSIX_SOURCE */
#endif	/* _UTSNAME_H */
