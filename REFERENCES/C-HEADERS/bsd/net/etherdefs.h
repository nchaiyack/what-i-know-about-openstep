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
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
 *
 * HISTORY
 * 11-Jul-93  Mac Gillon (mgillon) at NeXT
 *	Integrated MULTICAST support
 *
 * 09-Apr-90  Bradley Taylor (btaylor) at NeXT, Inc.
 *	Created. Originally part of <netinet/if_ether.h>.
 */
#ifndef _ETHERDEFS_
#define _ETHERDEFS_

/*
 * Ethernet address - 6 octets
 */
#define NUM_EN_ADDR_BYTES	6

struct ether_addr {
	u_char	ether_addr_octet[NUM_EN_ADDR_BYTES];
};

#define ea_byte	ether_addr_octet

typedef struct ether_addr enet_addr_t;

/*
 * Structure of a 10Mb/s Ethernet header.
 */
struct	ether_header {
	u_char	ether_dhost[6];
	u_char	ether_shost[6];
	u_short	ether_type;
};

typedef struct ether_header ether_header_t;

#define IFTYPE_ETHERNET "10MB Ethernet"

#define	ETHERTYPE_PUP	0x0200		/* PUP protocol */
#define	ETHERTYPE_IP	0x0800		/* IP protocol */
#define ETHERTYPE_ARP	0x0806		/* Addr. resolution protocol */
#define ETHERTYPE_REVARP 0x8035		/* Reverse ARP (SUN_RPC) */

/*
 * The ETHERTYPE_NTRAILER packet types starting at ETHERTYPE_TRAIL have
 * (type-ETHERTYPE_TRAIL)*512 bytes of data followed
 * by an ETHER type (as given above) and then the (variable-length) header.
 */
#define	ETHERTYPE_TRAIL		0x1000		/* Trailer packet */
#define	ETHERTYPE_NTRAILER	16


#define ETHERHDRSIZE	14
#define	ETHERMTU	1500
#define ETHERMAXPACKET	(ETHERHDRSIZE + ETHERMTU)
#define ETHERMINPACKET	64
#define ETHERCRC	4
#define	ETHERMIN	(ETHERMINPACKET-ETHERCRC-ETHERHDRSIZE)

/*
 * Byte and bit in an enet_addr_t defining individual/group destination.
 */
#define EA_GROUP_BYTE	0
#define EA_GROUP_BIT	0x01

#ifdef KERNEL
/*
 * Macro to map an IP multicast address to an Ethernet multicast address.
 * The high-order 25 bits of the Ethernet address are statically assigned,
 * and the low-order 23 bits are taken from the low end of the IP address.
 */
#define ETHER_MAP_IP_MULTICAST(ipaddr, enaddr)				\
	/* struct in_addr *ipaddr; */					\
	/* u_char enaddr[6];       */					\
{									\
	(enaddr)[0] = 0x01;						\
	(enaddr)[1] = 0x00;						\
	(enaddr)[2] = 0x5e;						\
	(enaddr)[3] = ((u_char *)ipaddr)[1] & 0x7f;			\
	(enaddr)[4] = ((u_char *)ipaddr)[2];				\
	(enaddr)[5] = ((u_char *)ipaddr)[3];				\
}
#endif KERNEL

#endif /* _ETHERDEFS_ */
