/* ThreadSafeQueue.h created by blaine on Mon 01-Apr-1996 */

/* A dirt simple queue - it doesn't copy, doesn't enumerate, doesn't code, ... */

#import <Foundation/Foundation.h>

@interface ThreadSafeQueue : NSObject {
    NSLock *lock;
    NSMutableArray *array;
}
+ instance;
- headItem;	// remove and return the item at the head (nil if empty)
- tailItem;	// remove and return the item at the tail (nil if empty)
- (void)insertItem:obj;	// inserts at head
- (void)appendItem:obj; // appends at tail
- (unsigned)count;
- (NSArray *)snapshot;

@end
