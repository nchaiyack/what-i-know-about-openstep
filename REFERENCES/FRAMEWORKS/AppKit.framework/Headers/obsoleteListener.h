/*
	obsoleteListener.h
	Application Kit
	Copyright (c) 1994-1996, NeXT Software, Inc.
	All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <mach/port.h>
#import <mach/message.h>
#import <AppKit/NSApplication.h>
#import <AppKit/NSPasteboard.h>
#import <AppKit/AppKitDefines.h>

/*
 * Names of workspace ports for requests and for acknowledging machlaunch
 * from the Workspace Manager.
 */

APPKIT_EXTERN NSString *NXWorkspaceName;
APPKIT_EXTERN NSString *NXWorkspaceReplyName;


enum {
    NSSelectorPMessage			= 35555,
    NSSelectorFMessage			= 35556,
    NSResponseMessage			= 35557,
    NSAcknowledge			= 35558
};

enum {
    NSIncorrectMessage			= -20000,
    NSMaxRemoteMethodParameters		= 20,
    NSDefaultSendAndReceiveTimeout	= 10000,
    NSMaxMessage			= (2048-sizeof(msg_header_t) - sizeof(msg_type_t)-sizeof(int) - sizeof(msg_type_t)-8)
};

typedef struct _NXMessage {	/* a message via mach */
    msg_header_t header;	/* every message has one of these */
    msg_type_t sequenceType;	/* sequence number type */
    int sequence;		/* sequence number */
    msg_type_t actionType;	/* selector string */
    char action[NSMaxMessage];
} NXMessage;

typedef struct _NXResponse {	/* a message via mach */
    msg_header_t header;	/* every message has one of these */
    msg_type_t sequenceType;	/* sequence number type */
    int sequence;		/* sequence number */
} NXResponse;

typedef struct _NXAcknowledge {	/* a message via mach */
    msg_header_t header;	/* every message has one of these */
    msg_type_t sequenceType;	/* sequence number type */
    int sequence;		/* sequence number */
    msg_type_t errorType;	/* error number type */
    int error;			/* error number, 0 is ok */
} NXAcknowledge;

typedef struct _NXRemoteMethod {/* defines method understood by Listener */
    SEL key;			/* obj-c selector */
    char *types;		/* defines types of parameters */
} NXRemoteMethod;

typedef union {			/* used to pass parameters to method */
    int ival;
    double dval;
    port_t pval;
    struct _bval {
        char *p;
        int len;
    } bval;
} NXParamValue;

APPKIT_EXTERN char *NXCopyInputData(int parameter);
APPKIT_EXTERN char *NXCopyOutputData(int parameter);
APPKIT_EXTERN port_t NXPortFromName(NSString * portName, NSString * hostName);
APPKIT_EXTERN port_t NXPortNameLookup(NSString * portName, NSString * hostName);
APPKIT_EXTERN NXRemoteMethod *NXRemoteMethodFromSel(SEL s, NXRemoteMethod *pt);
APPKIT_EXTERN id NXResponsibleDelegate(id self, SEL selector);

/*
 * permissible values of posType for setPosition:posType:andSelect:
 * and postion:posType:
 */
 
typedef enum _NSMsgPositionType {
    NSMsgTextPosition			= 0,
    NSMsgRegularExpressionPosition	= 1,
    NSMsgLineNumberPosition		= 2,
    NSMsgCharacterNumberPosition	= 3,
    NSMsgApplicationPosition		= 4
} NSMsgPositionType;


/* Old 3.X thresholds to be passed to setPriority: */
enum {
    NSBaseThreshhold			= 1,
    NSRunModalThreshold			= 5,
    NSModalResponseThreshold		= 10
};


@interface Listener : NSObject <NSCoding>
{
    NSString *portName;
    port_t              _listenPort;
    port_t              _signaturePort;
    id                  _delegate;
    int                 _timeout;
    int                 _priority;
    id                  _delegate2;
    id                  _requestDelegate;
    NSPort             *_listenPortObj;
}
 
+ run;

- (int)timeout;
- (void)setTimeout:(int)ms;
- (int)priority;
- (void)setPriority:(int)level;
- (port_t)listenPort;
- (port_t)signaturePort;
- (id)delegate;
- (void)setDelegate:(id)anObject;
- (void)setServicesDelegate:(id)anObject;
- (id)servicesDelegate;
- (NSString *)portName;
- (int)checkInAs:(NSString *)name;
- (int)usePrivatePort;
- (int)checkOut;
- (void)addPort;
- (void)removePort;
- (NXRemoteMethod *)remoteMethodFor:(SEL)aSelector;
- (void)messageReceived:(NXMessage *)msg;


- (int)msgQuit:(int *)flag;
- (int)msgCalc:(int *)flag;
- (int)msgDirectory:(char * const *)fullPath ok:(int *)flag;
- (int)msgVersion:(char * const *)aString ok:(int *)flag;
- (int)msgFile:(char * const *)fullPath ok:(int *)flag;
- (int)msgPrint:(const char *)fullPath ok:(int *)flag;
- (int)msgSelection:(char * const *)bytes length:(int *)len asType:(const char *)aType ok:(int *)flag;
- (int)msgSetPosition:(const char *)aString posType:(NSMsgPositionType)aPosition andSelect:(int)sflag ok:(int *)flag;
- (int)msgPosition:(char * const *)aString posType:(int *)anInt ok:(int *)flag;
- (int)msgCopyAsType:(const char *)aType ok:(int *)flag;
- (int)msgCutAsType:(const char *)aType ok:(int *)flag;
- (int)msgPaste:(int *)flag;
- (int)performRemoteMethod:(NXRemoteMethod *)method paramList:(NXParamValue *)params;

@end

@class Speaker;

@interface NSApplication(NSSpeakerListener)
- (port_t)replyPort;
- (void)setAppListener:(Listener *)aListener;
- (Listener *)appListener;
- (void)setAppSpeaker:(Speaker *)aSpeaker;
- (Speaker *)appSpeaker;
- (NSString *)appListenerPortName;
@end

APPKIT_PRIVATE_EXTERN NSString *appListenerPortName();
// Same as [NSApp appListenerPortName] but can be used before there is an NSApplication instance.
