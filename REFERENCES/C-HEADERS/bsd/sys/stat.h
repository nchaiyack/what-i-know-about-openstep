/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	stat.h,v $
 *  7-Jan-93  Mac Gillon (mgillon) at NeXT
 *	Integrated POSIX support
 *
 * 22-Feb-90  Gregg Kellogg (gk) at NeXT
 *	Added back in STAT_BSIZE, STAT_BSHIFT, btosb, and sbtob
 *
 * Revision 2.5  89/04/22  15:32:24  gm0w
 * 	Removed MACH_VFS changes.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.4  89/03/09  22:07:51  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  17:56:28  gm0w
 * 	Made items previously conditional on CMUCS and MACH_VFS
 * 	be unconditional.
 * 	[89/02/14            mrt]
 * 
 * Revision 2.2  89/01/18  01:19:13  jsb
 * 	Vnode support: define S_IFIFO.
 * 	[89/01/13            jsb]
 *
 * 06-Jan-88  Jay Kistler (jjk) at Carnegie Mellon University
 *	Made file reentrant.  Added declarations for __STDC__.
 *
 * 11-Aug-87  Peter King (king) at NeXT
 *	SUN_VFS: Added S_IFIFO for nfs routines (nfs_subr.c)
 *
 * 11-Dec-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added a variation of the stat structure that explicitly puts
 *	in padding where the Vax and RT compilers implicitly put it.
 *	This is for the Sun which does not align long fields on a long
 *	boundary.
 *
 * 25-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)stat.h	7.1 (Berkeley) 6/4/86
 */

#ifndef	_SYS_STAT_H_
#define _SYS_STAT_H_

#ifndef KERNEL
	#include <standards.h>
#endif

#import <sys/types.h>

#if defined(_POSIX_SOURCE) || defined(_NEXT_SOURCE)
	struct	stat
	{
		dev_t	st_dev;		/* File device number */
		ino_t	st_ino;		/* File serial number */
	#if defined(_POSIX_SOURCE)	
		mode_t	st_mode;	/* File type and access */
					/* permissions */
		nlink_t	st_nlink;	/* File link count */
	#else
		unsigned short st_mode;	
		short st_nlink;	
	#endif  /* _POSIX_SOURCE */
		uid_t	st_uid;		/* File owner's user ID */
		gid_t	st_gid;		/* File owner's group ID */
		dev_t	st_rdev;
		off_t	st_size;	/* File size in bytes */
					/* (for regular file only) */
		time_t	st_atime;	/* Time of last file access */
		int	st_spare1;
		time_t	st_mtime;	/* Time of last file */
					/* modification */
		int	st_spare2;
		time_t	st_ctime;	/* Time of last file status */
					/* change */
		int	st_spare3;
		long	st_blksize;
		long	st_blocks;
		long	st_spare4[2];
		};
#endif /* _POSIX_SOURCE || _NEXT_SOURCE */

#ifdef	sun
/*
 *	Explicitly padded stat structure
 */
struct	padded_stat
{
	dev_t	st_dev;
	short	st_shortpad1;	/* pad so next field starts on long bound. */
	ino_t	st_ino;
	unsigned short st_mode;
	short	st_nlink;
	uid_t	st_uid;
	gid_t	st_gid;
	dev_t	st_rdev;
	short	st_shortpad2;	/* pad so next field starts on long bound. */
	off_t	st_size;
	time_t	st_atime;
	int	st_spare1;
	time_t	st_mtime;
	int	st_spare2;
	time_t	st_ctime;
	int	st_spare3;
	long	st_blksize;
	long	st_blocks;
	long	st_spare4[2];
};
#endif	sun

#if defined(_POSIX_SOURCE) || defined(_NEXT_SOURCE)
	#define	_S_IFMT		0170000		/* type of file */
	#define	   _S_IFDIR	0040000		/* directory */
	#define	   _S_IFCHR	0020000		/* character special */
	#define	   _S_IFBLK	0060000		/* block special */
	#define	   _S_IFREG	0100000		/* regular */
	#define	   _S_IFLNK	0120000		/* symbolic link */
	#define	   _S_IFSOCK	0140000		/* socket */
	#define	   _S_IFIFO	0010000		/* fifo (SUN_VFS) */
	#define	_S_IRUSR	0000400		/* read permission, */
						/* owner */
	#define	_S_IWUSR	0000200		/* write permission, */
						/* owner */
	#define	_S_IXUSR	0000100		/* execute/search */
						/* permission, owner */

	#define	S_ISGID		0002000		/* set group id on */
						/* execution */
	#define	S_ISUID		0004000		/* set user id on */
						/* execution */
#endif /* _POSIX_SOURCE || _NEXT_SOURCE */

#ifdef _POSIX_SOURCE
	#define S_IRUSR	_S_IRUSR	/* read permission, owner */
	#define S_IRGRP	0000040		/* read permission, group */
	#define S_IROTH	0000004		/* read permission, other */
	#define S_IWUSR	_S_IWUSR	/* write permission, owner */
	#define S_IWGRP	0000020		/* write permission, group */
	#define S_IWOTH	0000002		/* write permission, other */
	#define S_IXUSR	_S_IXUSR	/* execute/search permission, */
					/* owner */
	#define S_IXGRP	0000010		/* execute/search permission, */
					/* group */
	#define S_IXOTH	0000001		/* execute/search permission, */
					/* other */
	#define S_IRWXU	0000700		/* read, write, execute */
					/* permissions, owner */
	#define S_IRWXG	0000070		/* read, write, execute */
					/* permissions, group */
	#define S_IRWXO	0000007		/* read, write, execute */
					/* permissions, other */

	#define S_ISBLK(mode)	(((mode) & (_S_IFMT)) == (_S_IFBLK))
	#define S_ISCHR(mode)	(((mode) & (_S_IFMT)) == (_S_IFCHR))
	#define S_ISDIR(mode)	(((mode) & (_S_IFMT)) == (_S_IFDIR))
	#define S_ISFIFO(mode)	(((mode) & (_S_IFMT)) == (_S_IFIFO))
	#define S_ISREG(mode)	(((mode) & (_S_IFMT)) == (_S_IFREG))
#endif /* _POSIX_SOURCE */


#ifdef _NEXT_SOURCE
	#define	S_IFMT		_S_IFMT		/* type of file */
	#define	    S_IFDIR	_S_IFDIR	/* directory */
	#define	    S_IFCHR	_S_IFCHR	/* character special */
	#define	    S_IFBLK	_S_IFBLK	/* block special */
	#define	    S_IFREG	_S_IFREG	/* regular */
	#define	    S_IFLNK	_S_IFLNK	/* symbolic link */
	#define	    S_IFSOCK	_S_IFSOCK	/* socket */
	#define	    S_IFIFO	_S_IFIFO	/* fifo (SUN_VFS) */
	#define	S_ISVTX		0001000		/* save swapped text */
						/* even after use */
	#define	S_IREAD		_S_IRUSR	/* read permission, */
						/* owner */
	#define	S_IWRITE 	_S_IWUSR	/* write permission, */
						/* owner */
	#define	S_IEXEC		_S_IXUSR	/* execute/search */
						/* permission, owner */

	#define	STAT_BSIZE	512	/* Size of blocks reported in */
					/* st_blocks */
	#define	STAT_BSHIFT	9	/* log2(STAT_BSIZE) */

	#define	btosb(bytes)	((unsigned)(bytes) >> STAT_BSHIFT)
				/* calculates (bytes / STAT_BSIZE) */
	#define sbtob(db)	((unsigned)(db) << STAT_BSHIFT)
				/* calculates (db * STAT_BSIZE) */
#endif /* _NEXT_SOURCE */

#ifndef KERNEL
	#ifdef _NEXT_SOURCE
		#ifdef __STDC__
			extern int lstat(const char *, struct stat *);
		#else
			extern int lstat();
		#endif /* __STDC__ */
	#endif /* _NEXT_SOURCE */

	#ifdef _POSIX_SOURCE
		#ifdef __STDC__
			extern int chmod(const char *path, mode_t mode);
			extern int mkdir(const char *path, mode_t mode);
			extern int mkfifo(const char *path, mode_t mode);
			extern mode_t umask(mode_t cmask);
		#else
			extern int chmod();
			extern int mkdir();
			extern int mkfifo();
			extern mode_t umask();
		#endif /* __STDC__ */
	#endif /* _POSIX_SOURCE */

	#if defined(_POSIX_SOURCE) || defined(_NEXT_SOURCE)
		#ifdef __STDC__
			extern int fstat(int fildes, struct stat *buf);
			extern int stat(const char *path,
				struct stat *buf);
		#else
			extern int fstat();
			extern int stat();
		#endif /* __STDC__ */
	#endif /* _POSIX_SOURCE || _NEXT_SOURCE */
#endif /* !KERNEL */
#endif	_SYS_STAT_H_


