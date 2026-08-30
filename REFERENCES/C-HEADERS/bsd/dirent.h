/* Copyright 1993 NeXT Computer, Inc. - WMG */

#ifndef _DIRENT_H
#define _DIRENT_H

#include <standards.h>

#ifdef _POSIX_SOURCE
	#include <sys/dir.h>		/* for struct DIR and */
					/* function declarations. */
	#include <sys/dirent.h>		/* for struct dirent */
#endif /* _POSIX_SOURCE */
#endif /* _DIRENT_H */
