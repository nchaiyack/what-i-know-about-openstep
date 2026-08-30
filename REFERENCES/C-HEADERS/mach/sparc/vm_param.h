/*
 * Copyright (c) 1994 NeXT Computer, Inc.
 *
 * sun sparc Family:	Virtual memory constants.
 *
 * HISTORY
 *
 * 11 April 1994 Mahesh M. Kumar created at NeXT
 *		based on the i386 version by David E. Bohman
 *
 */

#ifndef	_MACH_SPARC_VM_PARAM_H_
#define _MACH_SPARC_VM_PARAM_H_


#define BYTE_SIZE	8	/* byte size in bits */
#define BYTE_MSF	0

#define SPARC_PGBYTES	4096	/* bytes per sun4m page */
#define SPARC_PGSHIFT	12	/* number of bits to shift for pages */
#define SPARC_PGALIGN	12	/* number of bits to shift for pages */

/*
 *	Convert bytes to pages and convert pages to bytes.
 *	No rounding is used.
 */

#define sparc_btop(x)		(((unsigned)(x)) >> SPARC_PGSHIFT)
#define sparc_ptob(x)		(((unsigned)(x)) << SPARC_PGSHIFT)

/*
 *	Round off or truncate to the nearest page.  These will work
 *	for either addresses or counts.  (i.e. 1 byte rounds to 1 page
 *	bytes.
 */

#define sparc_round_page(x)	((((unsigned)(x)) + SPARC_PGBYTES - 1) & \
					~(SPARC_PGBYTES-1))
#define sparc_trunc_page(x)	(((unsigned)(x)) & ~(SPARC_PGBYTES-1))

#define VM_MIN_ADDRESS		((vm_offset_t) 0)
#define VM_MAX_ADDRESS		((vm_offset_t) 0xF0000000)


#define KERNELBASE  		0xF0000000
#define KERNELSIZE		(16*1024*1024) /* 16 MB */
#define VM_KERNEL_LOAD_ADDRESS  ((vm_offset_t)KERNELBASE)

#define VM_MIN_KERNEL_ADDRESS	((vm_offset_t) 0xF0000000)
#define VM_MAX_KERNEL_ADDRESS	((vm_offset_t) 0xFF000000)
				/* except the last 16 MB for DVMA */

#define KERNSTACK_SIZE		(4*SPARC_PGBYTES)
#define INTSTACK_SIZE		(8*SPARC_PGBYTES)

/*
 *	Conversion between sun4m pages and VM pages
 */

#define trunc_sun_to_vm(p)	(atop(trunc_page(sun_ptob(p))))
#define round_sun_to_vm(p)	(atop(round_page(sun_ptob(p))))
#define vm_to_sun(p)		(sun_btop(ptoa(p)))

/*
 * Maximum alignment required by any data type for this architecture.
 * (Use cache line size bytes for performance reasons....)
 */
#define	MAX_DATA_ALIGNMENT	16		/* 16 bytes */

#endif	_MACH_SPARC_VM_PARAM_H_
