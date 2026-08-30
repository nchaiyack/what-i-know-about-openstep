#import <AppKit/AppKit.h>

void main(int argc, char *argv[]) {
   NSAutoreleasePool * pool     = [[NSAutoreleasePool alloc] init];
   NSDictionary *info           = [[NSBundle mainBundle] infoDictionary];
   NSString *principalClassName = [info objectForKey: @"NSPrincipalClass"];
   NSString *mainNibFile        = [info objectForKey: @"NSMainNibFile"];
   if (principalClassName) {
      Class principalClass = NSClassFromString(principalClassName);
      if (principalClass) {
         [principalClass sharedApplication];
         if ([NSBundle loadNibNamed: mainNibFile owner: NSApp]) {
            [pool release];
            [NSApp run];
            [NSApp release];
            exit(0);
         }
         else NSLog(@"Unable to load nib file: %@, exiting", mainNibFile);
      }
      else NSLog(@"Unable to find class: %@, exiting", principalClassName);
   }
   else NSLog(@"No NSPrincipalClass specified in info dictionary, exiting");
   [NSApp release];
   [pool release];
   exit(1);
}
