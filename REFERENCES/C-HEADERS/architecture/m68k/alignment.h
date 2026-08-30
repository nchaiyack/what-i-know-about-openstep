/*
 * Copyright (c) 1992 NeXT Computer, Inc.
 *
 * Natural alignment of shorts and longs (for m68k)
 *
 * HISTORY
 *
 * 2 Sept 1992 Brian Raymor at NeXT
 *      Moved over to architecture.
 * 18 August 1992 Jack Greenfield at NeXT
 *	Created.
 */
 
/*
 * NOP
 */
__inline__ static unsigned short
get_align_short(void *ivalue)
{
    return *((unsigned short *) ivalue);
}

__inline__ static unsigned short 
put_align_short(unsigned short ivalue, void *ovalue)
{
    return *((unsigned short *) ovalue) = ivalue;
}

/*
 * NOP
 */
__inline__ static unsigned long
get_align_long(void *ivalue)
{
    return *((unsigned long *) ivalue);
}

__inline__ static unsigned long 
put_align_long(unsigned long ivalue, void *ovalue)
{
    return *((unsigned long *) ovalue) = ivalue;
}
