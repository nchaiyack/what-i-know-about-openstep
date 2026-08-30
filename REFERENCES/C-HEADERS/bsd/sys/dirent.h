/*	@(#)dirent.h	2.1 88/05/18 4.0NFSSRC SMI	*/

/* 
 * Copyright (c) 1988 by Sun Microsystems, Inc.
 *	1.2 88/02/08 SMI 
 */

/*
 * HISTORY
 *  7-Jan-93  Mac Gillon (mgillon) at NeXT
 *	Integrated POSIX changes
 *
 * 19-Dec-88  Peter King (king) at NeXT
 *	Original Sun source: NFSSRC4.0
 */

/*
 * Filesystem-independent directory information. 
 * Directory entry structures are of variable length.
 * Each directory entry is a struct dirent containing its file number, the
 * offset of the next entry (a cookie interpretable only the filesystem 
 * type that generated it), the length of the entry, and the length of the 
 * name contained in the entry.  These are followed by the name. The
 * entire entry is padded with null bytes to a 4 byte boundary. All names 
 * are guaranteed null terminated. The maximum length of a name in a 
 * directory is MAXNAMLEN, plus a null byte.
 */

#ifndef _SYS_DIRENT_H 
#define _SYS_DIRENT_H 

#ifndef KERNEL
	#include <standards.h> 
#endif

#if defined(_POSIX_SOURCE) && !defined(KERNEL)
	#include <limits.h>			/* for NAME_MAX */
#endif	/* POSIX_SOURCE && !KERNEL */
	
#if defined(_NEXT_SOURCE)
	#ifndef _MAXNAMLEN
		#define	_MAXNAMLEN
		#define	MAXNAMLEN	255
	#endif /* _MAXNAMLEN */
#endif	/* _NEXT_SOURCE */

#if defined(_POSIX_SOURCE) || defined(_NEXT_SOURCE)

	struct	dirent {
		off_t   d_off;			/* offset of next */
						/* disk directory */
						/* entry */
		unsigned long	d_fileno;	/* file number of */
						/* entry */
		unsigned short	d_reclen;	/* length of this */
						/* record */
		unsigned short	d_namlen;	/* length of string */
						/* in d_name */
	#if defined(_POSIX_SOURCE) && !KERNEL
		char	d_name[NAME_MAX + 1];	/* name (up to */
						/* NAME_MAX + 1) */
	#else
		char	d_name[MAXNAMLEN + 1];	/* name (up to */
						/* MAXNAMLEN + 1) */
	#endif	/* _POSIX_SOURCE  && !KERNEL */
	};
#endif  /* _POSIX_SOURCE || _NEXT_SOURCE */

#ifdef _NEXT_SOURCE

	/* 
	 * The macro DIRENTSIZ(dp) gives the minimum amount of space
	 * required to represent a directory entry.  For any directory
	 * entry dp->d_reclen >= DIRENTSIZ(dp). Specific filesystem
	 * types may use this use this macro to construct the value
	 * for d_reclen.
	 */
	#define DIRENTSIZ(dp)  \
		(((sizeof (struct dirent) - (MAXNAMLEN+1) + \
		   ((dp)->d_namlen+1)) + 3) & ~3)

#endif /* _NEXT_SOURCE */
#endif /* _SYS_DIRENT_H  */
