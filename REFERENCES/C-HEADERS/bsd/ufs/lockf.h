/*
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Scooter Morris at Genentech Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)lockf.h	7.1 (Berkeley) 2/1/91
 */

#ifndef	_LOCKF_H
#define _LOCKF_H

#if POSIX_KERN

#include <sys/types.h>
#include <sys/vnode.h>

/*
 * The lf_svnode structure is a kernel structure which shadows the real
 * vnode structure.  There is one lf_svnode structure for each vnode that
 * has locks.  Each structure points to a list lockf structures.  These
 * shadow vnode structures are kept in a hash list for efficiency.
 *
 * Note: This structure is added so as not to add fields
 *       to the inode or vnode structure.  
 */
struct lf_svnode {
	struct vnode		*lf_vnodep;	/* Pointer to vnode and id. */
	struct lockf		*lf_lockfp;	/* List of lockf structures. */
	int			lf_refcnt;	/* Reference counter. */
	struct lf_svnode	*lf_next;	/* Pointer to next struct */
};

/*
 * Hash list for shadow vnode (lf_svnode) structures.
 */
#define LF_SVNODE_HSZ	64
#define LF_SVNODE_HASH(num)	((num) & (LF_SVNODE_HSZ - 1))
extern struct lf_svnode	*lf_svnode_hash[];

/*
 * The lockf structure is a kernel structure which contains all the
 * information associated with a byte range lock. The lockf structures
 * are linked into a shadow vnode structure. Locks are sorted by the
 * starting byte of the lock for efficiency.
 */
struct lockf {
	short			lf_flags;	 /* Lock semantics: LF_WAIT,
						  * LF_NOWAIT
						  */
	short			lf_type;	 /* Lock type: F_RDLCK,
						  * F_WRLCK, F_UNLCK
						  */
	off_t			lf_start;	 /* The byte # of the start of
						  * the lock
						  */
	off_t			lf_end;		 /* The byte # of the end of
						  * the lock (-1=EOF)
						  */
	struct posix_proc	*lf_posix_procp; /* The id of the resource
						  * holding the lock
						  */
	struct lf_svnode	*lf_svnodep;	 /* Back pointer to the shadow
						  * vnode structure
						  */
	struct lockf		*lf_next;	 /* A pointer to the next lock
						  * on this vnode
						  */
	struct lockf		*lf_block;	 /* The list of blocked locks */
};

/*
 * Maximum length of sleep chains to traverse to try and detect deadlock.
 */
#define LF_MAXDEPTH 50

/*
 * Flags to indicate blocking or nonblocking locking.
 */
#define LF_NOWAIT	01
#define LF_WAIT		02

/*
 * Public lock manipulation routine
 */
extern int lf_lockctl();

#ifdef	LOCKF_DEBUG
extern int lockf_debug;
#endif	/* LOCKF_DEBUG */

#endif	/* POSIX_KERN */

#endif	/* _LOCKF_H */
