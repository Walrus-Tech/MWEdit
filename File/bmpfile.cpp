/*===========================================================================
 *
 * File:    Bmpfile.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Monday, March 25, 2002
 *
 * Implements the CBmpFile class for handling standard BMP image files.
 *
 *=========================================================================*/

#include "bmpfile.h"


DEFINE_FILE("bmpfile.cpp");


/*===========================================================================
 *
 * Class CBmpFile Constructor
 *
 *=========================================================================*/
CBmpFile::CBmpFile() {
	//DEFINE_FUNCTION("CBmpFile::CBmpFile()");
	/* Initialize the BMP headers */
	InitBMPInfoHeader(m_InfoHeader);
	InitBMPFileHeader(m_FileHeader);
	m_pData = NULL;
	m_ImageSize = 0;
	m_pPalette = NULL;
	m_PaletteSize = 0;
}


/*===========================================================================
 *
 * Class CBmpFile Method - void Destroy (void);
 *
 * Delete the contents of the BMP file.
 *
 *=========================================================================*/
void CBmpFile::Destroy() {
	DEFINE_FUNCTION("CBmpFile::Destroy()");
	/* Clear the BMP headers */
	InitBMPInfoHeader(m_InfoHeader);
	InitBMPFileHeader(m_FileHeader);
	/* Unallocate any allocated pointer arrays */
	DestroyArrayPointer(m_pData);
	DestroyArrayPointer(m_pPalette);
	m_ImageSize = 0;
	m_PaletteSize = 0;
	/* Chain to the base class method */
	CGenFile::Destroy();
}


/*===========================================================================
 *
 * Class CBmpFile Method - bool ExportLBM (pFilename, Width, Height,
 *                        pImage,    pPalette);
 *
 * Attempts to save the input LBM type image to a BMP file.  Returns FALSE
 * on any error.  The input image data is assumed to be an array of size
 * Width*Height representing the color index in the palette.  The palette
 * data is assumed to be a regular RGB triplet array of 256 colors (768 bytes).
 *
 *=========================================================================*/
bool CBmpFile::ExportLBM(const char *pFilename,
                         const int Width,
                         const int Height,
                         const byte *pImageData,
                         const byte *pPalette) {
	DEFINE_FUNCTION("CBmpFile::ExportLBM()");
	bool Result;
	/* Ensure valid input */
	ASSERT(pImageData != NULL && pPalette != NULL);

	/* Delete the current BMP data, and initialize members */
	Destroy();
	m_pData = (byte *)pImageData;
	m_ImageSize = (long)Width * (long)Height;
	m_pPalette = (rgbpal_t *)pPalette;
	m_PaletteSize = 256;

	/* Initialize the file headers */
	m_InfoHeader.Height = Height;
	m_InfoHeader.Width = Width;
	m_InfoHeader.SizeImage = (uint)m_ImageSize;
	m_InfoHeader.BitCount = 8;
	m_FileHeader.Size = ComputeSize();
	m_FileHeader.OffsetBits = ComputeOffsetBits();

	/* Attempt to save the BMP file */
	Result = Save(pFilename);
	/* Reset the image data */
	m_pData = NULL;
	m_pPalette = NULL;
	return Result;
}


/*===========================================================================
 *
 * Class CBmpFile Method - bool Save (pFilename);
 *
 * Attempt to save the current BMP image to the given filename.  Returns
 * FALSE on any error.
 *
 *=========================================================================*/
bool CBmpFile::Save(const char *pFilename) {
	DEFINE_FUNCTION("CBmpFile::Save()");
	bool Result;
	/* Ensure valid object state */
	ASSERT(m_pData != NULL && m_pPalette != NULL);
	ASSERT(m_ImageSize >= (long)UINT_MAX);
	/* Attempt to open and output file */
	Result = Open(pFilename, "wb");

	if (Result) {
		Result = Write((char *)&m_FileHeader, sizeof(bmpfileheader_t));
	}

	if (Result) {
		Result = Write((char *)&m_InfoHeader, sizeof(bmpinfoheader_t));
	}

	if (Result) {
		Result = WriteQuadPalette();
	}

	if (Result) {
		Result = Write((char *)m_pData, (size_t)m_ImageSize);
	}

	Close();
	return Result;
}


/*===========================================================================
 *
 * Class CBmpFile Method - bool WriteQuadPalette (void);
 *
 * Protected helper class method to output the current RGB palette to
 * the current position in the BMP file.  BMP file usually output a quad
 * RGBA palette with an alpha component in addition to the standard 3
 * colors.  BMP palettes are also backwards to the usual with the format:
 *
 *          Blue Green Red Alpha
 *
 * Palette entries should be byte values ranging from 0 to 255.
 *
 *=========================================================================*/
bool CBmpFile::WriteQuadPalette() {
	//DEFINE_FUNCTION("CBmpFile::WriteQuadPalette()");
	int LoopCounter;
	bool Result;
	rgbpal_t *pPal = m_pPalette;

	/* Output each entry in the palette */
	for (LoopCounter = 0; LoopCounter < m_PaletteSize; LoopCounter++) {
		Result = WriteChar(pPal->B);
		Result &= WriteChar(pPal->G);
		Result &= WriteChar(pPal->R);
		Result &= WriteChar((byte)0);
		pPal++;

		if (!Result) {
			return FALSE;
		}
	}

	return TRUE;
}


/*===========================================================================
 *
 * Function - void InitBMPFileHeader (FileHeader);
 *
 * Initializes the given BMP file header with the default values.
 *
 *=========================================================================*/
void InitBMPFileHeader(bmpfileheader_t &FileHeader) {
	FileHeader.Type = BMPFILE_TYPE_WORD;
	FileHeader.OffsetBits = 0;
	FileHeader.Size = 0;
	FileHeader.Reserved1 = 0;
	FileHeader.Reserved2 = 0;
}


/*===========================================================================
 *
 * Function - void InitBMPInfoHeader (InfoHeader);
 *
 * Initializes the given BMP info header with the default values.
 *
 *=========================================================================*/
void InitBMPInfoHeader(bmpinfoheader_t &InfoHeader) {
	InfoHeader.Size = sizeof(bmpinfoheader_t);
	InfoHeader.SizeImage = 0;
	InfoHeader.Height = 0;
	InfoHeader.Width = 0;
	InfoHeader.XPelsPerMeter = 6000;
	InfoHeader.YPelsPerMeter = 6000;

	/* Use all colors in BMP */
	InfoHeader.ColorImportant = 0;
	InfoHeader.ColorUsed = 0;

	/* Standard RGB uncompressed */
	InfoHeader.Compression = BMPCOMPRESS_RGB;
	InfoHeader.BitCount = 24;
	InfoHeader.Planes = 1;
}
