

#import <AppKit/AppKit.h>
#import <NEXTIME/NTMovieScreenCell.h>

@interface Controller: NSObject
{
	id			infoPanel;
	id			inspectorPanel;
        id			preferencesPanel;
        id			videoResizeMatrix;
}

- init;
- (void)dealloc;
- (void)showInfoPanel:sender;
- (void)showInspectorPanel:sender;
- (void)showPreferencesPanel:sender;
- (void)openDocument:sender;
- ( void)setDocumentSizingPolicy:sender;

+ (NTMovieScreenCellSizing)sizingPolicy;
+ (void)setSizingPolicy:(NTMovieScreenCellSizing)policy;
@end
