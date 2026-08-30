/* ExternalEditors.h
 * Copyright 1996-1997 Apple Computer, Inc. (unpublished)
 *
 * DO services for project document editors outside ProjectBuilder.
 */

#import <Foundation/Foundation.h>

@protocol ProjectBuilderExternalFileEditors
- (void)openFile:(NSString *)path;
- (void)saveFile:(NSString *)path;
- (void)closeFile:(NSString *)path;
@end

@protocol ProjectBuilderDOServices
- (BOOL)addFile:(NSString *)path forKey:(NSString *)key
        toProjectDirectory:(NSString *)directory;
- (BOOL)setApplicationClass:(NSString *)className
        inProjectDirectory:(NSString *)directory;
- (oneway void)editor:(id <ProjectBuilderExternalFileEditors>)editor
        didOpenFile:(NSString *)path;
- (oneway void)editor:(id <ProjectBuilderExternalFileEditors>)editor
        didModifyFile:(NSString *)path;
- (oneway void)editor:(id <ProjectBuilderExternalFileEditors>)editor
        didSaveFile:(NSString *)path;
- (oneway void)editor:(id <ProjectBuilderExternalFileEditors>)editor
        didCloseFile:(NSString *)path;
- (oneway void)editorWillTerminate:
        (id <ProjectBuilderExternalFileEditors>)editor;
@end
