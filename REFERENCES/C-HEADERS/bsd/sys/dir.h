/* 
 * Mach Operating System
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 *
 * HISTORY
 *  7-Jan-93  Mac Gillon (mgillon) at NeXT
 *	Integrated POSIX changes
 *
 * 27-Sep-89  Morris Meyer (mmeyer) at NeXT
 *	NFS 4.0 Changes.
 *
 * 13-Feb-88  John Seamons (jks) at NeXT
 *	NeXT: increased DEV_BSIZE from 512 to 1024.
 *
 * 06-Jan-88  Jay Kistler (jjk) at Carnegie Mellon University
 *	Added declarations for __STDC__.
 *
 * 10-Aug-87  Peter King (king) at NeXT
 *	SUN_VFS:  Change d_ino to d_fileno.  Add dd_bbase, dd_entno, dd_bsize,
 *	      and dd_buf fields.
 *
 * 24-Jul-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Prevent repeated inclusion.
 *
 */
 
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)dir.h	7.1 (Berkeley) 6/4/86
 */

/* @(#)dir.h	1.4 87/06/02 3.2/4.3NFSSRC */

#ifndef	_DIR_
	#define	_DIR_	1

	#if !defined(KERNEL) && defined(_POSIX_SOURCE)
		#include <standards.h>
	#endif
	#import <sys/types.h>

/* SUN_VFS */
/*

 * Filesystem-independent directory information.
 * Directory entry structures are of variable length.
 * Each directory entry is a struct direct containing its file number,
 * the offset of the next entry (a cookie interpretable only the
 * filesystem type that generated it), the length of the entry, and
 * the length of the name contained in the entry.  These are followed
 * by the name. The entire entry is padded with null bytes to a 4 byte
 * boundary. All names are guaranteed null terminated. The maximum
 * length of a name in a directory is MAXNAMLEN, plus a null byte.
 * Note: SVID style filesystem-independant directory routines are
 * supported by the files /usr/include/dirent.h and
 * /usr/include/sys/dirent.h.
 */
/* else SUN_VFS */
/*
 * A directory consists of some number of blocks of DIRBLKSIZ
 * bytes, where DIRBLKSIZ is chosen such that it can be transferred
 * to disk in a single atomic operation (e.g. 512 bytes on most machines).
 *
 * Each DIRBLKSIZ byte block contains some number of directory entry
 * structures, which are of variable length.  Each directory entry has
 * a struct direct at the front of it, containing its inode number,
 * the length of the entry, and the length of the name contained in
 * the entry.  These are followed by the name padded to a 4 byte boundary
 * with null bytes.  All names are guaranteed null terminated.
 * The maximum length of a name in a directory is MAXNAMLEN.
 *
 * The macro DIRSIZ(dp) gives the amount of space required to represent
 * a directory entry.  Free space in a directory is represented by
 * entries which have dp->d_reclen > DIRSIZ(dp).  All DIRBLKSIZ bytes
 * in a directory block are claimed by the directory entries.  This
 * usually results in the last entry in a directory having a large
 * dp->d_reclen.  When entries are deleted from a directory, the
 * space is returned to the previous entry in the same directory
 * block by increasing its dp->d_reclen.  If the first entry of
 * a directory block is free, then its dp->d_ino is set to 0.
 * Entries other than the first in a directory do not normally have
 * dp->d_ino set to 0.
 */
/* end SUN_VFS */
/* so user programs can just include dir.h */
#if !defined(KERNEL) && !defined(DEV_BSIZE) && defined(_NEXT_SOURCE)
	#if !NeXT
		#define	DEV_BSIZE	512
	#endif	/* NeXT */
#endif	/* !KERNEL && !DEV_BSIZE && _NEXT_SOURCE */

#ifdef _NEXT_SOURCE
	#if NeXT
		#define DIRBLKSIZ	1024
	#else
		#define DIRBLKSIZ	DEV_BSIZE
	#endif	/* NeXT */
#endif /* _NEXT_SOURCE */

#ifdef _NEXT_SOURCE

	#ifndef _MAXNAMLEN
		#define _MAXNAMLEN
		#define	MAXNAMLEN	255
	#endif  /* _MAXNAMLEN */

	struct	direct {
	/* SUN_VFS */
		u_long  d_fileno;               /* file number of */
							/* entry */
	/* SUN_VFS */
	/*	u_long d_ino; */		/* inode number of */
						/* entry SUN_VFS */
		u_short	d_reclen;		/* length of this */
						/* record */
		u_short	d_namlen;		/* length of string */
						/* in d_name */
		char	d_name[MAXNAMLEN + 1];	/* name must be no */
						/* longer than this */
	};

	/*
	 * The DIRSIZ macro gives the minimum record length which will
	 * hold the directory entry.  This requires the amount of space
	 * in struct direct without the d_name field, plus enough space
	 * for the name with a terminating null byte (dp->d_namlen+1),
	 * rounded up to a 4 byte boundary.
	 */
	#undef DIRSIZ
	#define DIRSIZ(dp) \
		((sizeof (struct direct) - (MAXNAMLEN+1)) + \
		(((dp)->d_namlen+1 + 3) &~ 3))
#endif 	/* _NEXT_SOURCE */

#ifndef KERNEL
	/* SUN_VFS */
	#ifdef _NEXT_SOURCE
		#define d_ino   d_fileno	/* compatability */
	#endif /* _NEXT_SOURCE */
	/* SUN_VFS */

	/*
	 * Definitions for library routines operating on directories.
	 */

	#if defined(_POSIX_SOURCE) || defined(_NEXT_SOURCE)
		typedef struct _dirdesc {
			int	dd_fd;
			long	dd_loc;
			long	dd_size;
		/* SUN_VFS */
			long	dd_bbase;
			long	dd_entno;
			long	dd_bsize;
			char	*dd_buf;
		/* SUN_VFS */
		/*	char	dd_buf[DIRBLKSIZ]; SUN_VFS */
		} DIR;
	#endif  /* _POSIX_SOURCE || _NEXT_SOURCE */

	#ifdef _NEXT_SOURCE
		#ifndef NULL
			#define NULL ((void *)0)
		#endif /* NULL */
	#endif /* _NEXT_SOURCE */


	#if defined(_POSIX_SOURCE) || defined(_NEXT_SOURCE)
		#ifdef __STDC__
			extern	DIR *opendir(const char *dirname);
			#if defined(_POSIX_SOURCE)
				extern	struct dirent *readdir(DIR *dirp);
				extern	void rewinddir(DIR *dirp);
			#else
				extern	struct direct *readdir(DIR *dirp);
				#define rewinddir(dirp)	\
					seekdir((dirp), (long)0)
			#endif 	/* _POSIX_SOURCE */
			extern	int closedir(DIR *dirp);

			#ifdef _NEXT_SOURCE
				extern void seekdir(DIR *, long);
				extern long telldir(DIR *);
				extern int \
					scandir(const char *, \
						struct direct ***, \
						int (*)(), int (*)());
				extern int \
					alphasort (struct direct **, \
						struct direct **);
			#endif /* _NEXT_SOURCE */
		#else /* __STDC__ */
			extern	DIR *opendir();
			#if defined(_POSIX_SOURCE)
				extern	struct dirent *readdir();
				extern  void rewinddir();
			#else
				extern	struct direct *readdir();
				#define rewinddir(dirp)	\
					seekdir((dirp), (long)0)
			#endif  /* _POSIX_SOURCE */
			extern	int closedir();

			#ifdef _NEXT_SOURCE
				extern	void seekdir();
				extern	long telldir();
				extern	int scandir();
				extern	int alphasort();
			#endif /* _NEXT_SOURCE */
		#endif /* __STDC__ */
	#endif /* _POSIX_SOURCE || _NEXT_SOURCE */
#endif /* !KERNEL */

#ifdef KERNEL
	/*
	 * Template for manipulating directories.
	 * Should use struct direct's, but the name field
	 * is MAXNAMLEN - 1, and this just won't do.
	 */
	struct dirtemplate {
		u_long	dot_ino;
		short	dot_reclen;
		short	dot_namlen;
		char	dot_name[4];	/* must be multiple of 4 */
		u_long	dotdot_ino;
		short	dotdot_reclen;
		short	dotdot_namlen;
		char	dotdot_name[4];	/* ditto */
	};
#endif /* KERNEL */
#endif /* _DIR_ */
