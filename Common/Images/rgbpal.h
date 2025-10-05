/*===========================================================================
 *
 * File:    Rgbpal.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Tuesday, June 26, 2001
 *
 * Defines the commonly used RGB type palette.
 *
 *=========================================================================*/
#ifndef __RGBPAL_H
#define __RGBPAL_H


#include "Common/dl_err.h"


/* Copy palette options */
#define COPYRGBPAL_CONVERTFROMRAW 1

/* Common conversion definitions */
#define RGBPAL2LONG(pal) ((long)(((long)(byte)((pal).R)) | \
                                 (((long)(byte)((pal).G)) << 8) | \
                                 (((long)(byte)((pal).B)) << 16)))

#define RGBRAWPAL2LONG(pal) ((long)((((long)(byte)((pal).R)) << 2) | \
                                    (((long)(byte)((pal).G)) << 10) | \
                                    (((long)(byte)((pal).B)) << 18)))

#define RGB2LONG(R, G, B) ((long)(((long)(byte)(R)) | \
                                  (((long)(byte)(G)) << 8) | \
                                  (((long)(byte)(B)) << 16)))

#define RGBRAW2LONG(R, G, B) ((long)((((long)(byte)(R)) << 2) | \
                                     (((long)(byte)(G)) << 8) | \
                                     (((long)(byte)(B)) << 16)))


#pragma pack(push, 1)

/* A standard RGB palette structure, color values range from 0 to 255 */
typedef struct {
	union {
		byte R, r, Red;
	};

	union {
		byte G, g, Green;
	};

	union {
		byte B, b, Blue;
	};
} rgbpal_t;

/* Same as a RGB palette except color values range from 0 to 63 */
typedef rgbpal_t rgbpalraw_t;

#pragma pack(pop)


/* Convert a raw RGB palette to a normal one */
void ConvertFromRawRGBPal(rgbpalraw_t *pPalette, const int PaletteSize);
rgbpal_t ConvertRawRGBPal(const rgbpalraw_t &RawPal);
long ConvertRawRGBToLong(const rgbpalraw_t &RawPal);

/* Copy RGB palettes */
void CopyRGBPalette(rgbpal_t *pDestPal,
                    rgbpal_t *pSourcePal,
                    const int PaletteSize,
                    const int Flags = 0);


#endif
