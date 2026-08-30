/*
 * Copyright (c) 1992 NeXT Computer, Inc.
 *
 * Network interface class.
 *
 * HISTORY
 *
 * 10 December 1992 David E. Bohman at NeXT
 *	Created.
 */

#ifdef	KERNEL

#import <objc/Object.h>
#import <bsd/net/netif.h>

@interface IONetwork:Object
{
@private
    netif_t	_netif;
    int		_IONetwork_reserved[4];
}

- initForNetworkDevice:device
		name:(const char *)name
		unit:(unsigned int)unit
		type:(const char *)type
		maxTransferUnit:(unsigned int)mtu
		flags:(unsigned int)flags;

- (int)handleInputPacket:(netbuf_t)pkt
		extra:(void *)extra;

- (unsigned)inputPackets;
- (void)incrementInputPackets;
- (void)incrementInputPacketsBy:(unsigned)increment;

- (unsigned)inputErrors;
- (void)incrementInputErrors;
- (void)incrementInputErrorsBy:(unsigned)increment;

- (unsigned)outputPackets;
- (void)incrementOutputPackets;
- (void)incrementOutputPacketsBy:(unsigned)increment;

- (unsigned)outputErrors;
- (void)incrementOutputErrors;
- (void)incrementOutputErrorsBy:(unsigned)increment;

- (unsigned)collisions;
- (void)incrementCollisions;
- (void)incrementCollisionsBy:(unsigned)increment;

@end

@protocol IONetworkDeviceMethods

- (int)finishInitialization;

- (int)outputPacket:(netbuf_t)pkt
	    address:(void *)addrs;

- (netbuf_t)allocateNetbuf;

- (int)performCommand:(const char *)command
	    data:(void *)data;

@end

#endif	KERNEL
