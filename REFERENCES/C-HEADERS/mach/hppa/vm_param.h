/* 
 * Copyright (c) 1993 NeXT, Inc.
 */ 


#ifndef	_MACH_HPPA_VM_PARAM_H_
#define _MACH_HPPA_VM_PARAM_H_

#import <sys/types.h>

#define BYTE_SIZE	8	/* byte size in bits */

#define HPPA_PGBYTES	4096	/* bytes per hppa page */
#define HPPA_PGSHIFT	12	/* number of bits to shift for pages */
#define HPPA_PGALIGN	12      /* power of two for page alignment */

#define VM_MIN_ADDRESS	((vm_offset_t) 0)
#define VM_MAX_ADDRESS	((vm_offset_t) 0xfffff000)

#define hppa_round_page(x)	((((unsigned)(x)) + HPPA_PGBYTES - 1) & \
					~(HPPA_PGBYTES-1))
#define hppa_trunc_page(x)	(((unsigned)(x)) & ~(HPPA_PGBYTES-1))

#define VM_MIN_KERNEL_ADDRESS	((vm_offset_t) 0x00000000)
#define VM_MAX_KERNEL_ADDRESS	((vm_offset_t) 0x40000000)

/*
 * WARNING : If you make the stack bigger, you need to check the
 *	trap code to make sure things still work...
 */
 
#define KERNSTACK_SIZE		(4 * HPPA_PGBYTES)
#define INTSTACK_SIZE		(10 * HPPA_PGBYTES)

#define STACK_GROWTH_UP	1

#ifdef	__ASSEMBLER__
#define HPPA_STACK_START			0x68FF3000  /* HP-UX Magic */
#else	__ASSEMBLER__
#define HPPA_STACK_START	((vm_offset_t) 0x68FF3000)  /* HP-UX Magic */
#endif	__ASSEMBLER__
#define HPPA_STACK_SIZE	((vm_size_t)(128*1024))

/*
 * Maximum alignment required by any data type for this architecture.
 */
#define MAX_DATA_ALIGNMENT      16  /* 16 byte alignment for LDCWS, LDCWX */

#endif	_HPPA_VM_PARAM_H_
