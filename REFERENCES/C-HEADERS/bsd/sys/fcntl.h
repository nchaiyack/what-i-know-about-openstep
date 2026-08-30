/*	@(#)fcntl.h	2.2 88/05/26 NFSSRC4.0 SMI; from UCB 5.1 85/05/30	*/
/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 * HISTORY
 *  7-Jan-93  Mac Gillon (mgillon) at NeXT
 *	Integrated POSIX support
 *
 * 27-Sep-89  Morris Meyer (mmeyer) at NeXT
 *	NFS 4.0 Changes: addition of FSYNC flag for synchronous writes
 *
 * 19-Oct-87  Peter King (king) at NeXT, Inc.
 *	Original Sun file.  Moved FNOSPC
 */

#ifndef __FCNTL_HEADER__
#define __FCNTL_HEADER__

#ifndef KERNEL
	#include <standards.h>
#endif

#if defined(_POSIX_SOURCE) && !defined(KERNEL)
	#include <sys/types.h>
#endif	/* _POSIX_SOURCE  & !KERNEL */

/*
 * Flag values accessible to open(2) and fcntl(2)
 *  (The first three can only be set by open)
 */
#if defined(_POSIX_SOURCE) || defined(_NEXT_SOURCE)
	#define	O_RDONLY	000
	#define	O_WRONLY	001
	#define	O_RDWR		002

	#define	O_APPEND	00010	/* append (writes guaranteed */
					/* at the end) */
	#define	O_CREAT		01000	/* open with file create */
	#define	O_TRUNC		02000	/* open with truncation */
	#define	O_EXCL		04000	/* error on create if file */
					/* exists */
#endif /* _POSIX_SOURCE || _NEXT_SOURCE */

#ifdef _POSIX_SOURCE
	#define O_ACCMODE	003	/* mask for file access modes */
	#define O_NONBLOCK	00004	/* non-blocking open */
	#define O_NOCTTY	00020	/* do not acquire a */
					/* controlling terminal */
#endif /* _POSIX_SOURCE */

#ifdef _NEXT_SOURCE
	#define	O_NDELAY	FNDELAY	/* Non-blocking I/O */
	#define	O_SYNC		FSYNC	/* Synchronous writes */

	#ifdef NeXT
		#define	O_POPUP	   0x80000000   /* force window to */
						/* popup on open */
		#define	O_NO_MFS   0x40000000   /* don't use mapped */
						/* files */
		#define	O_ALERT	   0x20000000	/* small, clean popup */
						/* window */
	#endif /* NeXT */
#endif	/* _NEXT_SOURCE */

/* flags for F_GETFL, F_SETFL-- needed by <sys/file.h> */
#ifdef _NEXT_SOURCE
	#define	FNDELAY		00004		/* non-blocking reads */
	#define	FAPPEND		00010		/* append on each */
						/* write */
	#define	FASYNC		00100		/* signal pgrp when */
						/* data */
						/* ready */
	#define	FCREAT		01000		/* create if */
						/* nonexistant */
	#define	FTRUNC		02000		/* truncate to zero */
						/* length */
	#define	FEXCL		04000		/* error if already */
						/* created */
	/* CS_RPAUSE */
	#define	FNOSPC		010000		/* disable resource */
						/* pause */
						/* for file */
	/* CS_RPAUSE */
	#define	FSYNC		01000000	/* Synchronous writes */

	/* fcntl(2) requests */
	#define	F_GETOWN 	5		/* Get owner */
	#define F_SETOWN 	6		/* Set owner */

#endif /* _NEXT_SOURCE */

/* fcntl(2) requests */
#if defined(_POSIX_SOURCE) || defined(_NEXT_SOURCE)
	#define	F_DUPFD	0	/* Duplicate fildes */
	#define	F_GETFD	1	/* Get fildes flags */
	#define	F_SETFD	2	/* Set fildes flags */
	#define	F_GETFL	3	/* Get file flags */
	#define	F_SETFL	4	/* Set file flags */
	#define F_GETLK  7      /* Get record-locking information */
	#define F_SETLK  8      /* Set or Clear a record-lock */
				/* (Non-Blocking) */
	#define F_SETLKW 9      /* Set or Clear a record-lock */
				/* (Blocking) */
#endif /* _POSIX_SOURCE || _NEXT_SOURCE */

#if POSIX_KERN
	#define _POSIX_FILE_FLAGS	(O_NO_MFS | FNOSPC)
#endif  /* POSIX_KERN */

/* access(2) requests */
#if defined(_POSIX_SOURCE) || defined(_NEXT_SOURCE)
	#define	F_OK		0	/* does file exist */
	#define	X_OK		1	/* is it executable by caller */
	#define	W_OK		2	/* writable by caller */
	#define	R_OK		4	/* readable by caller */
#endif /* _POSIX_SOURCE || _NEXT_SOURCE */

/* System-V record-locking options */
/* lockf(2) requests */
#ifdef _NEXT_SOURCE 
	#define F_ULOCK 0       /* Unlock a previously locked region */
	#define F_LOCK  1       /* Lock a region for exclusive use */ 
	#define F_TLOCK 2       /* Test and lock a region for */
				/* exclusive use */
	#define F_TEST  3       /* Test a region for other processes locks */
#endif /* _NEXT_SOURCE */

/* fcntl(2) flags (l_type field of flock structure) */
#if defined(_POSIX_SOURCE) || defined(_NEXT_SOURCE)
	#define F_RDLCK 1       /* read lock */
	#define F_WRLCK 2       /* write lock */
	#define F_UNLCK 3       /* remove lock(s) */
#endif /* _POSIX_SOURCE || _NEXT_SOURCE */

#ifdef _POSIX_SOURCE
	#define FD_CLOEXEC	01	/* Close on exec flag */
#endif 	/* _POSIX_SOURCE */


/* file segment locking set data type - information passed to 
 * system by user */
struct flock {
#if defined(_POSIX_SOURCE) || defined(_NEXT_SOURCE)
       	short   l_type;		/* F_RDLCK, F_WRLCK, or F_UNLCK */
       	short   l_whence;	/* flag to choose starting offset */
#if defined(_POSIX_SOURCE) && !defined(KERNEL)
       	off_t	l_start;	/* relative offset, in bytes */
       	off_t	l_len;          /* length, in bytes; 0 means lock */
				/* to EOF */
#else	/* _POSIX_SOURCE && !KERNEL */
       	long    l_start;	/* relative offset, in bytes */
       	long    l_len;          /* length, in bytes; 0 means lock */
				/* to EOF */
#endif	/* _POSIX_SOURCE && !KERNEL */
#if defined(_POSIX_SOURCE)
       	pid_t	l_pid;		/* returned with F_GETLK */	
#else	/* _POSIX_SOURCE */
       	short   l_pid;		/* returned with F_GETLK */
#endif	/* _POSIX_SOURCE */
       	short   l_xxx;		/* reserved for future use */
#endif /* _POSIX_SOURCE) || _NEXT_SOURCE */
};

#if defined(_POSIX_SOURCE) && !defined(KERNEL)
	#ifdef __STDC__
		extern creat(const char *path, mode_t mode);
		extern fcntl(int fildes, int cmd, ...);
		extern open(const char *path, int oflag, ...);
	#else
		extern creat();
		extern fcntl();
		extern open();
	#endif	/* __STDC__ */
#endif /* _POSIX_SOURCE && !KERNEL */
#endif !__FCNTL_HEADER__
