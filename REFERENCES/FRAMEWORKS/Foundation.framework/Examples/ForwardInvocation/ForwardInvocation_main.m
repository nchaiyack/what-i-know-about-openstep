/*
 * You may freely copy, distribute and reuse the code in this example.
 * NeXT Software, Inc. disclaims any warranty of any kind, expressed or implied,
 * as to its fitness for any particular use.  This disclaimer applies to all
 * source files in this example.
 */


#import <Foundation/Foundation.h>
#import "TargetProxy.h"

void doThings(NSMutableString *someThing, NSMutableString *anotherThing) {
    NSRange r1, r2;

    if (![[someThing description] isEqual:[anotherThing description]])
        NSLog(@"descriptions not equal!");
    [someThing appendString:@"something else"];
    	// will appear to have happened to anotherThing
    if (![[someThing description] isEqual:[anotherThing description]])
        NSLog(@"descriptions after appending not equal!");
    r1 = [someThing rangeOfString:@"some"];
    r2 = [anotherThing rangeOfString:@"some"];
    if (r1.location != r2.location)
        NSLog(@"locations not equal");
    if (r1.length != r2.length)
        NSLog(@"lengths not equal");
}

int main (int argc, const char *argv[])
{
   NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];

   NSMutableString *funny = [[@"and now for " mutableCopy] autorelease];
   TargetProxy *tp = [TargetProxy proxyWithTarget:funny];

   doThings(funny, (NSMutableString *)tp);

   NSLog(@"done!");

   [pool release];
   exit(0);       // insure the process exit status is 0
   return 0;      // ...and make main fit the ANSI spec.
}
