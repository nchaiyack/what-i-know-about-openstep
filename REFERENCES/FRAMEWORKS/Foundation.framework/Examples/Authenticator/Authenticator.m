#import "Authenticator.h"

unsigned char byteCheckSum(unsigned char input, const unsigned char *bytes, unsigned limit) {
    unsigned index;
    unsigned char result = input;

    for (index = 0; index < limit; ++index)
        result ^= bytes[index];
    return result;
}


@implementation Authenticator

// we will offer our class as the signature generator, thus we use
// factory methods as the delegates to NSConnection
+ (NSData *)authenticationDataForComponents:(NSArray *)components {
    unsigned int index;
    unsigned char checksum = 0;

    for (index = 0; index < [components count]; ++index) {
        id item = [components objectAtIndex:index];

        if ([item isKindOfClass:[NSData class]])
            checksum = byteCheckSum(checksum, [item bytes], [item length]);
    }

    return [NSData dataWithBytes:&checksum length:1];
}

+ (BOOL)authenticateComponents:(NSArray *)components withData:(NSData *)signature {
    //  verify authentication data
    // A real authenticator would have a way of verifying the signature without
    // recomputing it.  We don't, in this example, so just recompute.
    NSData *recomputedSignature = [self authenticationDataForComponents:components];
    
    if (![recomputedSignature isEqual:signature]) {
        NSLog(@"received signature %@ doesn't match computed signature %@", signature, recomputedSignature);
        return NO;
    }
    return YES;
}

+ (BOOL)connection:(NSConnection *)ancestor shouldMakeNewConnection:(NSConnection *)conn {
    // set up all new (per-client) connections to have the same delegate
    [conn setDelegate:[ancestor delegate]];
    return YES;
}


@end