/*	NSByteOrder.h
	Definitions for low-level byte swapping
	Copyright 1995-1996, NeXT Software, Inc.  All rights reserved.
*/

#if !defined(STRICT_OPENSTEP)

enum NSByteOrder {
    NS_UnknownByteOrder,
    NS_LittleEndian,
    NS_BigEndian
};

typedef unsigned long NSSwappedFloat;
typedef unsigned long long NSSwappedDouble;

static __inline__ enum NSByteOrder NSHostByteOrder(void) {
    unsigned int _x;
    _x = (NS_BigEndian << 24) | NS_LittleEndian;
    return ((enum NSByteOrder)*((unsigned char *)&_x));
}

/****************	Basic arch-dependent swapping	****************/

#if defined(m68k) || defined(hppa) || defined(sparc) || defined(ppc)

static __inline__ unsigned short NSSwapShort(unsigned short inv) {
    union sconv {
	unsigned short us;
	unsigned char uc[2];
    } *inp, outv;
    inp = (union sconv *)&inv;
    outv.uc[0] = inp->uc[1];
    outv.uc[1] = inp->uc[0];
    return (outv.us);
}

static __inline__ unsigned int NSSwapInt(unsigned int inv) {
    union iconv {
	unsigned int ui;
	unsigned char uc[4];
    } *inp, outv;
    inp = (union iconv *)&inv;
    outv.uc[0] = inp->uc[3];
    outv.uc[1] = inp->uc[2];
    outv.uc[2] = inp->uc[1];
    outv.uc[3] = inp->uc[0];
    return (outv.ui);
}

static __inline__ unsigned long NSSwapLong(unsigned long inv) {
    union lconv {
	unsigned long ul;
	unsigned char uc[4];
    } *inp, outv;
    inp = (union lconv *)&inv;
    outv.uc[0] = inp->uc[3];
    outv.uc[1] = inp->uc[2];
    outv.uc[2] = inp->uc[1];
    outv.uc[3] = inp->uc[0];
    return (outv.ul);
}

static __inline__ unsigned long long NSSwapLongLong(unsigned long long inv) {
    union llconv {
	unsigned long long ull;
	unsigned char uc[8];
    } *inp, outv;
    inp = (union llconv *)&inv;
    outv.uc[0] = inp->uc[7];
    outv.uc[1] = inp->uc[6];
    outv.uc[2] = inp->uc[5];
    outv.uc[3] = inp->uc[4];
    outv.uc[4] = inp->uc[3];
    outv.uc[5] = inp->uc[2];
    outv.uc[6] = inp->uc[1];
    outv.uc[7] = inp->uc[0];
    return (outv.ull);
}

static __inline__ NSSwappedFloat NSConvertHostFloatToSwapped(float x) {
    union fconv {
	float number;
	NSSwappedFloat sf;
    };
    return ((union fconv *)&x)->sf;
}

static __inline__ float NSConvertSwappedFloatToHost(NSSwappedFloat x) {
    union fconv {
	float number;
	NSSwappedFloat sf;
    };
    return ((union fconv *)&x)->number;
}

static __inline__ NSSwappedDouble NSConvertHostDoubleToSwapped(double x) {
    union dconv {
	double number;
	NSSwappedDouble sd;
    };
    return ((union dconv *)&x)->sd;
}

static __inline__ double NSConvertSwappedDoubleToHost(NSSwappedDouble x) {
    union dconv {
	double number;
	NSSwappedDouble sd;
    };
    return ((union dconv *)&x)->number;
}

static __inline__ NSSwappedFloat NSSwapFloat(NSSwappedFloat x) {
    return NSSwapLong(x);
}

static __inline__ NSSwappedDouble NSSwapDouble(NSSwappedDouble x) {
    return NSSwapLongLong(x);
}

#elif defined(i386)

static __inline__ unsigned short NSSwapShort (unsigned short inv) {
    unsigned short outv;
    __asm__ volatile("rorw $8,%0" : "=r" (outv) : "0" (inv));
    return (outv);
}
 
static __inline__ unsigned int NSSwapInt (unsigned int inv) {
    unsigned int outv;
    __asm__ volatile("bswap %0" : "=r" (outv) : "0" (inv));
    return (outv);
}
 
static __inline__ unsigned long NSSwapLong(unsigned long inv) {
    unsigned long outv;
    __asm__ volatile("bswap %0" : "=r" (outv) : "0" (inv));
    return (outv);
}

static __inline__ unsigned long long NSSwapLongLong(unsigned long long inv) {
    union llconv {
	unsigned long long ull;
	unsigned long ul[2];
    } *inp, outv;
    inp = (union llconv *)&inv;
    outv.ul[0] = NSSwapLong(inp->ul[1]);
    outv.ul[1] = NSSwapLong(inp->ul[0]);
    return (outv.ull);
}

static __inline__ NSSwappedFloat NSConvertHostFloatToSwapped(float x) {
    union fconv {
	float number;
	NSSwappedFloat sf;
    };
    return ((union fconv *)&x)->sf;
}

static __inline__ float NSConvertSwappedFloatToHost(NSSwappedFloat x) {
    union fconv {
	float number;
	NSSwappedFloat sf;
    };
    return ((union fconv *)&x)->number;
}

static __inline__ NSSwappedDouble NSConvertHostDoubleToSwapped(double x) {
    union dconv {
	double number;
	NSSwappedDouble sd;
    };
    return ((union dconv *)&x)->sd;
}

static __inline__ double NSConvertSwappedDoubleToHost(NSSwappedDouble x) {
    union dconv {
	double number;
	NSSwappedDouble sd;
    };
    return ((union dconv *)&x)->number;
}

static __inline__ NSSwappedFloat NSSwapFloat(NSSwappedFloat x) {
    return NSSwapLong(x);
}

static __inline__ NSSwappedDouble NSSwapDouble(NSSwappedDouble x) {
    return NSSwapLongLong(x);
}

#else
#error Do not know how to byte order this architecture
#endif

/*************** Swapping to big/little endian ***************/

#if defined(__BIG_ENDIAN__)

static __inline__ unsigned short NSSwapBigShortToHost(unsigned short x) {
    return (x);
}

static __inline__ unsigned int NSSwapBigIntToHost(unsigned int x) {
    return (x);
}

static __inline__ unsigned long NSSwapBigLongToHost(unsigned long x) {
    return (x);
}

static __inline__ unsigned long long NSSwapBigLongLongToHost(unsigned long long x) {
    return (x);
}

static __inline__ double NSSwapBigDoubleToHost(NSSwappedDouble x) {
    return NSConvertSwappedDoubleToHost(x);
}

static __inline__ float NSSwapBigFloatToHost(NSSwappedFloat x) {
    return NSConvertSwappedFloatToHost(x);
}

static __inline__ unsigned short NSSwapHostShortToBig(unsigned short x) {
    return (x);
}

static __inline__ unsigned int NSSwapHostIntToBig(unsigned int x) {
    return (x);
}

static __inline__ unsigned long NSSwapHostLongToBig(unsigned long x) {
    return (x);
}

static __inline__ unsigned long long NSSwapHostLongLongToBig(unsigned long long x) {
    return (x);
}

static __inline__ NSSwappedDouble NSSwapHostDoubleToBig(double x) {
    return NSConvertHostDoubleToSwapped(x);
}

static __inline__ NSSwappedFloat NSSwapHostFloatToBig(float x) {
    return NSConvertHostFloatToSwapped(x);
}

static __inline__ unsigned short NSSwapLittleShortToHost(unsigned short x) {
    return NSSwapShort(x);
}

static __inline__ unsigned int NSSwapLittleIntToHost(unsigned int x) {
    return NSSwapInt(x);
}

static __inline__ unsigned long NSSwapLittleLongToHost(unsigned long x) {
    return NSSwapLong(x);
}

static __inline__ unsigned long long NSSwapLittleLongLongToHost(unsigned long long x) {
    return NSSwapLongLong(x);
}

static __inline__ double NSSwapLittleDoubleToHost(NSSwappedDouble x) {
    return NSConvertSwappedDoubleToHost(NSSwapDouble(x));
}

static __inline__ float NSSwapLittleFloatToHost(NSSwappedFloat x) {
    return NSConvertSwappedFloatToHost(NSSwapFloat(x));
}

static __inline__ unsigned short NSSwapHostShortToLittle(unsigned short x) {
    return NSSwapShort(x);
}

static __inline__ unsigned int NSSwapHostIntToLittle(unsigned int x) {
    return NSSwapInt(x);
}

static __inline__ unsigned long NSSwapHostLongToLittle(unsigned long x) {
    return NSSwapLong(x);
}

static __inline__ unsigned long long NSSwapHostLongLongToLittle(unsigned long long x) {
    return NSSwapLongLong(x);
}

static __inline__ NSSwappedDouble NSSwapHostDoubleToLittle(double x) {
    return NSSwapDouble(NSConvertHostDoubleToSwapped(x));
}

static __inline__ NSSwappedFloat NSSwapHostFloatToLittle(float x) {
    return NSSwapFloat(NSConvertHostFloatToSwapped(x));
}

#elif defined(__LITTLE_ENDIAN__)

static __inline__ unsigned short NSSwapBigShortToHost(unsigned short x) {
    return NSSwapShort(x);
}

static __inline__ unsigned int NSSwapBigIntToHost(unsigned int x) {
    return NSSwapInt(x);
}

static __inline__ unsigned long NSSwapBigLongToHost(unsigned long x) {
    return NSSwapLong(x);
}

static __inline__ unsigned long long NSSwapBigLongLongToHost(unsigned long long x) {
    return NSSwapLongLong(x);
}

static __inline__ double NSSwapBigDoubleToHost(NSSwappedDouble x) {
    return NSConvertSwappedDoubleToHost(NSSwapDouble(x));
}

static __inline__ float NSSwapBigFloatToHost(NSSwappedFloat x) {
    return NSConvertSwappedFloatToHost(NSSwapFloat(x));
}

static __inline__ unsigned short NSSwapHostShortToBig(unsigned short x) {
    return NSSwapShort(x);
}

static __inline__ unsigned int NSSwapHostIntToBig(unsigned int x) {
    return NSSwapInt(x);
}

static __inline__ unsigned long NSSwapHostLongToBig(unsigned long x) {
    return NSSwapLong(x);
}

static __inline__ unsigned long long NSSwapHostLongLongToBig(unsigned long long x) {
    return NSSwapLongLong(x);
}

static __inline__ NSSwappedDouble NSSwapHostDoubleToBig(double x) {
    return NSSwapDouble(NSConvertHostDoubleToSwapped(x));
}

static __inline__ NSSwappedFloat NSSwapHostFloatToBig(float x) {
    return NSSwapFloat(NSConvertHostFloatToSwapped(x));
}

static __inline__ unsigned short NSSwapLittleShortToHost(unsigned short x) {
    return (x);
}

static __inline__ unsigned int NSSwapLittleIntToHost(unsigned int x) {
    return (x);
}

static __inline__ unsigned long NSSwapLittleLongToHost(unsigned long x) {
    return (x);
}

static __inline__ unsigned long long NSSwapLittleLongLongToHost(unsigned long long x) {
    return (x);
}

static __inline__ double NSSwapLittleDoubleToHost(NSSwappedDouble x) {
    return NSConvertSwappedDoubleToHost(x);
}

static __inline__ float NSSwapLittleFloatToHost(NSSwappedFloat x) {
    return NSConvertSwappedFloatToHost(x);
}

static __inline__ unsigned short NSSwapHostShortToLittle(unsigned short x) {
    return (x);
}

static __inline__ unsigned int NSSwapHostIntToLittle(unsigned int x) {
    return (x);
}

static __inline__ unsigned long NSSwapHostLongToLittle(unsigned long x) {
    return (x);
}

static __inline__ unsigned long long NSSwapHostLongLongToLittle(unsigned long long x) {
    return (x);
}

static __inline__ NSSwappedDouble NSSwapHostDoubleToLittle(double x) {
    return NSConvertHostDoubleToSwapped(x);
}

static __inline__ NSSwappedFloat NSSwapHostFloatToLittle(float x) {
    return NSConvertHostFloatToSwapped(x);
}

#else
#error Do not know the endianess of this architecture
#endif

#endif /* !STRICT_OPENSTEP */
