/*
 * Copyright (c) 1992 NeXT Computer, Inc.
 *
 * Natural alignment of shorts and longs (for hppa)
 *
 * HISTORY
 *
 * 2 Sept 1992 Brian Raymor at NeXT
 *      Moved over to architecture.
 * 17 August 1992 Jack Greenfield at NeXT
 *	Created.
 */

__inline__ static unsigned short 
get_align_short(void *ivalue)
{
    unsigned short	ovalue = ((unsigned char *) ivalue)[0];

    ovalue <<= 8 * sizeof(unsigned char);
    return ovalue + ((unsigned char *) ivalue)[1];
}

__inline__ static unsigned short 
put_align_short(unsigned short ivalue, void *ovalue)
{
    unsigned short	*tvalue = &ivalue;

    ((unsigned char *) ovalue)[0] = ((unsigned char *) tvalue)[0];
    ((unsigned char *) ovalue)[1] = ((unsigned char *) tvalue)[1];
    return ivalue;
}

__inline__ static unsigned long 
get_align_long(void *ivalue)
{
    unsigned long	ovalue = get_align_short(ivalue);

    ovalue <<= 8 * sizeof(unsigned short);
    return ovalue + get_align_short(((unsigned char *) ivalue) + sizeof(short));
}

__inline__ static unsigned long 
put_align_long(unsigned long ivalue, void *ovalue)
{
    unsigned long	*tvalue = &ivalue;

    ((unsigned char *) ovalue)[0] = ((unsigned char *) tvalue)[0];
    ((unsigned char *) ovalue)[1] = ((unsigned char *) tvalue)[1];
    ((unsigned char *) ovalue)[2] = ((unsigned char *) tvalue)[2];
    ((unsigned char *) ovalue)[3] = ((unsigned char *) tvalue)[3];
    return ivalue;
}

