/*
 * You may freely copy, distribute and reuse the code in this example.
 * NeXT Software, Inc. disclaims any warranty of any kind, expressed or implied,
 * as to its fitness for any particular use.  This disclaimer applies to all
 * source files in this example.
 */

/* Multithreaded DO example
 * Usage: no arguments, acts as server
 *	any argument, acts as a client (as many as you want)
 * The server and each client all spin off several threads to do their business.
 */

#import <Foundation/Foundation.h>
#import "ThreadSafeQueue.h"

int ClientCounter = 1000;
id ClientProxy;
NSConditionLock *CLock;

@interface ThreadSafeQueue (Helper)
+ (void)hammer;
@end

@implementation ThreadSafeQueue (Helper)
+ (void)hammer {
   unsigned condition;

   while (ClientCounter-- > 0) {
        NSAutoreleasePool *pool = [NSAutoreleasePool new];
        id item = [ClientProxy headItem];

        if (item) [ClientProxy appendItem:item];
        [pool release];
   }
   // synchronize with main thread
   [CLock lock];
   condition = [CLock condition];
   [CLock unlockWithCondition:++condition];
}
@end

int main (int argc, const char *argv[]) {
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    NSArray *arguments = [[NSProcessInfo processInfo] arguments];
    unsigned int limit = [arguments count];

    if (limit == 1) {
        // server
        ThreadSafeQueue *queue = [ThreadSafeQueue instance];
        NSConnection *conn = [NSConnection defaultConnection];
        [conn setRootObject:queue];
        [conn registerName:@"Queue"];

        [queue appendItem:@"string1"];
        [queue appendItem:@"string2"];
        [queue appendItem:@"string3"];
        [queue appendItem:@"string4"];
        [queue appendItem:@"string5"];
        [queue appendItem:@"string6"];
        [conn runInNewThread];
        [conn runInNewThread];
        [conn runInNewThread];
        [conn runInNewThread];
        [conn runInNewThread];
        [conn runInNewThread];
        NSLog(@"server running in a few threads");
        [[NSRunLoop currentRunLoop] run];
    }
    else {
        // client
        NSConnection *conn = [NSConnection connectionWithRegisteredName:@"Queue" host:nil];
        unsigned nThreads = 6, countThreads;

        if (!conn) {
            NSLog(@"didn't connect");
            exit(1);
        }
        CLock = [[NSConditionLock alloc] init];

        // enableMultipleThreads allows each of these client threads to use ClientProxy
        // and implicitly add their runLoop to the connection.  Alternatively, we could
        // have, in each thread, explicitly done
        //	[[ClientProxy connectionForProxy] addRunLoop:[NSRunLoop currentRunLoop]];
        [conn enableMultipleThreads];

        ClientProxy = [conn rootProxy];
        for (countThreads = 0; countThreads < nThreads; ++countThreads)
            [NSThread detachNewThreadSelector:@selector(hammer) toTarget:[ThreadSafeQueue self] withObject:nil];

        // synchronize with worker threads so that we don't lose an item
        [CLock lockWhenCondition:nThreads];
        
        NSLog(@"done hammering, strings should be out of order:");
        NSLog(@"%@", [ClientProxy snapshot]);
    }
    [pool release];
    exit(0);       // insure the process exit status is 0
    return 0;      // ...and make main fit the ANSI spec.
}
