/*
 * You may freely copy, distribute and reuse the code in this example.
 * NeXT Software, Inc. disclaims any warranty of any kind, expressed or implied,
 * as to its fitness for any particular use.  This disclaimer applies to all
 * source files in this example.
 */

/* Authenticator main

   Builds an executable with two personas
   	- run with no arguments to assume the server role
   	(and then)
   	- run with the name of your machine to assume the client role
 */

#import <Foundation/Foundation.h>
#import "Authenticator.h"

void client(NSString *hostname) {
    NSConnection *conn;
    NSDistantObject *proxy;

    // find the other process via the nmserver.
    // Note: no actual messages are sent yet
    conn = [NSConnection connectionWithRegisteredName:@"authentication test" host:hostname];
    if (!conn) {
        NSLog(@"didn't connect");
        exit(1);
    }
         // set up authenticator
         // all subsequent DO messages (including the one for rootProxy)
         // will have some authetication data generated and sent along.
         // Also (not required), all replies will be verified.
         // In a real system the authentication data would include a user name etc.
         // and a real password protected signature generator would get involved.
    [conn setDelegate:[Authenticator class]];

    // This message will actually cause some message traffic
    proxy = [conn rootProxy];
    if (!proxy) {
        NSLog(@"didn't get root proxy!");
        exit(1);
    }

    // since this is an example, we don't really care what the "served" object
    // really does, just that we can message it.  So treat it like the NSObject
    // that it is.

    (void)[proxy description];

    // if it didn't work, an exception is raised.
    NSLog(@"sent message (with implicit authentication)");
}

void server() {
    NSConnection *conn = [NSConnection defaultConnection];

    [conn setRootObject:[[[NSObject alloc] init] autorelease]];
    [conn setDelegate:[Authenticator class]];
    if (![conn registerName:@"authentication test"]) {
        NSLog(@"AuthServer: couldn't register!");
        exit(1);
    }
    NSLog(@"serving");
    // this will basically run forever
    [[NSRunLoop currentRunLoop] run];
}

int main (int argc, const char *argv[])
{
   NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
   NSArray *arguments = [[NSProcessInfo processInfo] arguments];
   unsigned limit = [arguments count];

   if (limit == 2)
       client([arguments objectAtIndex:1]);
   else
       server();



   [pool release];
   exit(0);       // insure the process exit status is 0
   return 0;      // ...and make main fit the ANSI spec.
}
