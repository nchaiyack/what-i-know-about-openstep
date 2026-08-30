/*
 *  DocumentView.h
 *	
 */


#import <NEXTIME/NTMovieDocument.h>
#import <NEXTIME/NTMovieControlView.h>
#import <NEXTIME/NTMovieScreen.h>

@interface DocumentView : NSView
{
@private
	NTMovieControlView	*control;
	NTMovieScreen	*videoWell;
        NSSize		movieSize;
}

- initWithFrame:(NSRect)frameRect;
- (BOOL)setMovieFile:(NSString *)file;
- (id <NTMovieDocument>)document;
- (NTMovieControlView *)control;
- (NTMovieScreen *)videoWell;

- (void)_resizePolicyChanged:(NSNotification *)note;

- (NSSize)normalSize;
- (NSSize)doubleSize;
@end
