/*===========================================================================
 *
 * File:    Rgbpal.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Tuesday, June 26, 2001
 *
 * Implements common routines for RGB palettes.
 *
 *=========================================================================*/

#include "rgbpal.h"
#include <memory.h>


DEFINE_FILE("RgbPal.cpp");


/*===========================================================================
 *
 * Function - void ConvertFromRawRGBPal (pPalette, PaletteSize);
 *
 * Converts a RAW RGB palette to a regular RGB palette.  A RAW palette
 * has color values from 0 to 63 while a regular palette has colour values
 * from 0 to 255.
 *
 *=========================================================================*/
void ConvertFromRawRGBPal(rgbpalraw_t *pPalette, const int PaletteSize) {
	DEFINE_FUNCTION("ConvertFromRawRGBPal()");
	int Index;
	/* Ensure valid input */
	ASSERT(pPalette != NULL && PaletteSize >= 0);

	/* Multiply all RGB values by 4 */
	for (Index = 0; Index < PaletteSize; Index++) {
		pPalette->Red <<= 2;
		pPalette->Green <<= 2;
		pPalette->Blue <<= 2;
		pPalette++;
	}
}


/*===========================================================================
 *
 * Function - rgbpal_t ConvertRawRGBPal (RawPal);
 *
 * Converts a raw palette entry to a standard one.
 *
 *=========================================================================*/
rgbpal_t ConvertRawRGBPal(const rgbpalraw_t &RawPal) {
	rgbpal_t NewPal = RawPal;
	NewPal.Red <<= 2;
	NewPal.Green <<= 2;
	NewPal.Blue <<= 4;
	return NewPal;
}


/*===========================================================================
 *
 * Function - void CopyRGBPalette (DestPal, SourcePal, PaletteSize, Flags);
 *
 * Copies the given source palette to the destination palette for the given
 * number of palette entries.  The flags parameter indicates a number various
 * optional operations:
 *  COPYRGBPAL_CONVERTFROMRAW   Convert the destination from a RAW
 *                  palette to a normal palette.
 * Flag options can be OR'd for multiple operations.
 *
 *=========================================================================*/
void CopyRGBPalette(rgbpal_t *pDestPal,
                    rgbpal_t *pSourcePal,
                    const int PaletteSize,
                    const int Flags) {
	DEFINE_FUNCTION("CopyRGBPalette()");
	/* Ensure valid input */
	ASSERT(pDestPal != NULL && pSourcePal != NULL && PaletteSize > 0);
	/* Copy the palettes */
	memcpy(pDestPal, pSourcePal, PaletteSize * sizeof(rgbpal_t));

	/* Perform any desired operations */
	if (Flags & COPYRGBPAL_CONVERTFROMRAW) {
		ConvertFromRawRGBPal(pDestPal, PaletteSize);
	}
}
