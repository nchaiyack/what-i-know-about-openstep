#import <Foundation/Foundation.h>

// An NSConnection delegate object (really Class !)

@interface Authenticator : NSObject

+ (NSData *)authenticationDataForComponents:(NSArray *)components;
    //  generate and return authentication data for DO

+ (BOOL)authenticateComponents:(NSArray *)components withData:(NSData *)signature;
    //  verify authentication data

@end