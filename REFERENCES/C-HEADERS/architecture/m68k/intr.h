/*	@(#)intr.h	1.0	10/16/91	(c) 1991 NeXT Computer Inc.	*/

/* 
 * HISTORY
 * 16-Oct-91  John Seamons (jks) at NeXT
 *	Split out from cpu.h.
 */
 
#ifndef	_M68K_INTR_
#define	_M68K_INTR_

/*
 * Interrupt structure.
 * BASE and BITS define the origin and length of the bit field in the
 * interrupt status/mask register for the particular interrupt level.
 * The first component of the interrupt device name indicates the bit
 * position in the interrupt status and mask registers; the second is the
 * interrupt level; the third is the bit index relative to the start of the
 * bit field.
 */
#define	I(l,i,b)	(((b) << 8) | ((l) << 4) | (i))
#define	I_INDEX(i)	((i) & 0xf)
#define	I_IPL(i)	(((i) >> 4) & 7)
#define	I_BIT(i)	( 1 << (((i) >> 8) & 0x1f))

#define	I_IPL7_BASE	0
#define	I_IPL7_BITS	2
#define	I_NMI		I(7,0,31)
#define	I_PARITY_ADBNMI	I(7,1,30)

#define	I_IPL6_BASE	2
#define	I_IPL6_BITS	12
#define	I_TIMER		I(6,0,29)
#define	I_ENETX_DMA	I(6,1,28)
#define	I_ENETR_DMA	I(6,2,27)
#define	I_SCSI_DMA	I(6,3,26)
#define	I_OPTICAL_DMA	I(6,4,25)	/* dma 313 chip */
#define	I_PRINTER_DMA	I(6,5,24)
#define	I_SOUND_OUT_DMA	I(6,6,23)
#define	I_SOUND_IN_DMA	I(6,7,22)
#define	I_SCC_DMA	I(6,8,21)	/* dma 313 chip */
#define	I_DSP_DMA	I(6,9,20)

#define	I_IPL5_BASE	14
#define	I_IPL5_BITS	3
#define	I_SCC		I(5,0,17)
#define	I_REMOTE	I(5,1,16)
#define	I_BUS		I(5,2,15)

#define	I_IPL4_BASE	17
#define	I_IPL4_BITS	1
#define	I_DSP		I(4,0,14)

#define	I_IPL3_BASE	18
#define	I_IPL3_BITS	12
#define	I_VIDEO		((dma_chip != 313)? I(3,0,13) : I(3,8,5))
#define	I_C16_VIDEO	I(3,0,13)	/* Warp 9C */
#define	I_OPTICAL	I(3,0,13)	/* dma 313 chip */
#define	I_SCSI		I(3,1,12)
#define	I_PRINTER	I(3,2,11)
#define	I_ENETX		I(3,3,10)
#define	I_ENETR		I(3,4,9)
#define	I_SOUND_OVRUN	I(3,5,8)
#define	I_FLOPPY	I(3,6,7)
#define	I_SPARE_3	I(3,7,6)
#define	I_VIDEO_IN	I(3,8,5)
#define	I_MONITOR	I(3,9,4)
#define	I_KYBD_MOUSE	I(3,10,3)
#define	I_RTC		I(3,11,2)

#define	I_IPL2_BASE	30
#define	I_IPL2_BITS	1
#define	I_SOFTINT1	I(2,0,1)

#define	I_IPL1_BASE	31
#define	I_IPL1_BITS	1
#define	I_SOFTINT0	I(1,0,0)

#endif	_M68K_INTR_
