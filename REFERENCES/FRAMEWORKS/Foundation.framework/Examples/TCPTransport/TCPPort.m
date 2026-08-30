/* TCPPort.m created by blaine on Wed 03-Apr-1996
   Copyright 1996, NeXT Computer, Inc.
   Blaine Garst
   Marc Majka
 */


#import "TCPPort.h"

#if defined(WIN32)
#import <windows.h>
#import <winsock.h>
#import <winnt-pdo.h>
#else
#import <sys/types.h>
#import <sys/socket.h>
#import <netinet/in.h>
#import <netdb.h>

#define SOCKET int
#define INVALID_SOCKET -1
#define closesocket(x) close(x)

#endif

#if !defined(__svr4__) && !defined(WIN32)
#import <libc.h>
#endif

#define ProtocolNameTCP "tcp"
#define MaxTCPListenQueue 5

static int enableLogging = 0;


/*************** Hashtable stuff *********************/
/*
 * Keep a table of TCPPorts so that if you're sent a port that
 * you already know about, you don't connect, etc. again.
 */
 
static NSHashTable *TCPPorts = NULL;

/* create a fake TCPPort to see if its in the table already */
static TCPPort *lookupSocketPort(unsigned short tcpPort, unsigned long addr, TCPPort *listener) {
    struct { @defs(TCPPort) } shadow;

    shadow.isa = [TCPPort class];
    shadow.internetAddr = addr;
    shadow.tcpPort = tcpPort;
    shadow.listener = listener;
    // [tableLock lock];
    return NSHashGet(TCPPorts, &shadow);
    // [tableLock unlock];
}

/*********** Utilities ********************************/
/*
 * A little function to canonicalize byte order dependent data.
 */
 
static unsigned int sanitize(unsigned int x) {
    return NSSwapBigIntToHost(x);  // no-op on BigEndians
}        

// Two socket utilities: tcpp and addrp are supposed to be inout, but
// experience with bind doesn't seem to indicate that they actually change.
// To wit, INADDR_ANY (0) stays that way...
static BOOL tryBind(int fd, unsigned short *tcpp, unsigned long *addrp) {
    struct sockaddr_in addr;
    int len, retval;

    // Set up my address
    len = sizeof(struct sockaddr_in);
    memset((char *)&addr, 0, len);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = *addrp; // INADDR_ANY;
    addr.sin_port = htons(*tcpp);

    // Give the socket my address and port 
    retval = bind(fd, (struct sockaddr *)&addr, len);
    *addrp = addr.sin_addr.s_addr;
    *tcpp = ntohs(addr.sin_port);
    if (retval < 0) NSLog(@"bind failed");
    return (retval >= 0);
}

// again, the out case doesn't seem to do anything XXX
static BOOL tryConnect(int fd, unsigned short *tcpp, unsigned long *addrp) {
    struct sockaddr_in addr;
    int len, retval;
    extern int errno;

    // Set up address
    len = sizeof(struct sockaddr_in);
    memset((char *)&addr, 0, len);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = *addrp;
    addr.sin_port = htons(*tcpp);

    retval = connect(fd, (struct sockaddr *)&addr, len);
    *addrp = addr.sin_addr.s_addr;
    *tcpp = ntohs(addr.sin_port);
    if (retval != 0) NSLog(@"connect failed, errno %d", errno);
    return (retval == 0);
}

static unsigned short getNumber(int s1) {
    struct sockaddr_in mine;
    int len, ret;

    len = sizeof(struct sockaddr_in);
    ret = getsockname(s1, (struct sockaddr *)&mine, &len);
    if (ret < 0) printf("socket %d has no name!\n", s1);
    return ntohs(mine.sin_port);
}

static SOCKET makeSocket() {
    static struct protoent *proto = NULL;
    SOCKET result;

#if 1
    if (!proto) {
	// Get the TCP protocol number
	proto = getprotobyname(ProtocolNameTCP);
	if (proto == NULL) {
  	    NSLog(@"failed to getproto");
	    return INVALID_SOCKET;
	}
    }
#endif

    // Create a new TCP socket
    result = socket(PF_INET, SOCK_STREAM, 0 /*proto->p_proto*/);
    if (enableLogging) NSLog(@"created socket %u", result);
    if (result == INVALID_SOCKET)
	if (enableLogging) NSLog(@"socket call failed");
    return result;
}

/*******************************************************/
/*********** the real concrete class *******************/
/*******************************************************/

@implementation TCPPort


/*
 * Before anything else, set up the hashtable.  The hashtable
 * doesn't retain its objects because they would never get
 * freed otherwise!
 * Also, watch out for multiple invocations of initialize.  This
 * is a problem for base classes but be careful anyway.
 */
+ (void)initialize {
#if defined(WIN32)
    DWORD vR = MAKEWORD(1, 1);
    WSADATA wsaData;
#endif

    if (TCPPorts) return;
    TCPPorts = NSCreateHashTable(NSNonRetainedObjectHashCallBacks, 0);
    // if not multithreaded already, register for multithreaded notification
    // otherwise just dipatch to the notification XXX
#if WATCH_ALL
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(readAllNotification:) name:NSFileHandleReadCompletionNotification object:nil];
#endif

#if defined(WIN32)
    (void)WSAStartup(vR, &wsaData);
#endif
}

#if WATCH_ALL
+ (void)readAllNotification:(NSNotification *)note {
    NSLog(@"-- read notification for %d, data length %u", [[note object] fileDescriptor], [[[note userInfo] objectForKey:NSFileHandleNotificationDataItem] length]);
}
#endif

+ (void)_toggleLogging {
    enableLogging = enableLogging ? 0 : 1;
}

/* the machPort cover is grody and should do something radical */
- (TCPPort *)initWithMachPort:(int)machPort {
    // raise or be nicer and return nil
    [self dealloc];
    return nil;	
}

/* reimplement hash and isEqual so that we can distinguish
   functional equivalents even if the memory (or socket)
   is different.  Elsewhere we cons up a fake object to see if we can
   find one that already exists so that we can avoid a duplicate.
  */
  
- (unsigned) hash {
    return internetAddr^tcpPort;
}

- (BOOL)isEqual:(TCPPort *)other {
    if (!other || other->isa != isa) return NO;
    return other
	&& other->isa == isa
	&& other->internetAddr == internetAddr
	&& other->tcpPort == tcpPort
	&& other->listener == listener;
    /* note that the socket itself is defined to be not important!! */
}




/*********** initialization stuff **************/

- _acceptorWithFileDescriptor:(int)fd {
#if defined(WIN32)
    NSFileHandle *result = [[NSFileHandle alloc] initWithNativeHandle:fd];
#else
    NSFileHandle *result = [[NSFileHandle alloc] initWithFileDescriptor:fd];
#endif
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(acceptNotification:) name:NSFileHandleConnectionAcceptedNotification object:result];
    return result;
}

- (void)_readerWithFileHandle:result {
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(readNotification:) name:NSFileHandleReadCompletionNotification object:result];
    dataStream = [[DataStream alloc] init];
}

- _readerWithFileDescriptor:(int)fd {
    NSFileHandle *result = [[NSFileHandle alloc] initWithFileDescriptor:fd];
    [self _readerWithFileHandle:result];
    return result;
}

// build up a tcpPort that will listen()
// tcpPort will indeed be the port we listen on
- (TCPPort *)initWithNumber:(unsigned short)p {
    SOCKET fd = makeSocket();
    int retval;

    if (fd == INVALID_SOCKET) {
	[super dealloc];
	return nil;
    }
    internetAddr = INADDR_ANY;
    tcpPort = p;
    if (!tryBind(fd, &tcpPort, &internetAddr)) {
	closesocket(fd);
	[super dealloc];
	return nil;
    }
    if (!p) {
    	// XXX untested
    	tcpPort = getNumber(fd);
    }
    if (internetAddr == INADDR_ANY) {
        NSHost *me = [NSHost currentHost];
	if (me == nil) {
	    closesocket(fd);
	    return nil;
	}
	internetAddr = inet_addr([[me address] cString]);
    }

    // Put the socket in passive mode (accept connections)
    retval = listen(fd, MaxTCPListenQueue);
    if (retval == INVALID_SOCKET) {
	closesocket(fd);
	[super dealloc];
	return nil;
    }

    modes = [NSCountedSet new];
    readWriter = [self _acceptorWithFileDescriptor:fd];
    return self;
}


- (BOOL)_connect {
    int fd = makeSocket();
    unsigned short myPort = tcpPort;
    unsigned long connectAddr = internetAddr;
    unsigned long tmp;
    
    if (fd == INVALID_SOCKET) {
        return NO;
    }
    if (!listener) return NO;
    if (!tryConnect(fd, &myPort, &connectAddr)) {
    	if (enableLogging) NSLog(@"***failed to connect to port %d addr %u", tcpPort, internetAddr);
	closesocket(fd);
	return NO;
    }

    if (enableLogging) NSLog(@"connect()ed to port %d addr %u for fd %d", tcpPort, internetAddr, fd);
    tmp = sanitize(listener->tcpPort);
    if (write(fd, &tmp, 4) != 4) {
	closesocket(fd);
	return NO;
    }
    // address is already sanitized
    if (write(fd, &listener->internetAddr, 4) != 4) {
	closesocket(fd);
	return NO;
    }
    readWriter = [self _readerWithFileDescriptor:fd];
    return YES;
}


//
// creates a connected tcp port suitable for DO (if necessary)
// if one already exists, use it
//
- (TCPPort *)connectToNumber:(unsigned short)p address:(unsigned long)addr {
    TCPPort *sender = lookupSocketPort(p, addr, self);

    if (sender) {
    	[sender retain];
    }
    if (!sender) {
        sender = [isa alloc];
	sender->internetAddr = addr;
	sender->tcpPort = p;
    	sender->listener = [self retain];
	NSHashInsertKnownAbsent(TCPPorts, sender);
	sender->modes = [NSCountedSet new];
    }

    if (!sender->readWriter && ![sender _connect]) {
	[sender release];
	sender = nil;
	return nil;
    }
    return [sender autorelease];
}

- (TCPPort *)connectToNumber:(unsigned short)p host:(NSString *)hostname {
    NSHost *her;
    unsigned long addr;


    // Get the server's address
    // XXX this stuff should be a category on NSHost...
    her = [NSHost hostWithName:hostname];
    if (her == nil) {
        return nil;
    }
    addr = inet_addr([[her address] cString]);

    return [self connectToNumber:p address:addr];
}


//
// Create a tcpPort from an existing listen()ing socket
//

- (TCPPort *)tcpPortWithAcceptedSocket:handle {
    TCPPort *source;
    unsigned long logicalPort;
    unsigned long destAddr;
    int s = [handle fileDescriptor];

    if (enableLogging) NSLog(@"accept()ed socket %d, reading...", s);
    if (read(s, &logicalPort, 4) != 4) {
	if (enableLogging) NSLog(@"didn't read send logicalPort");
	return nil;
    }
    logicalPort = sanitize(logicalPort);
    if (read(s, &destAddr, 4) != 4) {
	if (enableLogging) NSLog(@"didn't read sender's addr");
	return nil;
    }
    source = lookupSocketPort(logicalPort, destAddr, self);
    if (source) {
	if (enableLogging) NSLog(@"found accepted port %d addr %u", logicalPort, destAddr);
    	[source retain];
	if (source->reader) {
	    if (enableLogging) NSLog(@"***got 2nd reader!");
	    [source->reader release];
	}
	source->reader = [handle retain];
	[source _readerWithFileHandle:handle];
	// sync up with any already established connections
	[source->reader readInBackgroundAndNotifyForModes:[modes allObjects]];
    }
    else {
        source = [isa alloc];
	if (enableLogging) NSLog(@"creating accepted port %d addr %u", logicalPort, destAddr);
	source->listener = [self retain];
	source->tcpPort = logicalPort;
	source->internetAddr = destAddr;
	NSHashInsertKnownAbsent(TCPPorts, source);
	source->readWriter = [handle retain];
        source->modes = [NSCountedSet new];
	[source _readerWithFileHandle:handle];
    }
    return [source autorelease];
}

// 
// Create a TCP server on an arbitrary socket
//

- init {
    return [[isa alloc] initWithNumber:0];
}
   
+ (NSPort *)port {
    return [[[self alloc] initWithNumber:0] autorelease];
}

/*****************************************************/
/************ Coding behavior ************************/
/*****************************************************/

/* The good news is that we don't have to do anything!
 * This works because ports are treated very specially by the
 * portcoder - as long as they internally use the
 * {encode/decode}PortObject: methods.  These methods simply
 * stuff the port supplied into the portCoders array of
 * components.  We'll see these objects later when the portCoder
 * asks us to send a message along, or when we feed components
 * into a portCoder when we get a message off the wire.  All I'm
 * trying to say is that portCoder doesn't care how ports are
 * constructed internally.
 */


- (void)encodeWithCoder:(NSCoder *)coder {
if (enableLogging) NSLog(@"encoding port %d addr %d (out %d, in %d)", tcpPort, internetAddr, [readWriter fileDescriptor], [reader fileDescriptor]);
    [super encodeWithCoder:coder];
}

/*****************************************************/
/********* Deallocation behavior *********************/
/*****************************************************/

/* invalidate the port and inform everyone of such a circumstance */
- (void)invalidate {
    id reader2 = reader;
    id writer2 = readWriter;
    NSNotificationCenter *center = [NSNotificationCenter defaultCenter];

    if (invalid) return;
    invalid = 1;
    reader = nil;
    readWriter = nil;
    [connection release]; connection = nil;

    NSHashRemove(TCPPorts, self);
    [listener release]; listener = nil;
    [center removeObserver:self];
    [center postNotificationName:NSPortDidBecomeInvalidNotification object:self];
    // we may be free already, so operate on stack variables !!!
    if (reader2) [center removeObserver:reader2];
    if (writer2) [center removeObserver:writer2];
    [reader2 release];
    [writer2 release];
}

- (void)dealloc {
    [modes release];

    /** partial stuff **/
    [items release];
    [dataItem release];
    [dataStream release];

    [super dealloc];
}

- (BOOL)isValid {
    return !invalid;
}

/********* retain/release/retainCount must all be overridden */
- retain {
   ++refCount;
   return self;
}

/* Dereference is tricky.  Since many people can hold references to
   ports we need a way to inform them of our potential invalidity.
   We do this with a notification.  Unfortunately, this bumps our
   reference count.  So if our reference count goes to zip, we
   form and send a notification, bumping it, it then again drops to
   zero and attempts to call dealloc twice.  Not good.
   Keep an isDying bit to catch the final ref==0 case.
 */
- (void)release {
    if (refCount == 0) {
        // invalidate calls postNotification which retain/releases
        // but its correspondent might retain & autorrelease!
        if (!isDying) {
            isDying = 1;
            [self invalidate];
            if (refCount == 0) {  // don't do this now if retain-autoreleased
                [self dealloc];
            }
        }
        else {	// the autorelease case comes here
            [self dealloc];
        }
    }
    else {
        --refCount;
    }
}

- (unsigned)retainCount {
    return refCount + 1;
}

/****************************************************************/
/******************* general instance behavior ******************/
/****************************************************************/

/********* NSPort overrides ************************************/
/********* needed by all subclassers ***************************/

/* Give something useful. FD and tcpPort are equal contenders */
- (int)machPort {
   return tcpPort;
}

- (void)setDelegate:(id)anId {
   delegate = anId;
}

- (id)delegate {
   return delegate;
}

/*** runLoop interactions ****/

void doBackgroundForConnection(NSConnection *conn, NSString *mode, BOOL add) {
    TCPPort *listener = [conn receivePort];
    TCPPort *sender = [conn sendPort];
    
    if (add) {
    	[listener->modes addObject:mode];
   	[sender->modes addObject:mode];
    }
    else {
	[listener->modes removeObject:mode];
 	[sender->modes removeObject:mode];
    }
    if (enableLogging) NSLog(@"accept()ing on %@ for modes %@", listener, listener->modes);
    [listener->readWriter acceptConnectionInBackgroundAndNotifyForModes:[listener->modes allObjects]];
    
    if (listener != sender) {
	if (enableLogging) NSLog(@"read()ing on %@ for modes %@", sender, sender->modes);
	[sender->readWriter readInBackgroundAndNotifyForModes:[sender->modes allObjects]];
	[sender->reader readInBackgroundAndNotifyForModes:[sender->modes allObjects]];
    }
}

   
- (void)addConnection:(NSConnection *)conn toRunLoop:(NSRunLoop *)runLoop forMode:(NSString *)mode {
    doBackgroundForConnection(conn, mode, 1);
}

- (void)removeConnection:(NSConnection *)conn fromRunLoop:(NSRunLoop *)runLoop forMode:(NSString *)mode {
    doBackgroundForConnection(conn, mode, 0);
}


#define MAGIC_NUMBER 19560610
#define DATA_TYPE 1
#define PORT_TYPE 2

// this method causes portCoder to reserve space in the first data
// component for (surprise) necessary headers.  This avoids a message
// construction copy in many many cases.

- (unsigned)reservedSpaceLength {
    return 16;    // magic, component count, DATA_TYPE, data length
}

// portCoder tells us to send a message over the wire.  We're the
// sendPort so go ahead and use our socket.

- (BOOL) sendBeforeDate:(NSDate *)limitDate components:(NSMutableArray *)components from:(NSPort *)receivePort reserved:(unsigned)rsvd {
    unsigned counter;
    NSData *firstComponent = [components objectAtIndex:0];
    int *header = (int *)[firstComponent bytes];
    int length = [firstComponent length];
    int written;

    if (rsvd != 16) {
        if (enableLogging) NSLog(@"whoops, no header space reserved");
	// XXX be friendlier for more general use
        return NO;
    }
    // prepare magic number
    header[0] = sanitize(MAGIC_NUMBER);
    // prepare number of components, etc.
    header[1] = sanitize([components count]);
    header[2] = sanitize(DATA_TYPE);
    header[3] = sanitize(length-rsvd);
    written = write([readWriter fileDescriptor], [firstComponent bytes], length);
    if (written != length) {
        if (enableLogging) NSLog(@"oops, didn't send the entire first hunk");
        return NO;
    }
    // better schemes might be to collect several of these, use
    // a gathered write, etc.
    for (counter = 1; counter < [components count]; ++counter) {
        id item = [components objectAtIndex:counter];

        if ([item isMemberOfClass:[NSData class]]) {
            int length = [item length];
            int stuff[2] = { sanitize(DATA_TYPE), sanitize(length) };

            written = write([readWriter fileDescriptor], &stuff, sizeof(stuff));
            if (written != sizeof(stuff)) {
                if (enableLogging) NSLog(@"oops, didn't send the type");
                return NO;
            }
            written = write([readWriter fileDescriptor], [item bytes], length);
            if (written != length) {
                if (enableLogging) NSLog(@"oops, didn't send the data");
                return NO;
            }
        }
        else if ([item isMemberOfClass:[TCPPort class]]) {
            TCPPort *sp = item;
            int stuff[3] = { sanitize(PORT_TYPE), sanitize(sp->tcpPort), sp->internetAddr };
	    if (enableLogging) NSLog(@"writing sanitized port %d addr %d", stuff[1], stuff[2]);           
            written = write([readWriter fileDescriptor], &stuff, sizeof(stuff));
            if (written != sizeof(stuff)) {
                if (enableLogging) NSLog(@"oops, didn't send the port stuff");
                return NO;
            }

        }
        else {
            if (enableLogging) NSLog(@"can't send component of type %@", [item class]);
            return NO;
        }
    }
    if (enableLogging) NSLog(@"successfully wrote message on %d", [readWriter fileDescriptor]);
    return YES;
}

enum PartialState {
    READING_HEADER,
    READING_TYPE,
    READING_DATA_LENGTH,
    READING_DATA,
    READING_PORT,
    DISPATCHING,
};

- (void)readNotification:(NSNotification *)note {
    NSData *data = [[note userInfo] objectForKey:NSFileHandleNotificationDataItem];
    if ([data length]) {
	if (enableLogging) NSLog(@"read notification to %@; restarting with %@", self, modes);
        [[note object] readInBackgroundAndNotifyForModes:[modes allObjects]];
    }
    else {
	if (enableLogging) NSLog(@"failed read notification %@", data);
        [self invalidate];
	return;
    }
    [dataStream appendData:[[note userInfo] objectForKey:NSFileHandleNotificationDataItem]];
    for(;;) switch (partialState) {
        case READING_HEADER: {
            int stuff[2];
            if (![dataStream getBytes:&stuff[0] length:sizeof(stuff)]) return;
            if (sanitize(stuff[0]) != MAGIC_NUMBER) {
                if (enableLogging) NSLog(@"**** didn't get magic number");
                [self invalidate];
                return;
            }
            nItems = sanitize(stuff[1]);
            itemCounter = 0;
            if (!items) items = [[NSMutableArray alloc] init];
            partialState = READING_TYPE;
        }
		/* fall through */
	case READING_TYPE: {
            if (![dataStream getBytes:&itemType length:sizeof(itemType)]) return;
            itemType = sanitize(itemType);
            if (itemType == DATA_TYPE)
                partialState = READING_DATA_LENGTH;
            else if (itemType == PORT_TYPE)
                partialState = READING_PORT;
            else {
                if (enableLogging) NSLog(@"**bad type %u", itemType);
                [self invalidate];
                return;
            }
            break;
        }

	case READING_DATA_LENGTH: {
            if (![dataStream getBytes:&dataLength length:sizeof(dataLength)]) return;
            dataLength = sanitize(dataLength);
            if (dataLength > 64*1024*1024) {
                if (enableLogging) NSLog(@"**huge data item (%u bytes) error");
                [self invalidate];
                return;
            }
            dataItem = [[NSMutableData alloc] init];
            partialState = READING_DATA;
            break;
        }

	case READING_DATA: {
            unsigned int available = [dataStream length];
            if (!available) return;
            if (available > dataLength)
                available = dataLength;
            [dataStream fillData:dataItem length:available];
            dataLength -= available;
            if (dataLength == 0) {
                [items addObject:dataItem];
                [dataItem release];
		dataItem = nil;
                ++itemCounter;
                if (itemCounter == nItems)
                    partialState = DISPATCHING;
                else
                    partialState = READING_TYPE;
            }
            break;
        }

	case READING_PORT: {
            int stuff[2];
            TCPPort *sp;

            if (![dataStream getBytes:stuff length:sizeof(stuff)]) return;
            if (enableLogging) NSLog(@"got sanitized port %d addr %u", sanitize(stuff[0]), stuff[1]);
            sp = [listener connectToNumber:sanitize(stuff[0]) address:stuff[1]];
            if (!sp) {
                if (enableLogging) NSLog(@"*** didn't get port %d addr %u", sanitize(stuff[0]), stuff[1]);
                [self invalidate];
                return;
            }
            [items addObject:sp];
            ++itemCounter;
            if (itemCounter == nItems)
                partialState = DISPATCHING;
            else
                partialState = READING_TYPE;
            break;
        }

	case DISPATCHING: {
            NSPortCoder *pc = [NSPortCoder portCoderWithReceivePort:listener sendPort:self components:items];

	    if (enableLogging) NSLog(@"dispatching %@!", pc);
            [pc dispatch];
            [items release];
            items = nil;
            partialState = READING_HEADER;
            if (connection) {
                [connection release];
                connection = nil;
            }
            break;
        }
	
	default:
	    NSLog(@"bad case %u", partialState);
	    return;
    }
}

- (void)acceptNotification:(NSNotification *)note {
    NSFileHandle *socket = [[note userInfo] objectForKey:NSFileHandleNotificationFileHandleItem];
    TCPPort *sp;

    if (!socket) {
    	if (enableLogging) NSLog(@"** no socket in notification info %@", [note userInfo]);
    	[self invalidate];
    	return;
    }
    else {
        [readWriter acceptConnectionInBackgroundAndNotifyForModes:[modes allObjects]];
	if (enableLogging) NSLog(@"got socket %d from background, accepting for modes %@", [socket fileDescriptor], modes);
    }
    sp = [self tcpPortWithAcceptedSocket:socket];
    if (!sp) {
        if (enableLogging) NSLog(@"didn't set up socket port");
        return;
    }
    connection = [[NSConnection alloc] initWithReceivePort:self sendPort:sp];
}

- (NSString *)description {
    return [NSString stringWithFormat:@"<TCPPort %u, addr %u, reader %d, readWriter %d>", tcpPort, internetAddr, [reader fileDescriptor], [readWriter fileDescriptor]];
}
@end


