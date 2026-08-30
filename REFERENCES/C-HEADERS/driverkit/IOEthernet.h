/*
 * Copyright (c) 1992 NeXT Computer, Inc.
 *
 * Device independent abstract superclass for Ethernet.
 *
 * HISTORY
 *
 * 25 September 1992 David E. Bohman at NeXT
 *	Created.
 */

#ifdef	KERNEL

#import <driverkit/IODirectDevice.h>
#import <driverkit/IONetwork.h>
#import <kernserv/ns_timer.h>
#import <kernserv/queue.h>

#import <bsd/net/etherdefs.h>


@interface IOEthernet:IODirectDevice<IONetworkDeviceMethods>
{
@private
    BOOL		_isRunning;
    BOOL		_promiscEnabled;
    id			_driverCmd;
    ns_time_t		_absTimeout;
    id              	_multiLock;		// NXLock, protects multicastQ
    enet_addr_t  	_multiAddr;		// current multicast addr 
    queue_head_t	_multicastQueue; 	// queue of multicast addresses
    IONetwork		*_netif;
    enet_addr_t		_ethernetAddress;
    int			_IOEthernet_reserved[4];
}

- initFromDeviceDescription:(IODeviceDescription *)devDesc;
- free;

- (BOOL)isRunning;
- (void)setRunning:(BOOL)running;

- (unsigned int)relativeTimeout;

- (void)setRelativeTimeout:(unsigned int)timeout;

- (void)clearTimeout;

- (BOOL)isUnwantedMulticastPacket:(ether_header_t *)header; 

- (void)performLoopback:(netbuf_t)pkt;

@end

@interface IOEthernet(DriverInterface)

- (BOOL)resetAndEnable:(BOOL)enable;
- (IONetwork *)attachToNetworkWithAddress:(enet_addr_t)addrs;

- (void)transmit:(netbuf_t)pkt;

- (BOOL)enablePromiscuousMode;	 
- (void)disablePromiscuousMode;	 
- (BOOL)enableMulticastMode;	 
- (void)disableMulticastMode;	 

- (void)addMulticastAddress:(enet_addr_t *)addr;
- (void)removeMulticastAddress:(enet_addr_t *)addr;

@end

#endif
