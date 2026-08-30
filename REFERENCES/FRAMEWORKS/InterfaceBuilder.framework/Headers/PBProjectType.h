
// PBProjectType.h
// Copyright 1996-1997 Apple Computer, Inc.

#import <Foundation/Foundation.h>
#import <ProjectBuilder/PBSystem.h>
#import <ProjectBuilder/PBProject.h>

@interface PBProjectType : NSObject
{
    NSDictionary * infoDict;
    NSString * wrapperDirectory;
    NSMutableArray * allowableSubprojectTypes;
    NSDictionary * additionalAttributes;
}
+ (NSArray *) rootProjectTypeNames;
+ (PBProjectType *) projectTypeNamed: (NSString*) name;
- initFromPath: (NSString *) projectTypeWrapper;
- initFromPath: (NSString *) projectTypeWrapper dictionary: alreadyLoadedInfoDict;
- (void) awake;  // gets called after initialization, to connect up any object graph
- (PBProject *) instantiateProjectNamed: (NSString *) name
                            inDirectory: (NSString *) directory
                 appendProjectExtension: (BOOL) appendExtension;
- (void) customizeNewProject: (PBProject *) project;  // called by above method, but can be overridden
- (NSString *) projectTypeName;

   // Project Type Attributes live in the Info.table in the wrapper
- (NSDictionary *) infoTable;

// Many Project Type Attributes have convenient accessor methods
- (NSString *)inspectorClassName;
- (NSString *)makefileDirectory;
- (NSArray *)sourceKeys;
- (NSArray *)resourceKeys;
- (NSArray *)otherKeys;
- (NSArray *)subprojKeys;
- (NSArray *)buildTargets;
- (BOOL)creatableInExistingDirectory;
- (NSString *)defaultExtensionForProjectDir;
- (BOOL)hasIcons;  // e.g. apps have icons built into them
- (BOOL) maintainsFile: (NSString *) fileName;
- (BOOL) doesMajorVersioning; // versioning attributes for libraries
- (BOOL) isAggregate;

- (NSArray *)allowableSuperprojectTypes; // names of PBProjectTypes
- (NSArray *)allowableSubprojectTypes;  // names of PBProjectTypes
- (void) addAllowableSubprojectType: (PBProjectType *) projType;

// These attributes of a project type are in addition to
// the aspects provided via the api defined above.
// The names of the attributes are given below.
// This part of the API is still under construction.
- (BOOL) projectHasAttribute:(NSString *)attrName;	// true if projects of this type have the attr.

@end

PB_EXTERN NSString	*PB_BundleExtension_ProjectAttribute;
PB_EXTERN NSString	*PB_PrincipalClass_ProjectAttribute;


@interface PBApplicationProjectType : PBProjectType
- (void) customizeNewProject: (PBProject *) project;
@end

@interface PBToolProjectType : PBProjectType
- (void) customizeNewProject: (PBProject *) project;
@end

@interface PBPaletteProjectType : PBProjectType
- (void) customizeNewProject: (PBProject *) project;
@end
