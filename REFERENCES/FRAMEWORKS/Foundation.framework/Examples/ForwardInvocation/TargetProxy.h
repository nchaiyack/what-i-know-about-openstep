/* TargetProxy.h created by blaine on Tue 30-Jan-1996 */

#import <Foundation/Foundation.h>

@interface TargetProxy : NSProxy {
    id target;
}
// Designated initializer
- initWithTarget:t;

// convenience
+ proxyWithTarget:t;

@end
