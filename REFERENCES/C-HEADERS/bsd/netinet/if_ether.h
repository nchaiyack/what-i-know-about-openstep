/* 
 * Mach Operating System
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *	@(#)if_ether.h	7.3 (Berkeley) 6/29/88 plus MULTICAST 1.0
 *
 * HISTORY
 * 11-Jul-93  Mac Gillon (mgillon) at NeXT
 *	Integrated MULTICAST support
 *
 * 09-Apr-90  Bradley Taylor (btaylor) at NeXT, Inc.
 *	Move Ethernet definitions to <net/etherdefs.h>. Leave arp stuff here.
 *
 * 20-Oct-87  Peter King (king) at NeXT, Inc.
 *	SUN_RPC: Add definition for ether_addr.  Add RARP support.
 *
 * 25-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 * 15-Aug-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_INET:  added ac_if field to arptab definition to allow
 *	multiple interfaces to co-exist.
 *	[V1(1)]
 */
 
/*	@(#)if_ether.h	2.1 88/05/18 4.0NFSSRC SMI;	from UCB 7.1 6/5/86	*/

#import <net/etherdefs.h>


/*
 * Ethernet Address Resolution Protocol.
 *
 * See RFC 826 for protocol description.  Structure below is adapted
 * to resolving internet addresses.  Field names used correspond to 
 * RFC 826.
 */
struct	ether_arp {
	struct	arphdr ea_hdr;	/* fixed-size header */
	u_char	arp_sha[6];	/* sender hardware address */
	u_char	arp_spa[4];	/* sender protocol address */
	u_char	arp_tha[6];	/* target hardware address */
	u_char	arp_tpa[4];	/* target protocol address */
};
#define	arp_hrd	ea_hdr.ar_hrd
#define	arp_pro	ea_hdr.ar_pro
#define	arp_hln	ea_hdr.ar_hln
#define	arp_pln	ea_hdr.ar_pln
#define	arp_op	ea_hdr.ar_op


/*
 * Structure shared between the ethernet driver modules and
 * the address resolution code.  For example, each ec_softc or il_softc
 * begins with this structure.
 */
struct arpcom {
	struct ifnet ac_if;					/* network-visible interface */
	u_char ac_enaddr[6];				/* ethernet hardware address */
	struct in_addr ac_ipaddr;			/* copy of ip address- XXX */
	struct ether_multi *ac_multiaddrs;	/* list of ether multicast addrs */
};

/*
 * Internet to ethernet address resolution table.
 */
struct arptab {
	struct in_addr at_iaddr;			/* internet address */
	u_char at_enaddr[6];				/* ethernet address */
	u_char at_timer;					/* minutes since last reference */
	u_char at_flags;					/* flags */
	struct mbuf *at_hold;				/* one element packet buffering */
	struct ifnet *at_if;				/* interface (CS_INET) */
};

#ifdef	KERNEL
u_char etherbroadcastaddr[6];
struct	arptab *arptnew();
char *ether_sprintf();
#endif

/*
 * Ethernet multicast address structure.  There is one of these for each
 * multicast address or range of multicast addresses that we are supposed
 * to listen to on a particular interface.  They are kept in a linked list,
 * rooted in the interface's arpcom structure.  (This really has nothing to
 * do with ARP, or with the Internet address family, but this appears to be
 * the minimally-disrupting place to put it.)
 */
struct ether_multi {
	u_char enm_addrlo[6];			/* low  or only address of range */
	u_char enm_addrhi[6];			/* high or only address of range */
	struct arpcom *enm_ac;			/* back pointer to arpcom        */
	u_int enm_refcount;				/* no. claims to this addr/range */
	struct ether_multi *enm_next;	/* ptr to next ether_multi       */
};

#ifdef KERNEL
/*
 * Structure used by macros below to remember position when stepping through
 * all of the ether_multi records.
 */
struct ether_multistep {
	struct ether_multi  *e_enm;
};

/*
 * Macro for looking up the ether_multi record for a given range of Ethernet
 * multicast addresses connected to a given arpcom structure.  If no matching
 * record is found, "enm" returns NULL.
 */
#define ETHER_LOOKUP_MULTI(addrlo, addrhi, ac, enm)			\
	/* u_char              addrlo[6]; */				\
	/* u_char              addrhi[6]; */				\
	/* struct arpcom      *ac;        */				\
	/* struct ether_multi *enm;       */				\
{									\
	for ((enm) = (ac)->ac_multiaddrs;				\
	     (enm) != NULL &&						\
		(bcmp((enm)->enm_addrlo, (addrlo), 6) != 0 ||		\
		 bcmp((enm)->enm_addrhi, (addrhi), 6) != 0);		\
	     (enm) = (enm)->enm_next);					\
}

/*
 * Macro to step through all of the ether_multi records, one at a time.
 * The current position is remembered in "step", which the caller must
 * provide.  ETHER_FIRST_MULTI(), below, must be called to initialize "step"
 * and get the first record.  Both macros return a NULL "enm" when there
 * are no remaining records.
 */
#define ETHER_NEXT_MULTI(step, enm)					\
	/* struct ether_multistep  step; */				\
	/* struct ether_multi     *enm;  */				\
{									\
	if (((enm) = (step).e_enm) != NULL)				\
		(step).e_enm = (enm)->enm_next;				\
}

#define ETHER_FIRST_MULTI(step, ac, enm)				\
	/* struct ether_multistep  step; */				\
	/* struct arpcom          *ac;   */				\
	/* struct ether_multi     *enm;  */				\
{									\
	(step).e_enm = (ac)->ac_multiaddrs;				\
	ETHER_NEXT_MULTI((step), (enm));				\
}
#endif KERNEL

