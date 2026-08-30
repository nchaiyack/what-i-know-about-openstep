/* 	Copyright (c) 1993 NeXT Computer, Inc.  All rights reserved. 
 *
 * svgaPSExtension.h - Functions required for SVGA Window Server.
 *
 *
 * HISTORY
 * 04 Aug 93	Scott Forstall
 *      Created. 
 */


typedef struct {

    // Select which 64K segment we intend to read from
    void (*setReadSegment)(unsigned char num);
    
    // Select which 64K segment we intend to write to.
    void (*setWriteSegment)(unsigned char num);
    
    // Select which of 4 bit planes to read from in planar
    // modes - only one plane can be active at a time.
    void (*setReadPlane)(unsigned char num);
    
    // Select one of 4 bit planes to write to in planar modes.
    // Although more than one plane can be active at a time,
    // this routine only allows access to 1 plane at a time.
    void (*setWritePlane)(unsigned char num);
    
} IOSVGAFunctions;

/*
 * Initialize the setFunctions structure with the function pointers.
 * Return 0 for success, anything else for failure.
 */
int IOSetSVGAFunctions(IOSVGAFunctions *functs);

