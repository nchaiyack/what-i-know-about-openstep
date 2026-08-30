/* RemoteTest.m created by blaine on Tue 16-Apr-1996 */

#import "RemoteTest.h"

@implementation RemoteTest
- init {
    [super init];
    myHost = [[NSHost currentHost] retain];
    otherObject = nil;
    return self;
}

- (void)dealloc {
    [myHost release];
    [super dealloc];
}

- (NSHost *)host {
    return myHost;
}

- (NSDate *)date {
    return [NSDate date];
}

- (void)log:(NSString *)message {
    NSLog(@"%@", message);
}

- (void)setOtherObject:(NSObject *)anObject {
    [anObject retain];	// in case it == otherObject & there is only 1 ref
    [otherObject release];
    otherObject = anObject;
}

- (NSObject *)otherObject {
    return [[otherObject retain] autorelease];
    	// most expensive but safest way to hand out an attribute
        // Alternatives are: return otherObject, but if later someone
    	// does a setOtherObject the caller will be left with garbage
    	// Another alternative is to return otherObject here but do
    	// a [otherObject autorelease] in the setOtherObject: method.
    	// This works most of the time... but... fails if a setOtherObject:
    	// occurs after a new autorelease pool is formed then reclaimed, again
    	// leaving the caller holding garbage.
}

@end
