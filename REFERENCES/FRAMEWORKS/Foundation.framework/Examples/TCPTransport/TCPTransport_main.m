/*
 * You may freely copy, distribute and reuse the code in this example.
 * NeXT Software, Inc. disclaims any warranty of any kind, expressed or implied,
 * as to its fitness for any particular use.  This disclaimer applies to all
 * source files in this example.
 */

// Test program for TCPPort
//
// On hosts moe, larry, and curly
//  larry:
//    TCPTransport
// 
//  curly:
//    TCPTransport larry
//
//  moe:
//    TCPTransport larry
//
//
// If 3 hosts aren't available, on one host try:
//   shell1>  TCPTransport
//
//   shell2>  TCPTransport -l 10001
//
//   shell3>  TCPTransport -l 10002
//
// Other options:
// -l <port-number>      listen on this port instead of the default (10000)
// -s <port-number>      send to this port instead of to the default (10000)
// -v                    verbose - print log message from TCPPort
// -V                    very verbose - print log messages from DO and TCPPort

#import <Foundation/Foundation.h>
#import "TCPPort.h"
#import "RemoteTest.h"

@interface NSConnection (NSConnectionLogging)
+ (void)_toggleLogging;
@end

@interface TCPPort (TCPPortLogging)
+ (void)_toggleLogging;
@end

#define DefaultTCPPortNumber 10000

void main() {
    NSAutoreleasePool *pool= [[NSAutoreleasePool alloc] init];	// first thing
    NSArray *args = [[NSProcessInfo processInfo] arguments];
    unsigned int i, len = [args count];
    RemoteTest *testObject;
    RemoteTest *otherObject;
    NSConnection *conn;
    TCPPort *listener, *sender;
    NSString *serverName;
    NSString *hostName;
    unsigned short listenPort, sendPort;
    BOOL original, verbosePorts, verboseEverything;


    original = YES;
    verbosePorts = NO;
    verboseEverything = NO;
    listenPort = DefaultTCPPortNumber;
    sendPort = DefaultTCPPortNumber;
    hostName = nil;
    serverName = nil;

    for (i = 1; i < len; i++) {
        if ([[args objectAtIndex:i] isEqual:@"-l"])
            listenPort = [[args objectAtIndex:++i] intValue];
        else if ([[args objectAtIndex:i] isEqual:@"-s"])
            sendPort = [[args objectAtIndex:++i] intValue];
        else if ([[args objectAtIndex:i] isEqual:@"-v"])
            verbosePorts = YES;
        else if ([[args objectAtIndex:i] isEqual:@"-V"])
            verboseEverything = YES;
        else {
            serverName = [args objectAtIndex:i];
            original = NO;
        }
    }

    if (verbosePorts || verboseEverything) [TCPPort _toggleLogging];
    if (verboseEverything) [NSConnection _toggleLogging];

    listener = [[TCPPort alloc] initWithNumber:listenPort];
    if (listener == nil) {
        NSLog(@"couldn't create a listener!");
        [pool release];
        exit(1);
    }
    NSLog(@"listening on TCP port: %@", [listener description]);

    conn = [NSConnection connectionWithReceivePort:listener sendPort:listener];
    if (conn == nil) {
        NSLog(@"couldn't create a connection!");
        [pool release];
        exit(1);
    }
    
    if (original) {
        testObject = [[RemoteTest alloc] init];
        NSLog(@"Setting root object");
        [conn setRootObject:testObject];
        [testObject release];	// let conn own it
    }
    else {
        if (serverName == nil) serverName = [[NSHost currentHost] name];
        sender = [listener connectToNumber:sendPort host:serverName];
        if (sender == nil) {
            NSLog(@"couldn't create a sender (%@ %d)!", serverName, sendPort);
            [pool release];
            exit(1);
        }

        NSLog(@"connecting to: %@", [sender description]);

        conn = [NSConnection connectionWithReceivePort:listener
                                              sendPort:sender];
        if (conn == nil) {
            NSLog(@"couldn't create a connection!");
            [pool release];
            exit(1);
        }

        NSLog(@"Fetching root object from host %@", serverName);
        testObject = (RemoteTest *)[conn rootProxy];
        if (!testObject) {
            NSLog(@"couldn't get root proxy!");
            [pool release];
            exit(1);
        }

        NSLog(@"Remote host: %@", [[testObject host] name]);
        NSLog(@"Remote date: %@", [[testObject date] description]);

        NSLog(@"Sending hello message to host %@", serverName);
        hostName = [[NSHost currentHost] name];
        [testObject log:
            [NSString stringWithFormat:@"Hello from %@!", hostName]];

        NSLog(@"Fetching other object from host %@", serverName);
        otherObject = (RemoteTest *)[testObject otherObject];
        if (otherObject == nil) NSLog(@"Other object is nil");
        else {
            NSLog(@"Other object host: %@", [[otherObject host] name]);
            NSLog(@"Other object date: %@", [[otherObject date] description]);
            NSLog(@"Sending hello message to host %@",
                  [[otherObject host] name]);
            [otherObject log:
                [NSString stringWithFormat:@"Hello from %@!", hostName]];
        }

        NSLog(@"Setting other object on host %@ to my object", serverName);
        [testObject setOtherObject:[[[RemoteTest alloc] init] autorelease]];

    }

    /* become a server */
    


    NSLog(@"Starting run loop");
    [[NSRunLoop currentRunLoop] run];
    NSLog(@"exiting server!");

    [pool release];
    exit(0);
}
