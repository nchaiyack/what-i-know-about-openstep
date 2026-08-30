/* 
 * HISTORY
 *  3-Jan-90 Gregg Kellogg (gk) at NeXT, Inc.
 *	Modified parameters to use void * instead of caddr_t.
 *
 * 26-Oct-87 Peter King (king) at NeXT, Inc.
 *	Created.
 */ 

#ifndef	_KERN_INTERNAL_KALLOC_H_
#define _KERN_INTERNAL_KALLOC_H_

#import <machine/machparam.h>

#define MINSIZE 32

#ifdef	KERNEL
extern void kallocinit(void);
extern void *kalloc(int size);
extern void *kget(int size);
extern void kfree(void *data, long size);
extern void *kalloc_contiguous(int size);


extern void *malloc(unsigned int size);
extern void *calloc(unsigned int num, unsigned int size);
extern void *realloc(void *addr, unsigned int size);
extern void free(void *data);
extern void malloc_good_size(unsigned int size);
#endif	KERNEL
#endif	_KERN_INTERNAL_KALLOC_H_
