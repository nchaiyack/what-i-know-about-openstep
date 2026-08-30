/* RemoteTest.h created by blaine on Tue 16-Apr-1996 */

#import <Foundation/NSDate.h>
#import <Foundation/NSHost.h>
#import <Foundation/NSString.h>

@interface RemoteTest : NSObject
{
        NSObject *otherObject;
        NSHost *myHost;
}

- (NSHost *)host;
- (NSDate *)date;
- (void)log:(NSString *)message;
- (void)setOtherObject:(NSObject *)anObject;
- (NSObject *)otherObject;

@end