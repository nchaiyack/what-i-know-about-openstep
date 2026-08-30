/* 
 * Copyright (c) 1987 NeXT, Inc.
 *
 * HISTORY
 * 15-May-91  Gregg Kellogg (gk) at NeXT
 *	Converted NeXT_ stuff to m68k_ stuff.
 */ 

#ifndef	_MACH_M68K_VM_PARAM_
#define	_MACH_M68K_VM_PARAM_

#import <bsd/sys/types.h>

#define BYTE_SIZE	8	/* byte size in bits */
#define BYTE_MSF	1	/* Most significant byte first in word */

/*
 *	These are variables so we can change the page size by just rebooting.
 */

#ifndef	__ASSEMBLER__
extern int
	m68k_page_size,		/* bytes per m68k page */
	m68k_page_mask,		/* mask for page offset */
	m68k_page_shift,	/* number of bits to shift for pages */
	m68k_is,		/* initial shift: # of high VA bits to skip */
	m68k_tia,		/* table index a */
	m68k_tib,		/* table index b */
	m68k_pt1_entries,	/* number of entries per level 1 page table */
	m68k_pt2_entries,
	m68k_pt1_size,		/* size of a single level 1 page table */
	m68k_pt2_size,
	m68k_pt1_shift,		/* bits to shift for pt1 index */
	m68k_pt2_shift,
	m68k_pt1_mask,		/* mask to apply for pt1 index */
	m68k_pt2_mask,
	m68k_pt2_maps;		/* a single pt2 maps this much VA space */
#endif	__ASSEMBLER__

/*
 *	Most ports place the kernel in the high half of the total
 *	32-bit virtual address (VA) space, the u-area and kernel stack
 *	just below that and the user space starting at virtual
 *	location zero.  We disagree with this for several reasons
 *	(on the VAX the hardware gives you no choice).  The user
 *	should be able to address the entire 4GB virtual space now
 *	that Mach makes better use of virtual memory concepts
 *	(mapped files, shared memory, copy-on-write etc.) -- we need
 *	the extra 2GB for these things.
 *
 *	Some processes may also want to use the MMU transparent
 *	translation (tt) registers to access devices (e.g. video memory)
 *	without constantly invalidating the MMU address translation cache.
 *	Because the MMU tt registers map chunks of VA space directly to
 *	their corresponding physical address (PA) spaces this fragments
 *	the space even more and we'll need more VA space to compensate for it.
 *	Another goal is catching illegal zero pointer references
 *	in both the kernel and user address spaces.
 *	We'd also like to use the MMU tt registers to bypass address
 *	translation for the kernel text, data, bss and system page table
 *	areas.
 */

#define	M68K_MIN_PAGE_SIZE	8192
#define	M68K_MAX_PAGE_SIZE	32768

#define	VM_MIN_ADDRESS	((vm_offset_t) 0)
#define	VM_MAX_ADDRESS	((vm_offset_t) 0xfffffffc)

/* allow 64 MB of kernel virtual space */
#define VM_MIN_KERNEL_ADDRESS	((vm_offset_t) 0x10000000)
#define VM_MAX_KERNEL_ADDRESS	((vm_offset_t) 0x14000000)

#define	M68K_KERNEL_TEXT_ADDR	0x04000000

#define INTSTACK_SIZE		4096		/* interrupt stack size */
#define	KERNSTACK_SIZE		4096		/* kernel stack size
						 * Don't use this, use
						 * KERNEL_STACK_SIZE from
						 * <kern/kernel_stack.h>
						 */
#define	MAX_REGIONS		8		/* max regions of memory */

/*
 *	Convert bytes to pages and convert pages to bytes.
 *	No rounding is used.
 */

#define	m68k_btop(x)	(((unsigned)(x)) >> m68k_page_shift)
#define	m68k_ptob(x)	(((unsigned)(x)) << m68k_page_shift)

/*
 *	Round off or truncate to the nearest page.  These will work
 *	for either addresses or counts.  (i.e. 1 byte rounds to 1 page
 *	bytes.
 */

#define m68k_round_page(x)	((((unsigned)(x)) + m68k_page_size - 1) & \
					~(m68k_page_size-1))
#define m68k_trunc_page(x)	(((unsigned)(x)) & ~(m68k_page_size-1))

/*
 *	Conversion between m68k pages and VM pages.
 */

#define trunc_m68k_to_vm(p)	(atop(trunc_page(m68k_ptob(p))))
#define round_m68k_to_vm(p)	(atop(round_page(m68k_ptob(p))))

/*
 * Maximum alignment required by any data type for this architecture.
 * (Use 4 bytes for performance reasons....)
 */
#define	MAX_DATA_ALIGNMENT	4		/* 4 bytes */
#endif	_MACH_M68K_VM_PARAM_
