// PBProject.h
// Copyright 1992-1997 Apple Computer, Inc.

// NOTE: This API is tentative and is subject to change in future releases.
//   No assurance is provided that backward compatibility will be kept.

#import <Foundation/Foundation.h>
#import <ProjectBuilder/PBSystem.h>

typedef int ProjectMutationBits;
@class PBProjectType;

@interface PBProject : NSObject 
{
    NSMutableDictionary * dict;
    NSString * projectDir;
    NSString * languageDirCache;
    NSMutableArray * subprojects;
    PBProject * superProject;
    NSString * canonicalFile;
    NSDate * fileModTime;
    ProjectMutationBits	touched;
	NSMutableString *errorMessage;
}
+ (PBProject *) parse: (NSString *) pathName;
+ (Class)arrayClass;
+ (Class)dictionaryClass;

- (BOOL) checkDictionary;
- (BOOL) unparse;
- (NSString *) errorMessage;

- (id)copyWithZone:(NSZone *)zone;; //produces immutable copy!

- (void)setObject: (id)anObject forKey: (NSString *)key;
- (id)objectForKey: (NSString *)key;
- (void)removeObjectForKey:(NSString *)aKey;
- (void)renameProject:(NSString *)pathName;

- (NSString *) canonicalFile;
- (PBProjectType *) projectType;
- (NSString *) projectTypeName;
- (NSString *) projectName;
- (NSString *) projectDir;
- (NSString *) languageDir; 
- (NSString *) languageName;
- (NSString *) appIconFileForOSType: (int) anOS;
- (NSString *) appHelpFileForOSType: (int) anOS;
- (NSString *) bundleExtension;
- (NSMutableArray *) docExtensionsForOSType: (int) anOSType;
- (NSString *) versionNb;
- (NSString *) applicationClass;// depricated API, use principalClass
- (NSString *) principalClass;
- (NSString *) mainNibFileForOSType: (int) anOSType;

- (NSString *) projectVersion;
- (void)setProjectVersion:(NSString *)version;

- (NSString *) shouldGenerateMain;
- (void)setShouldGenerateMain: (NSString *) shouldI;

- (void) setTouched: (ProjectMutationBits) touch;
- (ProjectMutationBits) touched;

- (NSDictionary *) filesTable;
- (NSMutableArray *) fileListForKey:(NSString *)aKey create:(BOOL)createIt;
- (NSMutableArray *) fileListForKey:(NSString *)aKey;  // creates an empty one if nil
- (NSString *) keyForFile:(NSString *)aFile;
    /* If nil is returned, there is no such file in project. Otherwise the key
     * associated to the category the file lies in is returned.
     */
     
- (NSArray *)otherLinkedOFiles;
- (void)addSystemExtensions:(NSString *)ext;
- (NSArray *)systemExtensions;

- (void)setVersionNb:(NSString *)vn;
- (void)setProjectType:(NSString *)type; 
- (void)setProjectDir:(NSString *)dir;
- (void)setProjectName:(NSString *)name;
- (void)setLanguageName:(NSString *)l;
- (void)setAppIconFile: (NSString *)iconFile forOSType: (int) anOS;
- (void)setAppHelpFile: (NSString *)helpFile forOSType: (int) anOS;
- (void)setMainNibFile: (NSString *) mainNib forOSType: (int) anOS;
- (void)setApplicationClass:(NSString *)appClass; // old; do not use;
- (void)setPrincipalClass:(NSString *)pClass;
- (void)setBundleExtension:(NSString *)ext;

// For all the following 'aFile' is a fileName not a full pathName
- (void)addFile:(NSString *)aFile key:(NSString *)aKey;
- (void)addFileToFront:(NSString *)aFile key:(NSString *)aKey;
- (void)removeFile:(NSString *)aFile key:(NSString *)aKey;
- (NSDictionary *)localFiles;
- (BOOL)isLocalizable:(NSString *)aFile;
- (void)makeFile:(NSString *)aFile localizable:(BOOL)loc;

- (NSString *)buildDir;
- (NSArray *) parseSubprojects;
- (PBProject *)parseSubproject: (NSString *)subKey;
- (BOOL)isPublic:(NSString *)aFile;
- (void)makeFile:(NSString *)aFile public:(BOOL)isPublic;
- (NSArray *)subprojects;
- (PBProject *)superProject;
- (PBProject *)rootProject;
- (PBProject *)nonAggregateRootProject;

- (NSString *) lookupMakeVariable: (NSString *) makeVariable;
- setMakeVariable: (NSString *) makeVariable toValue: (NSString *) value;
- (NSDictionary *) makeEnvironment;  
@end


// Values that can be used in ProjectMutationBits

#define TOUCHED_NOTHING		(0)
#define TOUCHED_EVERYTHING	(1 << 0)
#define TOUCHED_PROJECT_NAME	(1 << 1)
#define TOUCHED_LANGUAGE	(1 << 2)
#define TOUCHED_PROJECT_TYPE	(1 << 3)
#define TOUCHED_INSTALL_DIR	(1 << 4)
#define TOUCHED_ICON_NAMES	(1 << 5)
#define TOUCHED_FILES		(1 << 6)
#define TOUCHED_MAINNIB		(1 << 7)
#define TOUCHED_APPCLASS	(1 << 8) // use TOUCH_PRINCIPALCLASS
#define TOUCHED_PRINCIPALCLASS	(1 << 8)
#define TOUCHED_TARGETS		(1 << 9)
#define TOUCHED_PB_PROJECT	(1 << 10)
#define TOUCHED_SYST_EXT	(1 << 11)
#define TOUCHED_EXTENSION	(1 << 12)
#define TOUCHED_PATHS		(1 << 13)

// Project File Keys
PB_EXTERN NSString *PB_ClassesKey;
PB_EXTERN NSString *PB_HeadersKey;
PB_EXTERN NSString *PB_OtherSourcesKey;
PB_EXTERN NSString *PB_OtherResourcesKey;
PB_EXTERN NSString *PB_SupportingFilesKey;
PB_EXTERN NSString *PB_ProjectHeadersKey;
PB_EXTERN NSString *PB_PublicHeadersKey;
PB_EXTERN NSString *PB_PrecompiledHeadersKey;
PB_EXTERN NSString *PB_SubprojectsKey;
PB_EXTERN NSString *PB_InterfacesKey;
PB_EXTERN NSString *PB_ImagesKey;
PB_EXTERN NSString *PB_LocalizableFilesKey;
PB_EXTERN NSString *PB_FrameworksKey;
PB_EXTERN NSString *PB_OtherLibsKey;
PB_EXTERN NSString *PB_NonProjectFilesKey;

@interface NSArray (Extra)
- (id) deepMutableNotifyingCopy;	// uses MutableNotifyingArrays
- (id) deepNSMutableCopy; 		// uses NSMutableArrays
@end

@interface NSDictionary (Extra)
- (id) deepMutableNotifyingCopy;	// uses MutableNotifyingDictionarys
- (id) deepNSMutableCopy; 		// uses NSMutableDictionarys
@end
