/*
 * Copyright (c) 1992 NeXT Computer, Inc.
 *
 * Byte ordering conversion (for m68k).
 *
 * HISTORY
 *
 * 8 October 1992 David E. Bohman at NeXT
 *	Converted to NXxxx versions.  Condensed history.
 *
 * 28 August 1992 Bruce Martin @NeXT
 *	Created.
 */

static __inline__
unsigned short
NXSwapShort(
    unsigned short	inv
)
{
    union sconv {
	unsigned short	us;
	unsigned char	uc[2];
    } *inp, outv;
    
    inp = (union sconv *)&inv;
    
    outv.uc[0] = inp->uc[1];
    outv.uc[1] = inp->uc[0];
    
    return (outv.us);
}

static __inline__
unsigned int
NXSwapInt(
    unsigned int	inv
)
{
    union iconv {
	unsigned int	ui;
	unsigned char	uc[4];
    } *inp, outv;
    
    inp = (union iconv *)&inv;
    
    outv.uc[0] = inp->uc[3];
    outv.uc[1] = inp->uc[2];
    outv.uc[2] = inp->uc[1];
    outv.uc[3] = inp->uc[0];
    
    return (outv.ui);
}

static __inline__
unsigned long
NXSwapLong(
    unsigned long	inv
)
{
    union lconv {
	unsigned long	ul;
	unsigned char	uc[4];
    } *inp, outv;
    
    inp = (union lconv *)&inv;
    
    outv.uc[0] = inp->uc[3];
    outv.uc[1] = inp->uc[2];
    outv.uc[2] = inp->uc[1];
    outv.uc[3] = inp->uc[0];
    
    return (outv.ul);
}

static __inline__
unsigned long long
NXSwapLongLong(
    unsigned long long	inv
)
{
    union llconv {
	unsigned long long	ull;
	unsigned char		uc[8];
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

static __inline__ NXSwappedFloat
NXConvertHostFloatToSwapped(float x)
{
    union fconv {
	float number;
	NXSwappedFloat sf;
    };
    return ((union fconv *)&x)->sf;
}

static __inline__ float
NXConvertSwappedFloatToHost(NXSwappedFloat x)
{
    union fconv {
	float number;
	NXSwappedFloat sf;
    };
    return ((union fconv *)&x)->number;
}

static __inline__ NXSwappedDouble
NXConvertHostDoubleToSwapped(double x)
{
    union dconv {
	double number;
	NXSwappedDouble sd;
    };
    return ((union dconv *)&x)->sd;
}

static __inline__ double
NXConvertSwappedDoubleToHost(NXSwappedDouble x)
{
    union dconv {
	double number;
	NXSwappedDouble sd;
    };
    return ((union dconv *)&x)->number;
}

static __inline__ NXSwappedFloat
NXSwapFloat(NXSwappedFloat x)
{
    return NXSwapLong(x);
}

static __inline__ NXSwappedDouble
NXSwapDouble(NXSwappedDouble x)
{
    return NXSwapLongLong(x);
}
