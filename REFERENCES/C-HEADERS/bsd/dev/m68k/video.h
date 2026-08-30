/*
 *	Copyright (C) 1989, NeXT, Inc.
 *
 * HISTORY
 *
 * 01-Mar-90  Ted Cohn (tcohn) at NeXT
 *	Added DKIOCREGISTER ioctl to register the MegaPixel with ev driver.
 *
 * 28-Feb-90  John Seamons (jks) at NeXT
 *	Added STOP_ANIM flag.
 *
 * 12-Aug-87  John Seamons (jks) at NeXT
 *	Created.
 */

#ifndef	_M68K_DEV_VIDEO_PRIV_
#define	_M68K_DEV_VIDEO_PRIV_

#import <sys/ioctl.h>

/* 2 bit display parameters */
#define PIXPERXFER	16		/* pixel alignment of a transfer */
#define PPXMASK		((unsigned int)0x0000000f)
#define LONGSIZE	32		/* pixel width of saved rect */

#define	NPPB		4		/* Pixels per byte */
#define	VIDEO_W		1120		/* Visible pixels per scanline */
#define	VIDEO_MW	((dma_chip == 313)? 1152 : 1120)	/* Actual pixels per scanline */
#define	VIDEO_H		832		/* Visible scanlines */
#define	VIDEO_MH	((dma_chip == 313)? 910 : 936)
#define	VIDEO_NBPL	(VIDEO_MW >> 2)
#define	WHITE		0x00000000
#define	LT_GRAY		0x55555555
#define	DK_GRAY		0xaaaaaaaa
#define	BLACK		0xffffffff
#define	RETRACE_START	0x00
#define	RETRACE_LIMIT	0xea		/* limit reg value to int @ retrace */
#define	RETRACE_MAX	0xfc
#define	CONTINUE_ANIM	0x12345678	/* continue animation (if any) */
#define	STOP_ANIM	0x87654321

/*
 *	Size of video memory area to be mapped.  The lower limit is the
 *	minimum size that can be transparently translated, which is 16 Mbytes
 *	on the 68030 and 68040.
 */
#define VID_MAPPED_SIZE		0x01000000

/* 16 bit color display parameters */
#define C16_VIDEO_1120x832_W	1120
#define C16_VIDEO_1120x832_MW	((dma_chip == 313)? 1152 : 1120)
#define C16_VIDEO_1120x832_H	832
#define C16_VIDEO_1120x832_MH	((dma_chip == 313)? 910 : 936)
#define C16_VIDEO_832x624_W	832
#define C16_VIDEO_832x624_MW	832
#define C16_VIDEO_832x624_H	624
#define C16_VIDEO_832x624_MH	1260
#define C16_VIDEO_NBPP		2	/* 2 bytes/pixel */
#define C16_VID_SIZE		0x00200000	 /* 2 Mbytes of VRAM */
#define C16_VID_MAPPED_SIZE	0x01000000

#define C16_NPPW		2	/* 2 pixels per word. */
#define	C16_WHITE		0xFFF0FFF0
#define	C16_LT_GRAY		0xAAA0AAA0
#define	C16_DK_GRAY		0x55505550
#define	C16_BLACK		0

/* Bits for the write-only P_C16_CMD_REG register (Warp9C only). */
#define C16_CMD_CLRINTR		1
#define C16_CMD_INTRENA		2
#define C16_CMD_UNBLANK		4
#define C16_CMD_FASTWRITE	8
#define C16_CMD_DFLT		C16_CMD_UNBLANK

#define	DKIOCGADDR	_IOWR('v', 0, int)	/* get address of video mem */
#define	DKIOCSMWF	_IOWR('v', 1, struct mwf) /* set mwf bounds */
#define	DKIOCBRIGHT	_IOWR('v', 2, int)	/* get/set brightness */
#define	DKIOCDISABLE	_IO('v', 3)		/* disable translation */
#define	DKIOCGNVRAM	_IOR('v', 4, struct nvram_info) /* get NVRAM */
#define	DKIOCSNVRAM	_IOW('v', 4, struct nvram_info) /* set NVRAM */
#define	DKIOCREGISTER	_IO('v', 5)			/* register screen */
#define	DKIOCGFBINFO	_IO('v', 6) /* Get info on built-in frame buffer */
#define	DKIOCGALARM	_IOR('v', 7, struct alarm)	/* get RTC alarm */
#define	DKIOCSALARM	_IOW('v', 7, struct alarm)	/* set RTC alarm */


#ifndef	__ASSEMBLER__

struct alarm {
	int	alarm_enabled;
	int	alarm_time;
};

#if !defined(__Bounds__) && !defined(BINTREE_H)
#define __Bounds__
typedef struct { short minx, maxx, miny, maxy; } Bounds;
#endif
#if !defined(__Point__) && !defined(BINTREE_H)
#define __Point__
typedef struct { short x, y; } Point;
#endif

struct mp12Cursor {
    unsigned int image[4][16];
    unsigned int mask[4][16];
    unsigned int save[16];
};

struct mp18Cursor {
    unsigned char image[4][256];
    unsigned char mask[4][256];
    unsigned char save[256];
};

struct mp34Cursor {
    unsigned short image[4][256];
    unsigned short save[256];
};

struct mp38Cursor {
    unsigned int image[4][256];
    unsigned int save[256];
};

typedef struct {
    int frame;
    int cursorSema;
    char cursorShow;
    char cursorObscured;
    char shieldFlag;
    char shielded;
    Bounds saveRect;
    Bounds shieldRect;
    Point cursorLoc;
    Bounds cursorRect;
    Bounds oldCursorRect;
    Bounds screenBounds;
    Point hotSpot[4];
    union {
	struct mp12Cursor bw;
	struct mp18Cursor bw8;
	struct mp34Cursor rgb;
	struct mp38Cursor rgb24;
    } cursor;
} vidShmemStruct;

#define VIDSETSEMA() if (msp->cursorSema) return 1; else msp->cursorSema = 1
#define VIDCLEARSEMA() msp->cursorSema = 0
#endif	__ASSEMBLER__

#endif	_M68K_DEV_VIDEO_PRIV_
