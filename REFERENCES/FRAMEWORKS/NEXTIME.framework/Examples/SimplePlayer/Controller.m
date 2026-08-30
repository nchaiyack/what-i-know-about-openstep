

#import "Controller.h"
#import "Document.h"
#import "SimplePlayer_Globals.h"

static NSString *curDirectory = nil;	/* Directory for open panel */

@implementation Controller

// Register our defaults
+ (void)initialize {
    if (self == [Controller class]) {
        NSDictionary *dict = [NSDictionary dictionaryWithObjectsAndKeys:
            @"EvenMultiples", @"NTVideoCellSizing",
            nil];
        NSArray *types = [NSArray arrayWithObject: NSFilenamesPboardType];

        [[NSUserDefaults standardUserDefaults] registerDefaults:dict];
	[NSApp registerServicesMenuSendTypes:types returnTypes:NULL];
    }
    return;
}

+ (NTMovieScreenCellSizing)sizingPolicy
{
        NSString * policyString;

        policyString = [[NSUserDefaults standardUserDefaults]
        			stringForKey: @"NTVideoCellSizing"];
        if (  policyString == nil
           || [policyString isEqualToString:@"EvenMultiples"] )
        {
        	return NTMovieScreenCellPowerOfTwoSizing;
        }
        if ( [policyString isEqualToString:@"Normal"] )
        {
        	return NTMovieScreenCellNormalSizing;
        }
        if ( [policyString isEqualToString:@"Continuous"] )
        {
        	return NTMovieScreenCellContinuousSizing;
        }
        if ( [policyString isEqualToString:@"MaintainAspectRatio"] )
        {
        	return NTMovieScreenCellMaintainAspectRatioSizing;
        }
        return NTMovieScreenCellPowerOfTwoSizing;
}

+ (void)setSizingPolicy:(NTMovieScreenCellSizing)policy
{
        NSString * policyString;
	NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
	NSMutableDictionary *domainDict;
	NSString *domain = [[NSProcessInfo processInfo] processName];
        
        switch ( policy )
        {
		case NTMovieScreenCellNormalSizing:
        		policyString = @"Normal";
        		break;
                default:
        	case NTMovieScreenCellPowerOfTwoSizing:
                        policyString = @"EvenMultiples";
                        break;
        	case NTMovieScreenCellContinuousSizing:
                        policyString = @"Continuous";
                        break;
        	case NTMovieScreenCellMaintainAspectRatioSizing:
                        policyString = @"MaintainAspectRatio";
                        break;
        }
        domainDict = [[[defaults persistentDomainForName:domain] mutableCopy]
        							autorelease];
        [domainDict setObject:policyString forKey:@"NTVideoCellSizing"];
	[defaults setPersistentDomain:domainDict forName:domain];
        [[NSNotificationCenter defaultCenter]
		postNotificationName: NTResizePolicyChangeNotification
                object:self];
}

- init
{
	self = [super init];
	if ( self == nil )
		return nil;
        return self;
}

- (void)dealloc
{
	[[NSUserDefaults standardUserDefaults] synchronize];
	if ( infoPanel )
		[infoPanel release];
	if ( inspectorPanel )
		[inspectorPanel release];
	if ( preferencesPanel )
		[preferencesPanel release];
	[super dealloc];
}

- (void)showInfoPanel:sender
{
    if (!infoPanel)
        [NSBundle loadNibNamed:@"InfoPanel.nib" owner:self];
    [infoPanel makeKeyAndOrderFront:self];
}

- (void)showInspectorPanel:sender
{
    if (!inspectorPanel)
        [NSBundle loadNibNamed:@"InspectorPanel.nib" owner:self];
    [inspectorPanel makeKeyAndOrderFront:self];
}

- (void)showPreferencesPanel:sender
{
    if (!preferencesPanel)
        [NSBundle loadNibNamed:@"PreferencesPanel.nib" owner:self];
    [preferencesPanel makeKeyAndOrderFront:self];
    [videoResizeMatrix selectCellWithTag:[Controller sizingPolicy]];
}

- (void)openDocument:sender
{
	Document *newDocument;
	NSOpenPanel *openPanel;
	NSArray *filenames;
	int i, count;
	
	openPanel = [NSOpenPanel openPanel];
	[openPanel setCanChooseFiles:YES];
	[openPanel setAllowsMultipleSelection:YES];
        if ( curDirectory != nil )
            [openPanel setDirectory:curDirectory];
        else
       	    [openPanel setDirectory:NSHomeDirectory()];
	i = [openPanel runModalForTypes:[NTMovieDocument readableMovieFileTypes]];
	if ( i != NSOKButton )
		return;
	filenames = [openPanel filenames];
	count = [filenames count];
	for ( i = 0; i < count; ++i )
	{
	    newDocument = [[Document alloc]
	    		initByReferencingFile:[filenames objectAtIndex:i]];
            if ( newDocument == nil )
            {
        	continue;
            }
	    [newDocument show];
	    // We let tke kit keep track of windows and the delegate
	    // documents, using
            // [[[NSApplication sharedApplication] mainWindow]
	    // to fish out the current document when needed.

	}
        // Keep track of the 'current directory'
        [curDirectory autorelease];
        curDirectory = [[[filenames objectAtIndex:(count - 1)]
               		stringByDeletingLastPathComponent] copy];
}

- ( void)setDocumentSizingPolicy:sender
{
	[Controller setSizingPolicy:[[videoResizeMatrix selectedCell] tag]];
}

/* NSApplication delegate methods */
- (BOOL)application:(NSApplication *)application
           openFile:(NSString *)filename
{
	Document *newDocument;

	newDocument = [[Document alloc] initByReferencingFile:filename];
        if ( newDocument == nil )
        {
        	return NO;
        }
	[newDocument show];
	// We let tke kit keep track of windows and the delegate
	// documents, using
        // [[[NSApplication sharedApplication] mainWindow]
	// to fish out the current document when needed.

        return YES;
}

@end
