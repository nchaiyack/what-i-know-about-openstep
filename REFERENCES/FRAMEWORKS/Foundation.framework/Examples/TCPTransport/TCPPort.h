/* TCPPort.h created by blaine on Wed 03-Apr-1996
   Copyright 1996, NeXT Computer, Inc.
   Blaine Garst
   Marc Majka
 */

/*
 * The Distributed Objects subsystem within Foundation allows one to
 * substitute a different transport in place of the standard mach IPC
 * (either direct or emulated).
 * The transport takes the form of an alternate concrete NSPort subclass
 * implementation.  This is an example of such a beast, hopefully to
 * serve not as a direct replacement but as a starting point for other
 * work.  Its chief drawbacks over the mach IPC nmserver are:
 *	- no security: intramachine objects are all net visible
 *	- no multiplexing: when you run out of sockets... poof!
 *	- no nameservice: there is no broadcast lookup
 * These all must be solved to be as good as the mach IPC transport.
 */


#import <Foundation/Foundation.h>
#import "DataStream.h"


/* TCPPort - a concrete port implementation based on TCP ports.
 * A TCP port is in the range of unsigned shorts.  A port that is
 * advertised for connect()ions does not receive any data directly.
 * Instead, a per-connect()ion port is built and used as the sendPort
 * of NSConnections.  Thus, the TCP port number is used as a rendezvous
 * point and not for any data transmission.
 * There is a race, however, if two parties both do connect()s at the
 * same time.  This results in having two TCP circuits for a single
 * connection between two peers.  Both parties will write on only one
 * of these circuits, however, so there is no ordering problem.  Both
 * parties must read() on the connect()ed socket until an accept()ed
 * socket shows up.
 */
 
/* PLEASE NOTE that DO is thread-safe and so should this class! */
 

@interface TCPPort : NSPort {
    id readWriter;	// the connect()ed one
    id reader;	// the accept()ed one
    id delegate;
    TCPPort *listener;
    NSConnection *connection;	// needs to be held until first message processed
    NSCountedSet *modes;
    unsigned long internetAddr;
    unsigned int refCount;
    unsigned short tcpPort;
    BOOL isDying;
    BOOL invalid;
	/* partial portMessage assembly */
    int partialState;
    DataStream *dataStream;
    unsigned int dataLength;
    NSMutableData *dataItem;
    NSMutableArray *items;
    unsigned int nItems;
    unsigned int itemCounter;
    unsigned int itemType;
}

- (TCPPort *)initWithNumber:(unsigned short)p;
  /* build a rendezvous port on a publishable number */

- (TCPPort *)connectToNumber:(unsigned short)p host:(NSString *)hostname;
- (TCPPort *)connectToNumber:(unsigned short)p address:(unsigned long)addr;
   /* given a port that you are listening on, connect to another.  This
      builds a TCP port connected to the other end suitable for DO
      communication.  There is a race here, so this code must resolve who
      should win if both ends connect to each other at the same time.
    */

+ (void)_toggleLogging;


@end
