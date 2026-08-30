/* ThreadSafeQueue.m created by blaine on Mon 01-Apr-1996 */

#import "ThreadSafeQueue.h"

@implementation ThreadSafeQueue

+ instance {
    ThreadSafeQueue *result = [self alloc];
    result->lock = [NSLock new];
    result->array = [NSMutableArray new];
    return [result autorelease];
}

- (void)dealloc {
    [lock release];
    [array release];
}

- headItem {
   id result;
   [lock lock];
   if ([array count] == 0)
       result = nil;
   else {
       result = [array objectAtIndex:0];
       // hold onto it in case the queue is the only retainer
       [[result retain] autorelease];
       [array removeObjectAtIndex:0];
   }
   [lock unlock];
   return result;
}

- tailItem {
   id result;
   [lock lock];
   if ([array count] == 0)
       result = nil;
   else {
       result = [array lastObject];
       // hold onto it in case the queue is the only retainer
       [[result retain] autorelease];
       [array removeLastObject];
   }
   [lock unlock];
   return result;
}

- (void)insertItem:obj {
   [lock lock];
   [array insertObject:obj atIndex:0];
   [lock unlock];
}

- (void)appendItem:obj {
   [lock lock];
   [array addObject:obj];
   [lock unlock];
}

- (unsigned)count {
    return [array count];
}

- (NSArray *)snapshot {
   return [[array copy] autorelease];
}

@end
