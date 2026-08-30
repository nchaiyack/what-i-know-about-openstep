/* 
 * Mach Operating System
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
 
/* HISTORY
 *  7-Jan-93  Mac Gillon (mgillon) at NeXT
 *	Integrated POSIX changes
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)errno.h	7.1 (Berkeley) 6/4/86
 */

/* @(#)errno.h	2.1 88/05/18 4.0NFSSRC SMI;	from UCB 7.1 06/04/86	*/

#ifndef	_ERRNO_
#define	_ERRNO_	1

#ifndef KERNEL
	#include <ansi/standards.h>
#endif

/*
 * Error codes
 */

#if defined(_POSIX_SOURCE) || defined(_NEXT_SOURCE)
	#define	EPERM		 1	/* Not owner */
	#define	ENOENT		 2	/* No such file or directory */
	#define	ESRCH		 3	/* No such process */
	#define	EINTR		 4	/* Interrupted system call */
	#define	EIO		 5	/* I/O error */
	#define	ENXIO		 6	/* No such device or address */
	#define	E2BIG		 7	/* Arg list too long */
	#define	ENOEXEC		 8	/* Exec format error */
	#define	EBADF		 9	/* Bad file number */
	#define	ECHILD		10	/* No children */
	#define	EAGAIN		11	/* No more processes */
	#define	ENOMEM		12	/* Not enough core */
	#define	EACCES		13	/* Permission denied */
	#define	EFAULT		14	/* Bad address */
#endif /* _POSIX_SOURCE || _NEXT_SOURCE */

#ifdef _NEXT_SOURCE
	#define	ENOTBLK		15	/* Block device required */
#endif /* _NEXT_SOURCE */

#if defined(_POSIX_SOURCE) || defined(_NEXT_SOURCE)
	#define	EBUSY		16	/* Mount device busy */
	#define	EEXIST		17	/* File exists */
	#define	EXDEV		18	/* Cross-device link */
	#define	ENODEV		19	/* No such device */
	#define	ENOTDIR		20	/* Not a directory*/
	#define	EISDIR		21	/* Is a directory */
	#define	EINVAL		22	/* Invalid argument */
	#define	ENFILE		23	/* File table overflow */
	#define	EMFILE		24	/* Too many open files */
	#define	ENOTTY		25	/* Not a typewriter */
#endif /* _POSIX_SOURCE || _NEXT_SOURCE */

#ifdef _NEXT_SOURCE
	#define	ETXTBSY		26	/* Text file busy */
#endif /* _NEXT_SOURCE */

#if defined(_POSIX_SOURCE) || defined(_NEXT_SOURCE)
	#define	EFBIG		27	/* File too large */
	#define	ENOSPC		28	/* No space left on device */
	#define	ESPIPE		29	/* Illegal seek */
	#define	EROFS		30	/* Read-only file system */
	#define	EMLINK		31	/* Too many links */
	#define	EPIPE		32	/* Broken pipe */
#endif /* _POSIX_SOURCE || _NEXT_SOURCE */

#if defined(__STRICT_ANSI__) || defined(_NEXT_SOURCE) 
	/* math software */
	#define	EDOM		33	/* Argument too large */
	#define	ERANGE		34	/* Result too large */
#endif /* __STRICT_ANSI__ || _NEXT_SOURCE  */

#ifdef _NEXT_SOURCE
	/* non-blocking and interrupt i/o */
	#define	EWOULDBLOCK	35	/* Operation would block */
	#define	EINPROGRESS	36	/* Operation now in progress */
	#define	EALREADY	37	/* Operation already in */
					/* progress */
	
	/* ipc/network software */

		/* argument errors */
	#define	ENOTSOCK	38	/* Socket operation on */
					/* non-socket */
	#define	EDESTADDRREQ	39	/* Destination address */
					/* required */
	#define	EMSGSIZE	40	/* Message too long */
	#define	EPROTOTYPE	41	/* Protocol wrong type for */
					/* socket */
	#define	ENOPROTOOPT	42	/* Protocol not available */
	#define	EPROTONOSUPPORT	43	/* Protocol not supported */
	#define	ESOCKTNOSUPPORT	44	/* Socket type not supported */
	#define	EOPNOTSUPP	45	/* Operation not supported */
					/* on socket */
	#define	EPFNOSUPPORT	46	/* Protocol family */
					/* not supported */
	#define	EAFNOSUPPORT	47	/* Address family */
					/* not supported by */
					/* protocol family */
	#define	EADDRINUSE	48	/* Address already in use */
	#define	EADDRNOTAVAIL	49	/* Can't assign requested */
					/* address */

		/* operational errors */
	#define	ENETDOWN	50	/* Network is down */
	#define	ENETUNREACH	51	/* Network is unreachable */
	#define	ENETRESET	52	/* Network dropped */
					/* connection on reset */
	#define	ECONNABORTED	53	/* Software caused */
					/* connection abort */
	#define	ECONNRESET	54	/* Connection reset by peer */
	#define	ENOBUFS		55	/* No buffer space available */
	#define	EISCONN		56	/* Socket is already */
					/* connected */
	#define	ENOTCONN	57	/* Socket is not connected */
	#define	ESHUTDOWN	58	/* Can't send after */
					/* socket shutdown */
	#define	ETOOMANYREFS	59	/* Too many references: */
					/* can't splice */
	#define	ETIMEDOUT	60	/* Connection timed out */
	#define	ECONNREFUSED	61	/* Connection refused */

		/* */
	#define	ELOOP		62	/* Too many levels of */
					/* symbolic links */
#endif /* _NEXT_SOURCE */

#if defined(_POSIX_SOURCE) || defined(_NEXT_SOURCE)
	#define	ENAMETOOLONG	63	/* File name too long */
#endif /* _POSIX_SOURCE || _NEXT_SOURCE */

#ifdef _NEXT_SOURCE
	/* should be rearranged */
	#define	EHOSTDOWN	64	/* Host is down */
	#define	EHOSTUNREACH	65	/* No route to host */
#endif /* _NEXT_SOURCE */

#if defined(_POSIX_SOURCE) || defined(_NEXT_SOURCE)
	#define	ENOTEMPTY	66	/* Directory not empty */
#endif /* _POSIX_SOURCE || _NEXT_SOURCE */

#ifdef _NEXT_SOURCE
	/* quotas & mush */
	#define	EPROCLIM	67	/* Too many processes */
	#define	EUSERS		68	/* Too many users */
	#define	EDQUOT		69	/* Disc quota exceeded */

	/* SUN_NFS */
	/* Network File System */
	#define	ESTALE		70	/* Stale NFS file handle */
	#define	EREMOTE		71	/* Too many levels of */
					/* remote in path */
	/* SUN_NFS */
#endif /* _NEXT_SOURCE */

#if defined(_POSIX_SOURCE) || defined(_NEXT_SOURCE)
	/* SUN_LOCK */
	/* SystemV Record Locking */
	#define EDEADLK         78	/* Deadlock condition. */
	#define ENOLCK          79	/* No record locks available. */
	/* SUN_LOCK */
#endif /* _POSIX_SOURCE || _NEXT_SOURCE */

#ifdef _NEXT_SOURCE
	/* Intelligent device errors */
	#define	EPWROFF		80	/* Device power is off */
	#define	EDEVERR		81	/* Device error, */
					/* e.g. paper out */
	#define	ENOINIT		82	/* Device not initialized */

	/* Program loading errors */
	#define EBADEXEC	83	/* Bad executable */
	/* Program loading errors */
	#define EBADARCH	84	/* Bad CPU type in executable */
	#define ESHLIBVERS	85	/* Shared library version mismatch */
	#define EBADMACHO	86	/* Malformed Macho file */
#endif /* _NEXT_SOURCE */

#ifdef _POSIX_SOURCE
	#define	ENOSYS		87	/* Function not implemented. */
#endif	/* _POSIX_SOURCE */

#if defined(_NEXT_SOURCE) && defined(__STDC__) && \
	  !defined(KERNEL) && !defined(__ASSEMBLER__)
	#ifdef __STRICT_BSD__
		extern int errno;
	#else
		#import <stddef.h>
	#endif /* __STRICT_BSD__ */

	extern void perror(const char *);
	extern char *sys_errlist[];
	extern int sys_nerr;
#endif /* _NEXT_SOURCE && __STDC__ && !KERNEL && !__ASSEMBLER__ */
#endif /* _ERRNO_ */
