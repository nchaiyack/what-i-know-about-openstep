// PBBundleHost.h - Functionality available to ProjectBuilder extension bundles
//
// Copyright 1995-1997 Apple Computer, Inc. (unpublished)
// All rights reserved.

#import <Foundation/Foundation.h>
#import "PBSystem.h"

#if defined(WIN32) || defined(__MACH__)

#import <AppKit/AppKit.h>

// PB Bundle Loading
//    At launch time, a single PBBundleHost inside ProjectBuilder attempts to
//    load all bundle wrappers specified in the user's preferences 
//    (ProjectBuilder's "BundlesLoadedAtLaunch" preference).  Further, a set 
//    of projectTypes are loaded from various locations.  Each projectType
//    wrapper may contain a bundle executable that will be loaded at launch
//    time.  Functionality in these bundles can be registered with the
//    application via calls made from bundle initialization - the preferred
//    method is +initialize on the bundle's principal class, since +load can
//    be fired too early before NSBundle methods are guaranteed to work.
//    These calls should be made to the PBBundleHost, which is accessible as
//    NSApp.


// PB SCM Integration
// The PBBundleHost can host bundles of any sort.  However, it is especially useful
// for loading interfaces to Software Configuration Management systems.
// The PBBundleHost interface was explicitly designed with this capability in mind.
// To register an implementer of the PBConfigManager protocol, call
// registerConfigManager: on the PBBundleHost.  Bundles providing a ConfigManager
// are encouraged to also register a series of project- and file-specific
// operations in PB's menus and provide an inspector panel.  Preferences specific
// to the integration can be managed with a preferences panel registered with the
// PBBundleHost.

@protocol PBConfigManager <NSObject>
- (BOOL) managesPath: (NSString *) path;
     // Should return YES iff this bundle can grant the user write permission to
     // path under normal circumstances.  Should be a cheap call to just check
     // if calling the following more expensive method has a chance in succeeding.

- (BOOL) makePathWritable: (NSString *) path;
     // This actually requests the per-file "check out" from the SCM system.
     // Called when a file transitions from saved to unsaved (dirty) state and
     // the associated file is read only. Should return YES if file was made
     // writable to PB.
@end

// PB Panel Controllers
// The PBBundleHost will inform controllers of inspector and preference views that
// they are in need of refreshing their contents.  This might happen on initial
// exposure of the panel or if relevant data affecting the browser changes
// (e.g. the selected file/project, in the case of the inspector).

@interface PBInspectorController : NSObject
{
    NSWindow *window;
    NSView *contentView;
    id tool;
}
- (NSString *) inspectorName;
     // Name that will appear on pop-up to select this panel.
- (NSView *)contentView;
   // Lazily called to provide panel as needed.
- (void)revert;
   // Called when panel displayed or relevant data changes (e.g. selectedFile)
@end

// Preferences specific to the operation of a PB Bundle can be managed
// and storing preferences as a sub-dictionary of PB's preferences, such as:
//   [[NSUserDefaults standardUserDefaults] persistentDomainForName: @"MyConfigMgr"]

@interface PBPreferenceController : NSObject
{
    NSWindow *window;
    NSView *contentView;
    id prefController;
}
- (NSString *) viewName;
- (NSView *)contentView;
- (void)revert;
@end


@protocol PBBundleHost
// Register bundle functionality
- (BOOL) registerConfigManager: (id<PBConfigManager>) configManager;
- (BOOL) registerProjectSubmenu: (NSMenu *) menu;
- (BOOL) registerFileSubmenu: (NSMenu *) menu;
- (BOOL) registerToolsSubmenu: (NSMenu *) menu;
#ifdef NOT_IMPLEMENTED
- (BOOL) registerInspectorController: (PBInspectorController *) inspector;
- (BOOL) registerPreferenceController: (PBPreferenceController*) prefPanel;
#endif

// Query app's state:
- (NSString*) selectedProjectName;
     // Returns name (as set in inspector panel) of the active project
- (NSString*) selectedProject;
     // Returns path to currently active project or nil if none.
- (NSString*) currentlyActiveFile;
     // Returns path to currently active file or nil if none.  This is the file
     // that would receive key events from the user typing.
- (NSArray*) selectedFiles;
     // Returns array of paths for all currently selected files or nil if none.
- (NSArray*) dirtiedFiles;
     // Returns array of paths of files (including PB.project files)
     // that are "unsaved".  Returns nil if none.

// Change app's state:
- (BOOL) openFileOrProject: (NSString *) path;
     // equivalent to using Cmd-D and typing in path
- (BOOL) revertPath: (NSString *) path;
     // Revert file or all files under directory named by path.
     // If files have been modified releative to a loaded buffer, the user
     // will be prompted to have the files re-loaded into PB.
     // Returns YES on successful reload.
- (BOOL) queryDirtiedFiles;
     // Prompts user to save all files and projects with dirtied buffers.
     // Returns YES if any files were saved.
- (NSTextView*) viewForFile: (NSString *) path;
     // Calls openFileOrProject: on path if not already loaded.
     // Returns nil if file could not be loaded as text.  This
     // allows access to the underlying file contents, the selection, and
     // the associated NSTextStorage.  Files can be edited programmatically
     // this way.

// Project editing:
- (BOOL) addFileWithPath: (NSString *) filePath
               toProject: (NSString *) projectPath;
- (BOOL) removeFileFromProject: (NSString *) filePath;
@end

#endif

// PB Notifications
// The following notifications can be observed by PB Bundles from the
// [NSNotificationCenter defaultCenter].  The following notification names
// may be used.  The object provided in the subscription to the notification
// should be nil to get all notifications or an NSString containing the path
// to the file or "PB.project" project file in which the observer is specifically
// interested.  The object of the notifications is an NSString containing the
// path of the referenced file or project.

// Top-level Project Notifications:
// The following four notifications are only sent for top-level projects.  
// The top-level project represents the document that is openned and closed
//  in PB and these notifications are document-oriented.  The object of these
// notifications is the instance of PBProject corresponding to the top-level PB.project.
// NOTE: only one PBProject object can exist for a given PB.project file.
PB_EXTERN NSString * PBProjectWillOpenNotification; 
PB_EXTERN NSString * PBProjectDidOpenNotification;
PB_EXTERN NSString * PBProjectWillCloseNotification;
PB_EXTERN NSString * PBProjectDidCloseNotification;

// Project Upgrade Notifications:
// PB.project files prior to 4.1 get automatically upgraded in-memory upon being
// opened in ProjectBuilder.  This does not trigger an auto-save of the file as a
// normal modification would, but these notifications are sent.   The object of these
// notifications is the instance of PBProject corresponding to the upgraded PB.project.
PB_EXTERN NSString * PBProjectWillUpgradeNotification;
PB_EXTERN NSString * PBProjectDidUpgradeNotification;

// Project Change Notifications:
// When the ProjectBuilder user modifies a project definition (e.g. adds a file,
// changes a build flag, marks a resource as localizable), the project document
// gets dirtied and PBProjectDidChangeNotification is sent.  An auto-save is normally
// then scheduled, eventually resulting in PBProjectWillSaveNotification and culimnates
// in either a PBProjectDidSaveNotification or PBProjectSaveDidFailNotification.
// The object of these notifications is the instance of PBProject corresponding to the 
// PB.project file.
PB_EXTERN NSString * PBProjectDidChangeNotification;
PB_EXTERN NSString * PBProjectWillSaveNotification;
PB_EXTERN NSString * PBProjectDidSaveNotification;
PB_EXTERN NSString * PBProjectSaveDidFailNotification;

// Project FileSet Change Notifications
// Because adding and removing files from a project are significant events with respect
// to integrating an SCM system, these special notifications are sent out in addition to
// the normal PBProjectDidChangeNotification.  The object of these notifications is the
// instance of PBProject corresponding to the PB.project file.  Additionally, a "userInfo"
// dictionary is attached with: 
//   {"file" = name of file added/deleted, 
//    "key" = the category of the file in the project 
//                   (i.e. one of the Project File Keys declared in PBProject.h)
//   }.
PB_EXTERN NSString * PBFileAddedToProjectNotification;
PB_EXTERN NSString * PBFileRemovedFromProjectNotification;

// File Viewing Notifications:
// As files are loaded and unloaded from buffers in PB, the following notifications are sent,
// with the object of the notification a string containing the path of the file.
PB_EXTERN NSString * PBFileWillOpenNotification;
PB_EXTERN NSString * PBFileDidOpenNotification;
PB_EXTERN NSString * PBFileWillCloseNotification;
PB_EXTERN NSString * PBFileDidCloseNotification;

// File Editing/Saving Notifications:
// These notifications are sent as files are transitioned into an unsaved or dirtied state
// (PBFileDidChangeNotification) and saved by the user (PBFileWillSaveNotification
// before and either PBFileDidSaveNotification or PBFileSaveDidFailNotification
// afterwards).  Files can be reverted back to their saved copy (PBFileWillRevertNotification
// and PBFileDidRevertNotification) as well.
PB_EXTERN NSString * PBFileDidChangeNotification;  // buffer dirtied
PB_EXTERN NSString * PBFileWillSaveNotification;
PB_EXTERN NSString * PBFileDidSaveNotification;
PB_EXTERN NSString * PBFileSaveDidFailNotification;
PB_EXTERN NSString * PBFileWillRevertNotification;
PB_EXTERN NSString * PBFileDidRevertNotification;

// File Delete/Move Notifications:
// After a file is removd from disk or renamed, the following notifications are sent. As
// above the object of the notification a string containing the path of the file.  In the case,
// of rename, a userInfo dictionary is attached containing: { "NewFilePath" = <new path>; }.
PB_EXTERN NSString * PBFileDeletedNotification;
PB_EXTERN NSString * PBFileRenamedNotification;

// Project Build Notifications:
// As builds are accomplished from within PB, notifications are sent alerting
// subscribers of status changes to this operation.  The object is the string containing
// the project path.
PB_EXTERN NSString * PBProjectBuildWillBeginNotification;
PB_EXTERN NSString * PBProjectBuildDidBeginNotification;
PB_EXTERN NSString * PBProjectBuildDidSucceedNotification;
PB_EXTERN NSString * PBProjectBuildDidFailNotification;
PB_EXTERN NSString * PBProjectBuildDidStopNotification;

// File Browser Notifications
// As the user navigates around the project and file hierarchy in the project 
// window browser, the following notifications are sent so that open panels can
// track the selection in the browser.  As a new project is clicked into, 
// PBSelectedProjectDidChangeNotification is sent with the path of the project or
// subproject.  As a new file is selected, the PBSelectedFileDidChangeNotification
// object denotes the path of the selected file.
PB_EXTERN NSString * PBSelectedProjectDidChangeNotification;
PB_EXTERN NSString * PBSelectedFileDidChangeNotification;

