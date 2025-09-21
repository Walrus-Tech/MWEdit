/*===========================================================================
 *
 * File:    Pcx.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Tuesday, June 26, 2001
 *
 * Implements the CPcxFile class for handling simple PCX image files.
 *
 *=========================================================================*/

#include "pcx.h"


DEFINE_FILE("pcx.cpp");


/*===========================================================================
 *
 * Class CPcxFile Constructor
 *
 *=========================================================================*/
CPcxFile::CPcxFile() {
	//DEFINE_FUNCTION("CPcxFile::CPcxFile()");
	m_pData = NULL;
	m_pPalette = NULL;
	m_PaletteSize = 0;
	m_ImageSize = 0;
	/* Initialize the PCX header */
	memset(&m_Header, 0, sizeof(pcxheader_t));
}


/*=========================================================================
 *
 * Class CPcxFile Destructor
 *
 *=======================================================================*/
void CPcxFile::Destroy() {
	DEFINE_FUNCTION("CPcxFile::Destroy()");
	/* Delete the allocated data */
	DestroyArrayPointer(m_pData);
	DestroyArrayPointer(m_pPalette);
	m_PaletteSize = 0;
	m_ImageSize = 0;
	memset(&m_Header, 0, sizeof(pcxheader_t));
}


/*===========================================================================
 *
 * Class CPcxFile Method - void CreateStandardHeader (void);
 *
 * Initializes the PCX header with default values.  Protected class method.
 *
 *=========================================================================*/
void CPcxFile::CreateStandardHeader() {
	/* Clear header */
	memset(&m_Header, 0, sizeof(pcxheader_t));
	/* Set header defaults */
	m_Header.Manufacturer = 10;
	m_Header.Version = 5;
	m_Header.Encoding = 1;
	m_Header.BitsPerPixel = 8;
	m_Header.HorzResolution = 150;
	m_Header.VertResolution = 150;
	m_Header.NumColorPlanes = 1;
	m_Header.PaletteType = 1;
	m_Header.Padding[1] = 4;
	m_Header.Padding[3] = 3;
}


/*=========================================================================
 *
 * Class CPcxFile Method -
 *  bool ExportLBM (pFilename, Width, Height, pImage, pPalette);
 *
 * Uses the given image information to save the data to a standard 256
 * colour (8 bit) paletted PCX file with the given name.  The input
 * palette is assumed to be a standard 265 color, 768 byte, palette data
 * with color values ranging from 0 to 255.  Returns FALSE on any error.
 * The current PCX image, if any, is destroyed.
 *
 *=======================================================================*/
bool CPcxFile::ExportLBM(const char *pFilename,
                         const int Width,
                         const int Height,
                         const byte *pImage,
                         const byte *pPalette) {
	DEFINE_FUNCTION("CPcxFile::ExportLBM()");
	bool Result;
	/* Ensure valid input */
	ASSERT(pFilename != NULL && pPalette != NULL);
	ASSERT(Width >= 0 && Height >= 0);

	/* Destroy the current PCX image */
	Destroy();
	/* Initialize the PCX header */
	CreateStandardHeader();

	/* Set the image sizes */
	m_Header.Width = Width;
	m_Header.Height = Height;
	m_Header.BytesPerLine = Width;
	m_ImageSize = (long)Width * (long)Height;

	/* Temporarily use the image and palette data pointers */
	m_pData = (byte *)pImage;
	m_pPalette = (rgbpal_t *)pPalette;
	m_PaletteSize = 256;

	/* Attempt to save the image */
	Result = Save(pFilename);

	/* Reset the image/palette pointers so that they are not deleted */
	m_pData = NULL;
	m_pPalette = NULL;

	/* Delete the PCX image */
	Destroy();
	return Result;
}


/*=========================================================================
 *
 * Class CPcxFile Method - bool Load (pFilename);
 *
 * Attempts to read in the specified PCX file.  Returns FALSE on any error.
 *
 *=======================================================================*/
bool CPcxFile::Load(const char *pFilename) {
	DEFINE_FUNCTION("CPcxFile::Load()");
	bool Result;
	/* Attempt to open the file for input */
	Result = Open(pFilename, "rb");

	if (!Result) {
		return FALSE;
	}

	/* Clear the current image contents, if any */
	Destroy();
	/* Read in the header, image, and palette data */
	Result = ReadHeader();

	if (Result) {
		Result = ReadImage();
	}

	if (Result) {
		Result = ReadPalette();
	}

	Close();
	return Result;
}


/*=========================================================================
 *
 * Class CPcxFile Method - bool ReadHeader (void);
 *
 * Attempts to read in the header data from the current position in
 * in the file stream.  Returns FALSE on any error.  Protected class
 * method.
 *
 *=======================================================================*/
bool CPcxFile::ReadHeader() {
	//DEFINE_FUNCTION("CPcxFile::ReadHeader()");
	bool Result;
	/* Load the header all at once */
	Result = CGenFile::Read((char *)&m_Header, sizeof(pcxheader_t));

	if (!Result) {
		return FALSE;
	}

	/* Adjust image size now to make life easier */
	m_Header.Width++;
	m_Header.Height++;
	return TRUE;
}


/*===========================================================================
 *
 * Class CPcxFile Method - bool ReadImage (void);
 *
 * Protected class method which attempts to read in the image data from
 * the current position in the file stream.  Returns FALSE on any error.
 *
 *=========================================================================*/
bool CPcxFile::ReadImage() {
	DEFINE_FUNCTION("CPcxFile::ReadImage()");
	size_t Count = 0;
	size_t BytesInput;
	size_t DataIndex;

	int Column;
	int RowDiff;
	int Row;
	int NumBytes;
	int InputChar;

	/* Check the image size */
	m_ImageSize = (long)m_Header.Width * (long)m_Header.Height;

	/* Check for size overflow */
	if ((ulong)m_ImageSize >= (long)UINT_MAX) {
		ErrorHandler.AddError(PCXERR_BIGIMAGE);
		return FALSE;
	} else if (m_ImageSize < 0) { /* Check for a negative image size */
		ErrorHandler.AddError(PCXERR_IMAGESIZE);
		return FALSE;
	} else if (m_ImageSize == 0) { /* Ignore if no data to load */
		return TRUE;
	}

	/* Allocate image data */
	CreateArrayPointer(m_pData, byte, (size_t)m_ImageSize);
	/* Initialize input and uncompression variables */
	DataIndex = 0;
	BytesInput = 0;
	Column = 0;
	Row = 0;
	RowDiff = m_Header.BytesPerLine - m_Header.Width;

	/* Read in the image data */
	while (DataIndex <= (size_t)m_ImageSize) {
		ClearError();

		/* Remove any row padding */
		if (RowDiff > 0 && Column >= m_Header.Width) {
			if (Column == m_Header.BytesPerLine) {
				Column = 0;
				Row++;
				DataIndex--;
			} else if (Column >= m_Header.Width) {
				Column = 0;
				Row++;

				while (Column != RowDiff) {
					InputChar = fgetc(GetHandle());
					BytesInput++;

					if (InputChar >= PCX_RLE_VALUE) {
						InputChar = fgetc(GetHandle());
						BytesInput++;
					}

					Column++;
				}

				Column = 0;
			}
		} else { /* Read in regular or RLE pixel data */
			InputChar = fgetc(GetHandle());
			BytesInput++;

			/* Is this byte a RLE code? */
			if (InputChar >= PCX_RLE_VALUE) {
				NumBytes = InputChar - PCX_RLE_VALUE;
				/* Get the actual pixel data for the run */
				InputChar = fgetc(GetHandle());
				BytesInput++;

				/* Replicate data in image buffer */
				while (NumBytes-- > 0) {
					m_pData[DataIndex] = (byte)InputChar;
					DataIndex++;
					Column++;
				}
			} else { /* Copy uncompressed data into image buffer */
				m_pData[DataIndex] = (byte)InputChar;
				DataIndex++;
				Column++;
			}
		}

		/* Check for errors */
		if (IsError() || IsEOF()) {
			return FALSE;
		}
	} /* End while loop */

	return TRUE;
}


/*===========================================================================
 *
 * Class CPcxFile Method - bool ReadPalette (void);
 *
 * Attempts to read an 8 bit, 256 entry, RGB palette fromt the end of
 * the PCX file. Returns FALSE on any error.  Protected class method.
 *
 *=========================================================================*/
bool CPcxFile::ReadPalette() {
	DEFINE_FUNCTION("CPcxFile::ReadPalette()");
	bool Result;

	/* Allocate the palette data as required */
	if (m_pPalette == NULL || m_PaletteSize < 256) {
		DestroyArrayPointer(m_pPalette);
		CreateArrayPointer(m_pPalette, rgbpal_t, 256);
		m_PaletteSize = 256;
	}

	/* Move to end of file and input palette data */
	Result = Seek(-768l, SEEK_END);

	if (Result) {
		Result = CGenFile::Read((char *)m_pPalette, 256 * sizeof(rgbpal_t));
	}

	return Result;
}


/*=========================================================================
 *
 * Class CPcxFile Method - bool Save (pFilename);
 *
 * Attempts to save the PCX image to the specified file.  Returns FALSE
 * on any error.
 *
 *=======================================================================*/
bool CPcxFile::Save(const char *pFilename) {
	DEFINE_FUNCTION("CPcxFile::Save()");
	bool Result;
	/* Attempt to open file for output */
	Result = Open(pFilename, "wb");

	if (!Result) {
		return FALSE;
	}

	/* Output the PCX data */
	Result = WriteHeader();

	if (Result) {
		Result = WriteImage();
	}

	if (Result) {
		Result = WritePalette();
	}

	return Result;
}


/*=========================================================================
 *
 * Class CPcxFile Method - bool WriteHeader (void);
 *
 * Attempts to write the header data to the current position in the
 * file stream.  Returns FALSE on any error.  Protected class method.
 *
 *=======================================================================*/
bool CPcxFile::WriteHeader() {
	//DEFINE_FUNCTION("CPcxFile::WriteHeader()");
	bool Result;
	/* Adjust image size temporarily */
	m_Header.Width--;
	m_Header.Height--;
	/* Write the header all at once */
	Result = CGenFile::Write((char *)&m_Header, sizeof(pcxheader_t));
	/* Reset image size */
	m_Header.Width++;
	m_Header.Height++;
	return Result;
}


/*===========================================================================
 *
 * Class CPcxFile Method - bool WriteImage (void);
 *
 * Protected class method which writes the RLE compressed image data
 * to the current position in the file stream.  Returns FALSE on any error.
 *
 *=========================================================================*/
bool CPcxFile::WriteImage() {
	DEFINE_FUNCTION("CPcxFile::WriteImage()");
	byte *pDataPtr;
	byte PrevData;
	int ByteCount;
	int Column;
	long Index;

	/* Ignore if no image to write */
	if (m_ImageSize == 0 || m_pData == NULL) {
		return TRUE;
	}

	/* Initialize compression and output variables */
	pDataPtr = m_pData;
	PrevData = *pDataPtr;
	Column = 1;
	pDataPtr++;

	/* Write the main image */
	for (Index = 0; Index < m_ImageSize; Index++) {
		ClearError();
		ByteCount = 1;

		/* Count the number of consecutive identical pixels */
		while (*pDataPtr == PrevData && ByteCount < 63 && Column != m_Header.Width) {
			pDataPtr++;
			ByteCount++;
			Index++;
			Column++;
		}

		/* Output single pixel data value */
		if (ByteCount == 1) {
			if (PrevData >= PCX_RLE_VALUE) {
				fputc(PCX_RLE_VALUE + 1, GetHandle());
			}

			fputc(PrevData, GetHandle());
		} else { /* Output RLE encoded bytes */
			fputc((byte)(PCX_RLE_VALUE + ByteCount), GetHandle());
			fputc(PrevData, GetHandle());
		}

		/* Check for error conditions */
		if (IsError() || IsEOF()) {
			return FALSE;
		}

		if (Column == m_Header.Width) {
			Column = 0;
		}

		PrevData = *pDataPtr;
		pDataPtr++;
		Column++;
	}

	return TRUE;
}


/*===========================================================================
 *
 * Class CPcxFile Method - bool WritePalette (void);
 *
 * Protected class method which outputs the palette data to the current
 * position in the file stream.  Returns FALSE on any error.
 *
 *=========================================================================*/
bool CPcxFile::WritePalette() {
	DEFINE_FUNCTION("CPcxFile::WritePalette()");
	bool Result;

	/* Ignore if nothing to write */
	if (m_PaletteSize == 0 || m_pPalette == NULL) {
		return TRUE;
	}

	/* Need this to seperate the image and palette data? */
	Result = WriteChar(0x0C);

	/* Write palette data */
	if (Result) {
		Result = CGenFile::Write((char *)m_pPalette, m_PaletteSize * sizeof(rgbpal_t));
	}

	return Result;
}


/*===========================================================================
 *
 * Function - bool CreatePCXErrors (void);
 *
 * Adds the PCX error messages to the error database.
 *
 *=========================================================================*/
bool CreatePCXErrors() {
	ErrorDatabase.Add(PCXERR_BIGIMAGE,
	                  "PCX image size exceeds the maximum allocation size for this system!");
	ErrorDatabase.Add(PCXERR_IMAGESIZE, "PCX image size is not valid!");
	return TRUE;
}

/* Add the errors automatically on startup */
static bool _InitPCXErrors = CreatePCXErrors();
