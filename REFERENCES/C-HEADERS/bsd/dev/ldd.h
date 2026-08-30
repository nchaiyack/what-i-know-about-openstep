/*	@(#)ldd.h	2.0	03/20/90	(c) 1990 NeXT	
 *
 * ldd.h - kernel prototypes used by loadable device drivers
 *
 * HISTORY
 * 22-May-91	Gregg Kellogg (gk) at NeXT
 *	Split out public interface.
 *
 * 16-Aug-90  Gregg Kellogg (gk) at NeXT
 *	Removed a lot of stuff that's defined in other header files. 
 *	Eventually this file should either go away or contain only imports of
 *	other files.
 *
 * 20-Mar-90	Doug Mitchell at NeXT
 *	Created.
 *
 */

#ifndef	_M68K_DEV_LDD_PRIV_
#define _M68K_DEV_LDD_PRIV_

#import <kernserv/prototypes.h>
#ifdef	m68k
#import <bsd/dev/m68k/dma.h>
#endif	m68k
#import <bsd/dev/disk.h>

typedef int (*PFI)();

extern int physio(int (*strat)(), struct buf *bp, dev_t dev, int rw, 
	unsigned (*mincnt)(), struct uio *uio, int blocksize);

extern u_short checksum_16 (u_short *wp, int shorts);
extern int sdchecklabel(struct disk_label *dlp, int blkno);

extern int sleep(void *chan, int pri);
extern void wakeup(void *chan);
extern void psignal(struct proc *p, int sig);

extern boolean_t untimeout(int (*fun)(), void *arg);
extern void timeout(int (*fun)(), void *arg, int time);


#endif	_M68K_DEV_LDD_PRIV_

