/* DataStream.h created by blaine on Wed 03-Apr-1996 */

#import <Foundation/Foundation.h>

@interface DataStream : NSObject {
    NSMutableArray *array;
    unsigned int offset;	// into the first item
    unsigned int length;	// from offset to end
}

- (void)appendData:(NSData *)item;
- (unsigned int)length;
- (BOOL)getBytes:(void *)bytes length:(unsigned)len;
- (void)fillData:(NSMutableData *)data length:(unsigned)len;
@end
