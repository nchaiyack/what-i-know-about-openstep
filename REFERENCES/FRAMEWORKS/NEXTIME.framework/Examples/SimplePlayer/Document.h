
#import <NEXTIME/NTMovieDocument.h>
#import <NEXTIME/NTMovieControlView.h>
#import <NEXTIME/NTMovieScreen.h>
#import "DocumentView.h"

@interface Document: NSObject
{
	NSWindow	*myWindow;
	DocumentView *	docView;
}

- initByReferencingFile:(NSString *)file;
- (void)show;

@end
