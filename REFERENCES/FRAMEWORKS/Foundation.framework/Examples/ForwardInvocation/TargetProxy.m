/* TargetProxy.m created by blaine on Tue 30-Jan-1996 */

#import "TargetProxy.h"

@implementation TargetProxy

- initWithTarget:t {
    target = [t retain];
    return self;
}

- (void)dealloc {
    [target release];
    [super dealloc];
}

+ proxyWithTarget:t {
    TargetProxy *result = [self alloc];

    // always assume that init methods can substitute!
    result = [result initWithTarget:t];
    return [result autorelease];
}

- (void)forwardInvocation:(NSInvocation *)invocation {
    [invocation invokeWithTarget:target];
}


// The compiler knows the types at the call site but unfortunately doesn't
// leave them around for us to use, so we must poke around and find the types
// so that the invocation can be initialized from the stack frame.
- (NSMethodSignature *)methodSignatureForSelector:(SEL)selector {
    return [target methodSignatureForSelector:selector];
}


// NSProxy does some things that we don't like...

- (NSString *)description {
    return [target description];
}
@end
