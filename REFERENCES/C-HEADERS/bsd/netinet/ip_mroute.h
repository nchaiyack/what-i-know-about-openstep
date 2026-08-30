/*
 * Definitions for the kernel part of DVMRP,
 * a Distance-Vector Multicast Routing Protocol.
 * (See RFC-1075.)
 *
 * Written by David Waitzman, BBN Labs, August 1988.
 * Modified by Steve Deering, Stanford, February 1989.
 *
 * MROUTING 1.0
 */


/*
 * DVMRP-specific setsockopt commands.
 */
#define DVMRP_INIT		100
#define DVMRP_DONE		101
#define DVMRP_ADD_VIF	102
#define DVMRP_DEL_VIF	103
#define DVMRP_ADD_LGRP	104
#define DVMRP_DEL_LGRP	105
#define DVMRP_ADD_MRT	106
#define DVMRP_DEL_MRT	107


/*
 * Types and macros for handling bitmaps with one bit per virtual interface.
 */
#define MAXVIFS 32
typedef u_long vifbitmap_t;
typedef u_short vifi_t;		/* type of a vif index */

#define	VIFM_SET(n, m)		((m) |=  (1 << (n)))
#define	VIFM_CLR(n, m)		((m) &= ~(1 << (n)))
#define	VIFM_ISSET(n, m)	((m) &   (1 << (n)))
#define VIFM_CLRALL(m)		((m) = 0x00000000)
#define VIFM_COPY(mfrom, mto)	((mto) = (mfrom))
#define VIFM_SAME(m1, m2)	((m1) == (m2))


/*
 * Agument structure for DVMRP_ADD_VIF.
 * (DVMRP_DEL_VIF takes a single vifi_t argument.)
 */
struct vifctl {
    vifi_t	    vifc_vifi;			/* the index of the vif to be added   */
    u_char	    vifc_flags;			/* VIFF_ flags defined below          */
    u_char	    vifc_threshold;		/* min ttl required to forward on vif */
    struct in_addr  vifc_lcl_addr;  /* local interface address            */
    struct in_addr  vifc_rmt_addr;  /* remote address (tunnels only)      */
};

#define VIFF_TUNNEL	  0x1			/* vif represents a tunnel end-point */


/*
 * Argument structure for DVMRP_ADD_LGRP and DVMRP_DEL_LGRP.
 */
struct lgrplctl {
    vifi_t         lgc_vifi;
    struct in_addr lgc_gaddr;
};


/*
 * Argument structure for DVMRP_ADD_MRT.
 * (DVMRP_DEL_MRT takes a single struct in_addr argument, containing origin.)
 */
struct mrtctl {
    struct in_addr  mrtc_origin;		/* subnet origin of multicasts      */
    struct in_addr  mrtc_originmask;	/* subnet mask for origin           */
    vifi_t	    mrtc_parent;			/* incoming vif                     */
    vifbitmap_t	    mrtc_children;		/* outgoing children vifs           */
    vifbitmap_t	    mrtc_leaves;		/* subset of outgoing children vifs */
};




