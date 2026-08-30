/*
 * Definitions for parameters to vm_deactivate and vm_set_policy.
 *
 * Copyright (c) 1993 NeXT, Inc.
 *
 * HISTORY
 *
 *  23Jan93	Brian Pinkerton at NeXT
 *	Created.
 */

#ifndef	_VM_POLICY_H
#define	_VM_POLICY_H

/*
 *  Flags for vm_deactivate
 */
#define VM_DEACTIVATE_NOW		0x0	/* most aggressive: free mem */
#define	VM_DEACTIVATE_SOON		0x1	/* less aggressive */
#define VM_DEACTIVATE_SHARED		0x2	/* deactivate shared mem too */

/*
 *  Flags for vm_set_policy
 */
#define VM_POLICY_RANDOM		0x0	/* access pattern is random */
#define VM_POLICY_SEQ_FREE		0x1	/* free pages on sequential */
#define VM_POLICY_SEQ_DEACTIVATE	0x2	/* deactivate pages on seq */
#define VM_POLICY_PAGE_AHEAD		0x4	/* page ahead */

#define	VM_POLICY_SEQUENTIAL (VM_POLICY_SEQ_FREE | VM_POLICY_SEQ_DEACTIVATE)

#endif	_VM_POLICY_H

