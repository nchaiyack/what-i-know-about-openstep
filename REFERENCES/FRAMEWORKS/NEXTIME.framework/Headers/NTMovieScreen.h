
#import <AppKit/NSControl.h>

@interface NTMovieScreen : NSControl
{
@private
	void *				_private;
}

+ (Class)cellClass;
/* 
 * returns the NTMovieScreenCell class, or the class set by 'setCellClass:'
 */

+ (void)setCellClass:(Class)class;
/*
 * sets the cell created for NTMovieScreen instances.  The default is
 * NTMovieScreenCell
 */

- (BOOL)setMovieFile:(NSString *)path;
/*
 * opens the movie file "path" and updates the receivers cell.  Returns
 * 'YES' if "path" is a valid movie, 'NO' otherwise.
 */

- (NSString *)movieFile;
/* Return the movie file repreesnted by the movie screen. */
@end

