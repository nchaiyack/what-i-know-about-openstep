#import <Foundation/NSException.h>
/*
 * Exception names.  These have to be defines instead of extern NSString *,
 * due to NEXTIME being delivered as an optional package.  (Otherwise those
 * externs might never be resolved!)
 */
#define NTExceptionCorruptFile		@"NTExceptionCorruptFile"
#define NTExceptionCorruptData		@"NTExceptionCorruptData"
#define NTExceptionInvalidDataReference	@"NTExceptionInvalidDataReference"
#define NTExceptionFileWriteError	@"NTExceptionFileWriteError"
#define NTExceptionInvalidDataOperation	@"NTExceptionInvalidDataOperation"
#define NTExceptionFileCreateError	@"NTExceptionFileCreateError"
#define NTExceptionInvalidMovie		@"NTExceptionInvalidMovie"
#define NTExceptionInvalidMedia		@"NTExceptionInvalidMedia"
#define NTExceptionInternalError	@"NTExceptionInternalError"
#define NTExceptionDescriptorError	@"NTExceptionDescriptorError"
#define NTExceptionCallerError		@"NTExceptionCallerError"
#define NTExceptionBadImageDescription	@"NTExceptionBadImageDescription"
