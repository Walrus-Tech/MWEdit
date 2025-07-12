/*===========================================================================
 *
 * File:    BMPFile.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Monday, March 25, 2002
 *
 * Definition of the CBmpFile class for handling standard input output of
 * BMP type image files.
 *
 *=========================================================================*/
#ifndef __BMPFILE_H
#define __BMPFILE_H


/*===========================================================================
 *
 * Begin Required Include Files
 *
 *=========================================================================*/
#include "common/images/rgbpal.h"
#include "common/file/genfile.h"
/*===========================================================================
 *      End of Required Include Files
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

/* Standard BMP file type */
#define BMPFILE_TYPE_WORD ((ushort)0x4D42)

/* BMP Compression values */
#define BMPCOMPRESS_RGB   ((uint)0)
#define BMPCOMPRESS_RLE8  ((uint)1)
#define BMPCOMPRESS_RLE4  ((uint)2)
#define BMPCOMPRESS_BIT   ((uint)3)

/*===========================================================================
 *      End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

/* Standard bitmap file header */
typedef struct {
	ushort Type;
	uint Size;
	ushort Reserved1;
	ushort Reserved2;
	uint OffsetBits;
} bmpfileheader_t;

/* Standard bitmap info header */
typedef struct {
	uint Size;
	long Width;
	long Height;
	ushort Planes;
	ushort BitCount;
	uint Compression;
	uint SizeImage;
	long XPelsPerMeter;
	long YPelsPerMeter;
	uint ColorUsed;
	uint ColorImportant;
} bmpinfoheader_t;


#pragma pack(pop)
/*===========================================================================
 *      End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CBmpFile Definition
 *
 * Derived from the standard CGenFile class for handling standard BMP type
 * image files.
 *
 *=========================================================================*/
class CBmpFile : virtual public CGenFile {

	/*---------- Begin Private Class Members ----------------------*/
  private:

	bmpfileheader_t m_FileHeader; /* Image header data */
	bmpinfoheader_t m_InfoHeader;

	byte *m_pData;                /* Raw image data (uncompressed) */
	long m_ImageSize;

	rgbpal_t *m_pPalette;         /* Palette data */
	int m_PaletteSize;


	/*---------- Begin Protected Class Methods --------------------*/
  protected:

	/* Helper output functions */
	bool WriteQuadPalette();


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CBmpFile();
	virtual void Destroy();

	/* Compute various sizes/offset */
	uint ComputeSize() const;
	uint ComputeOffsetBits() const;

	/* Saves LBM image data to a standard 256 color BMP file */
	bool ExportLBM(const char *pFilename,
	               const int Width,
	               const int Height,
	               const byte *pImage,
	               const byte *pPalette);

	/* Save the current BMP image to a file */
	bool Save(const char *pFilename);
};

/*===========================================================================
 *      End of Class CBmpFile Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Class CBmpFile Inline Methods
 *
 *=========================================================================*/

/* Compute various file offsets and sizes */
inline uint CBmpFile::ComputeSize() const {
	return ((uint)sizeof(bmpfileheader_t)
	        + (uint)sizeof(bmpinfoheader_t)
	        + (uint)(m_PaletteSize * 4)
	        + (uint)m_InfoHeader.SizeImage);
}

inline uint CBmpFile::ComputeOffsetBits() const {
	return ((uint)sizeof(bmpfileheader_t)
	        + (uint)sizeof(bmpinfoheader_t)
	        + (uint)(m_PaletteSize * 4) );
}

/*===========================================================================
 *      End of Class CBmpFile Inline Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Definitions
 *
 *=========================================================================*/

/* Initialize the header structures with default values */
void InitBMPFileHeader(bmpfileheader_t &FileHeader);
void InitBMPInfoHeader(bmpinfoheader_t &InfoHeader);

/*===========================================================================
 *      End of Function Definitions
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of File Bmpfile.H
 *=========================================================================*/
