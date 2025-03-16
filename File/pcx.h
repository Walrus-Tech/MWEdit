/*===========================================================================
 *
 * File:    Pcx.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Tuesday, June 26, 2001
 *
 * Implements the CPcxFile class for handling simple PCX image files.
 *
 *=========================================================================*/
#ifndef __PCX_H
#define __PCX_H


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

/* PCX specific error codes */
#define PCXERR_BIGIMAGE  2001
#define PCXERR_IMAGESIZE 2002

/* Compression constant */
#define PCX_RLE_VALUE 192

/*===========================================================================
 *      End of Definitions
 *=========================================================================*/


/*=========================================================================
 *
 * Begin Type Definitions
 *
 *=======================================================================*/
#pragma pack(push, 1)

/* Defines the header data structure for a PCX file */
typedef struct {
	char Manufacturer;
	char Version;
	char Encoding;
	char BitsPerPixel;
	short X;
	short Y;
	short Width;
	short Height;
	short HorzResolution;
	short VertResolution;
	char EGAPalette[48];
	char Reserved;
	char NumColorPlanes;
	short BytesPerLine;
	short PaletteType;
	char Padding[58];      /* Padding for future use */
} pcxheader_t;

#pragma pack(pop)
/*=========================================================================
 *      End of Type Definitions
 *=======================================================================*/


/*===========================================================================
 *
 * Begin Class CPcxFile Definition
 *
 * Handles simple PCX image files, derived from the CGenFile class.
 * Currently only supports 8 bit, 256 paletted images.
 *
 *=========================================================================*/
class CPcxFile : public CGenFile {

	/*---------- Begin Private Class Members ----------------------*/
  private:
	pcxheader_t m_Header;       /* Header information */

	byte *m_pData;        /* Raw image data (uncompressed) */
	long m_ImageSize;

	rgbpal_t *m_pPalette;     /* Palette data */
	int m_PaletteSize;


	/*---------- Begin Protected Class Methods --------------------*/
  protected:

	/* Sets header values to default values */
	void CreateStandardHeader (void);

	/* Helper input and output methods */
	bool ReadHeader (void);
	bool ReadImage (void);
	bool ReadPalette (void);
	bool WriteHeader (void);
	bool WriteImage (void);
	bool WritePalette (void);


	/*---------- Begin Public Class Methods -----------------------*/
  public:

	/* Class Constructors/Destructors */
	CPcxFile();
	virtual ~CPcxFile() {
		Destroy();
	}

	virtual void Destroy (void);

	/* Saves LBM image data to a standard 256 color PCX file */
	bool ExportLBM (const char* pFilename, const int Width, const int Height,
	                const byte* pImage, const byte* pPalette);

	/* Attempt to load/save the specified PCX image */
	bool Load (const char* pFilename);
	bool Save (const char* pFilename);

};

/*===========================================================================
 *      End of Class CPcxFile Definition
 *=========================================================================*/



#endif
/*=========================================================================
 *      End of File PCX.H
 *=======================================================================*/


