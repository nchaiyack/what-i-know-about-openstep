/*	@(#)dma.h	1.0	08/12/87	(c) 1987 NeXT	*/

/* 
 **********************************************************************
 * HISTORY
 *
 * 26-Sep-89  John Seamons (jks) at NeXT
 *	Made dd_csr in struct dma_dev an int (and changed the corresponding
 *	register #defines) because this register responds as a 32-bit device
 *	and therefore needs to be accessed this way to work on the 68040.
 *
 * 12-Apr-88  John Seamons (jks) at NeXT
 *	Changes to support DMA chip 313.
 *
 * 12-Aug-87  Mike DeMoney (mike) at NeXT
 *	Created.
 *
 **********************************************************************
 */ 

/*
 * dma.h -- description of NeXT dma structures
 */

#ifndef	_M68K_DEV_DMA_
#define	_M68K_DEV_DMA_

#define	MAX_DMA_LEN	(64*1024)	/* max DMA transfer size */
#define	MAX_CHAIN_LEN	(8*1024)	/* max DMA transfer size per chain */

#define	DMA_BEGINALIGNMENT	16	/* initial buffer must be on quad 
					 * longword */
#define	DMA_ENDALIGNMENT	16	/* DMA must end on quad longword */
#define	DMA_LONGALIGNMENT	4	/* sound and enet tx channels support 
					 * long alignment */

#define	DMA_BEGINALIGN(type, addr)	\
	((type)(((unsigned)(addr)+DMA_BEGINALIGNMENT-1) \
		&~(DMA_BEGINALIGNMENT-1)))

#define	DMA_ENDALIGN(type, addr)	\
	((type)(((unsigned)(addr)+DMA_ENDALIGNMENT-1) \
		&~(DMA_ENDALIGNMENT-1)))
#define	DMA_BEGINALIGNED(addr)	(((unsigned)(addr)&(DMA_BEGINALIGNMENT-1))==0)
#define	DMA_ENDALIGNED(addr)	(((unsigned)(addr)&(DMA_ENDALIGNMENT-1))==0)
#define	DMA_LONGALIGNED(addr)	(((unsigned)(addr)&(DMA_LONGALIGNMENT-1))==0)


#endif	_M68K_DEV_DMA_

