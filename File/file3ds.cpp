/*===========================================================================
 *
 * File:    File3ds.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Friday, June 22, 2001
 *
 * Implements the C3dsFile class.
 *
 *=========================================================================*/

/* Include Files */
#include "file3ds.h"
#include <math.h>


/*===========================================================================
 *
 * Begin Local Variable Definitions
 *
 *=========================================================================*/
DEFINE_FILE("file3ds.cpp");
/*===========================================================================
 *      End of Local Variable Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Chunk ID Structure
 *
 * Contains information for each of the known 3DS chunk IDs.  Use the
 * static C3dsFile methods
 *  chunk3ds_t*  FindChunk(ID);
 *  char*        GetChunkName(ID);
 *  int      GetChunkFlag(ID);
 * to access the array elements.
 *
 *=========================================================================*/
#include "chunk3ds.h"
/*===========================================================================
 *      End of Chunk ID Structure
 *=========================================================================*/




/*===========================================================================
 *
 * Class C3dsFile Method -
 *  void CreateMeshMatrix (float* pMeshMatrix, XPos,   YPos,   ZPos,
 *                         XScale, YScale, ZScale,
 *                         XAngle, YAngle, ZAngle);
 *
 * Static class method to generate a translation mesh matrix using the
 * given input.  The input matrix pointer must point to at least 12 floats,
 * or a 3x4 matrix.
 *  0 1 2       0, 4, 8 = X,Y,Z Scale translation
 *  3 4 5       9, A, B = X,Y,Z Position translation
 *  6 7 8
 *  9 A B
 *
 *=========================================================================*/
void C3dsFile::CreateMeshMatrix(float *pMeshMatrix,
                                const float XPos,
                                const float YPos,
                                const float ZPos,
                                const float XScale,
                                const float YScale,
                                const float ZScale,
                                const float XAngle,
                                const float YAngle,
                                const float ZAngle) {
	DEFINE_FUNCTION("C3dsFile::CreateMeshMatrix()");
	/* Ensure valid input */
	ASSERT(pMeshMatrix != NULL);
	/* Initialize the matrix */
	memset(pMeshMatrix, 0, sizeof(float) * 12);

	/* Set just the z-axis rotation transform for now */
	pMeshMatrix[0] = (float)cos(ZAngle);
	pMeshMatrix[4] = pMeshMatrix[0];
	pMeshMatrix[1] = (float)sin(ZAngle);
	pMeshMatrix[3] = -pMeshMatrix[1];
	pMeshMatrix[8] = (float)1.0;

	/* Set the scale components */
	pMeshMatrix[0] *= XScale;
	pMeshMatrix[4] *= YScale;
	pMeshMatrix[8] *= ZScale;

	/* Set the position components */
	pMeshMatrix[9] = XPos;
	pMeshMatrix[10] = YPos;
	pMeshMatrix[11] = ZPos;
}

/*===========================================================================
 *      End of Class Method C3dsFile::CreateMeshMatrix()
 *=========================================================================*/


/*===========================================================================
 *
 * Class C3dsFile Method - bool DumpChunk (pFileHandle);
 *
 * Recursive method which reads in the chunk header at the current location
 * and outputs to the given file stream and current SystemLog file.  Returns
 * FALSE on any error.  Protected class method.
 *
 *=========================================================================*/
bool C3dsFile::DumpChunk(FILE *pFileHandle) {
	//DEFINE_FUNCTION("C3dsFile::DumpChunk()");
	bool Result;
	ushort ChunkID;
	long ChunkSize;
	long EndPos;
	/* Input the chunk header */
	Result = ReadShort((short &)ChunkID);

	if (Result) {
		Result = ReadLong(ChunkSize);
	}

	if (!Result) {
		SystemLog.Printf(pFileHandle, "\tError reading 3DS chunk header data!");
		return FALSE;
	}

	/* Output chunk information */
	SystemLog.Printf(pFileHandle,
	                 "Chunk 0x%04hX (%ld bytes), %s",
	                 ChunkID,
	                 ChunkSize,
	                 GetChunkName(ChunkID));
	EndPos = Tell() + ChunkSize - 6;

	/* Read an object chunk, special case */
	if (ChunkID == CHUNK3DS_ID_NAMEDOBJECT) {
		Result = ReadName(NULL);

		if (!Result) {
			return FALSE;
		}
	} else if (ChunkID == CHUNK3DS_ID_MESHMATRIX) {
		Result = DumpMeshMatrix(pFileHandle);
		return Result;
	} else if ((GetChunkFlag(ChunkID) & CHUNK3DS_FLAG_SIMPLECONTAINER) == 0) { /* Skip unknown-sized chunk */
		Result = Seek(ChunkSize - 6, SEEK_CUR);
		return Result;
	}

	SystemLog.IncrementTabs();

	/* Read in sub-chunks until chunk size is reached */
	while (Tell() < EndPos) {
		Result = DumpChunk(pFileHandle);

		if (!Result) {
			break;
		}
	}

	if (EndPos != Tell()) {
		SystemLog.Printf(pFileHandle,
		                 "\tPossible error reading chunk (%ld bytes over read)!",
		                 EndPos - Tell());
	}

	SystemLog.DecrementTabs();
	return Result;
}

/*===========================================================================
 *      End of Class Method C3dsFile::DumpChunk()
 *=========================================================================*/


/*===========================================================================
 *
 * Class C3dsFile Method - bool DumpContents (pFileHandle);
 *
 * Dumps the contents of the 3DS file to the given file stream and current
 * SystemLog file.  Returns FALSE on any error.
 *
 *=========================================================================*/
bool C3dsFile::DumpContents(FILE *pFileHandle) {
	DEFINE_FUNCTION("C3dsFile::DumpContents()");
	bool Result;

	/* Ensure file is open */
	if (!IsOpen()) {
		SystemLog.Printf(pFileHandle, "3DS file must be open to dump its contents!");
		return FALSE;
	}

	/* Move to start of file */
	Result = Seek(0, SEEK_SET);

	if (!Result) {
		SystemLog.Printf(pFileHandle, "Failed to move to start of 3DS file!");
		return FALSE;
	}

	/* Start recursively reading chunks */
	SystemLog.IncrementTabs();
	Result = DumpChunk(pFileHandle);
	SystemLog.DecrementTabs();
	return Result;
}

/*===========================================================================
 *      End of Class Method C3dsFile::DumpContents()
 *=========================================================================*/


/*===========================================================================
 *
 * Class C3dsFile Method - bool DumpMeshMatrix (pFileHandle);
 *
 * Dumps the mesh matrix contents from the current position in the file
 * stream to the SystemLog and stdout.  Returns FALSE on any error.
 * Protected class method.
 *
 *=========================================================================*/
bool C3dsFile::DumpMeshMatrix(FILE *pFileHandle) {
	DEFINE_FUNCTION("C3dsFile::DumpMeshMatrix()");
	char Buffer[256];
	char NumBuffer[32];
	float InputFloat;
	bool Result;
	int Row;
	int Column;

	/* Read the 3x4 float matrix */
	for (Row = 0; Row < 4; Row++) {
		Buffer[0] = NULL_CHAR;

		for (Column = 0; Column < 3; Column++) {
			Result = ReadFloat(InputFloat);

			if (!Result) {
				return FALSE;
			}

			sprintf(NumBuffer, "%8.3f  ", InputFloat);
			strcat(Buffer, NumBuffer);
		}

		SystemLog.Printf(stdout, "%s", Buffer);
	}

	return TRUE;
}

/*===========================================================================
 *      End of Class Method C3dsFile::DumpMeshMatrix()
 *=========================================================================*/


/*===========================================================================
 *
 * Class C3dsFile Method - chunk3ds_t* FindChunk (ChunkID);
 *
 * Static class method which attempts to find the given ChunkID in the
 * local ChunkInfo[] array.  Returns NULL on any error.
 *
 *=========================================================================*/
chunk3ds_t *C3dsFile::FindChunk(const ushort ChunkID) {
	int Index;

	/* Search entire array for ID match */
	for (Index = 0; ChunkInfo[Index].ID != CHUNK3DS_ID_LAST; Index++) {
		if (ChunkInfo[Index].ID == ChunkID) {
			return &(ChunkInfo[Index]);
		}
	}

	/* No match found! */
	ErrorHandler.AddError(ERR_BADINPUT, "3DS chunk id 0x%04hX not found!", ChunkID);
	return NULL;
}

/*===========================================================================
 *      End of Class Method C3dsFile::FindChunk()
 *=========================================================================*/


/*===========================================================================
 *
 * Class C3dsFile Method - int GetChunkFlag (const ushort ChunkID);
 *
 * Static class method which returns a the flag of the given chunk ID.
 * If the chunk ID is invalid, 0 is returned.
 *
 *=========================================================================*/
int C3dsFile::GetChunkFlag(const ushort ChunkID) {
	chunk3ds_t *pChunk = FindChunk(ChunkID);

	if (pChunk == NULL) {
		return 0;
	}

	return pChunk->Flags;
}

/*===========================================================================
 *      End of Class Method C3dsFile::GetChunkFlag()
 *=========================================================================*/


/*===========================================================================
 *
 * Class C3dsFile Method - char* GetChunkName (const ushort ChunkID);
 *
 * Static class method which returns a valid string describing the
 * given chunk ID.  If the chunk ID is invalid, a default string is
 * returned, never NULL.
 *
 *=========================================================================*/
char *C3dsFile::GetChunkName(const ushort ChunkID) {
	chunk3ds_t *pChunk = FindChunk(ChunkID);

	if (pChunk == NULL) {
		return "Invalid Chunk ID";
	}

	if (pChunk->pName == NULL) {
		return "Invalid Chunk Name";
	}

	return pChunk->pName;
}

/*===========================================================================
 *      End of Class Method C3dsFile::GetChunkName()
 *=========================================================================*/


/*===========================================================================
 *
 * Class C3dsFile Method - bool OutputMatEntry (pMatName, pTextureName);
 *
 * Outputs a standard material entry with the given material and texture
 * file name.  Uses standard material settings.  Returns FALSE on any error.
 *
 *=========================================================================*/
bool C3dsFile::OutputMatEntry(const char *pMatName, const char *pTextureName) {
	DEFINE_FUNCTION("C3dsFile::OutputMatEntry()");
	bool Result;
	/* Ensure valid input */
	ASSERT(pMatName != NULL);
	ASSERT(pTextureName != NULL);
	/* Start the material entry chunk */
	Result = StartChunk(CHUNK3DS_MAT_ENTRY);

	if (!Result) {
		return FALSE;
	}

	/* Output the material name */
	Result = WriteString(CHUNK3DS_MAT_NAME, pMatName);

	/* Output default object colors */
	Result &= WriteCharColor(CHUNK3DS_MAT_AMBIENT, 0x96, 0x96, 0x96);
	Result &= WriteCharColor(CHUNK3DS_MAT_DIFFUSE, 0x96, 0x96, 0x96);
	Result &= WriteCharColor(CHUNK3DS_MAT_SPECULAR, 0xE5, 0xE5, 0xE5);

	/* Output default material properties */
	Result &= WriteIntPercent(CHUNK3DS_MAT_SHININESS, 10);
	Result &= WriteIntPercent(CHUNK3DS_MAT_SHIN2PCT, 0);
	Result &= WriteIntPercent(CHUNK3DS_MAT_TRANSPARENCY, 0);
	Result &= WriteIntPercent(CHUNK3DS_MAT_XPFALL, 0);
	Result &= WriteIntPercent(CHUNK3DS_MAT_REFBLUR, 0);
	Result &= WriteChunkShort(CHUNK3DS_MAT_SHADING, 3);
	Result &= WriteIntPercent(CHUNK3DS_MAT_SELF_ILPCT, 0);
	Result &= WriteChunkFloat(CHUNK3DS_MAT_WIRESIZE, 1.0f);

	/* Output the texture map chunk */
	Result &= StartChunk(CHUNK3DS_MAT_TEXMAP);
	Result &= WriteIntPercent(100);
	Result &= WriteString(CHUNK3DS_MAT_MAPNAME, pTextureName);
	Result &= WriteChunkShort(CHUNK3DS_MAT_MAP_TILING, 0);
	Result &= WriteChunkFloat(CHUNK3DS_MAT_MAP_TEXBLUR, 0);
	Result &= EndChunk(CHUNK3DS_MAT_TEXMAP);

	/* End the material entry chunk */
	Result &= EndChunk(CHUNK3DS_MAT_ENTRY);
	return Result;
}

/*===========================================================================
 *      End of Class Method C3dsFile::OutputMatEntry()
 *=========================================================================*/


/*===========================================================================
 *
 * Class C3dsFile Method - bool OutputMatEntry (pMatName, PalEntry);
 *
 * Outputs a standard material entry section to the 3DS file with the
 * given RBG palette.  Returns FALSE on any error.
 *
 *=========================================================================*/
bool C3dsFile::OutputMatEntry(const char *pMatName, const rgbpal_t &PalEntry) {
	DEFINE_FUNCTION("C3dsFile::OutputMatEntry()");
	bool Result;
	/* Ensure valid input */
	ASSERT(pMatName != NULL);
	/* Start the material entry chunk */
	Result = StartChunk(CHUNK3DS_MAT_ENTRY);

	if (!Result) {
		return FALSE;
	}

	/* Output the material name */
	Result = WriteString(CHUNK3DS_MAT_NAME, pMatName);

	/* Output default object colors */
	Result &= WriteCharColor(CHUNK3DS_MAT_AMBIENT, PalEntry.R, PalEntry.G, PalEntry.B);
	Result &= WriteCharColor(CHUNK3DS_MAT_DIFFUSE, PalEntry.R, PalEntry.G, PalEntry.B);
	Result &= WriteCharColor(CHUNK3DS_MAT_SPECULAR, 0xE5, 0xE5, 0xE5);

	/* Output default material properties */
	Result &= WriteIntPercent(CHUNK3DS_MAT_SHININESS, 10);
	Result &= WriteIntPercent(CHUNK3DS_MAT_SHIN2PCT, 0);
	Result &= WriteIntPercent(CHUNK3DS_MAT_TRANSPARENCY, 0);
	Result &= WriteIntPercent(CHUNK3DS_MAT_XPFALL, 0);
	Result &= WriteIntPercent(CHUNK3DS_MAT_REFBLUR, 0);
	Result &= WriteChunkShort(CHUNK3DS_MAT_SHADING, 3);
	Result &= WriteIntPercent(CHUNK3DS_MAT_SELF_ILPCT, 0);
	Result &= WriteChunkFloat(CHUNK3DS_MAT_WIRESIZE, 1.0f);

	/* End the material entry chunk */
	Result &= EndChunk(CHUNK3DS_MAT_ENTRY);
	return Result;
}

/*===========================================================================
 *      End of Class Method C3dsFile::OutputMatEntry()
 *=========================================================================*/


/*===========================================================================
 *
 * Class C3dsFile Method - bool PopChunkStack (ID);
 *
 * Protected class method which pops the top chunk from the stack.  The
 * given ID must match the popped item ID or an error will occur.
 * stack with the given ID and current file position. FALSE is returned
 * on any error.  Outputs the chunk 6 byte header.
 *
 *=========================================================================*/
bool C3dsFile::PopChunkStack(const ushort ID) {
	DEFINE_FUNCTION("C3dsFile::PopChunkStack()");
	bool Result;
	long Offset;

	/* Ensure a valid stack size */
	if (m_ChunkStackSize <= 0) {
		ASSERT(m_ChunkStackSize > 0);
		ErrorHandler.AddError(ERR_BADARRAYINDEX, "No items on 3DS chunk stack to pop!");
		return FALSE;
	}

	/* Remove item */
	m_ChunkStackSize--;

	/* Ensure a valid ID */
	if (ID != m_ChunkStack[m_ChunkStackSize].ID) {
		ASSERT(ID == m_ChunkStack[m_ChunkStackSize].ID);
		ErrorHandler.AddError(ERR_BADINPUT,
		                      "3DS chunk ID of 0x%04X does not match chunk stack ID of 0x%04X",
		                      (int)ID,
		                      (int)m_ChunkStack[m_ChunkStackSize].ID);
		return FALSE;
	}

	/* Update the chunk size */
	Result = Tell(Offset);

	if (Result) {
		Result = Seek(m_ChunkStack[m_ChunkStackSize].Offset + 2, SEEK_SET);
	}

	if (Result) {
		Result = WriteLong(Offset - m_ChunkStack[m_ChunkStackSize].Offset);
	}

	if (Result) {
		Result = Seek(Offset, SEEK_SET);
	}

	return Result;
}

/*===========================================================================
 *      End of Class Method C3dsFile::PopChunkStack()
 *=========================================================================*/


/*===========================================================================
 *
 * Class C3dsFile Method - bool PopChunkStack (ID, Value);
 *
 * Protected class method which pops the top chunk from the stack.  The
 * given ID must match the popped item ID or an error will occur.
 * stack with the given ID and current file position. FALSE is returned
 * on any error.  Outputs the chunk 6 byte header in addition to the
 * given short value.
 *
 *=========================================================================*/
bool C3dsFile::PopChunkStack(const ushort ID, const short Value) {
	DEFINE_FUNCTION("C3dsFile::PopChunkStack(ushort, short)");
	bool Result;
	long Offset;

	/* Ensure a valid stack size */
	if (m_ChunkStackSize <= 0) {
		ASSERT(m_ChunkStackSize > 0);
		ErrorHandler.AddError(ERR_BADARRAYINDEX, "No items on 3DS chunk stack to pop!");
		return FALSE;
	}

	/* Remove item */
	m_ChunkStackSize--;

	/* Ensure a valid ID */
	if (ID != m_ChunkStack[m_ChunkStackSize].ID) {
		ASSERT(ID == m_ChunkStack[m_ChunkStackSize].ID);
		ErrorHandler.AddError(ERR_BADINPUT,
		                      "3DS chunk ID of 0x%04X does not match chunk stack ID of 0x%04X",
		                      (int)ID,
		                      (int)m_ChunkStack[m_ChunkStackSize].ID);
		return FALSE;
	}

	/* Update the chunk size */
	Result = Tell(Offset);

	if (Result) {
		Result = Seek(m_ChunkStack[m_ChunkStackSize].Offset + 2, SEEK_SET);
	}

	if (Result) {
		Result = WriteLong(Offset - m_ChunkStack[m_ChunkStackSize].Offset);
	}

	if (Result) {
		Result = WriteShort(Value);
	}

	if (Result) {
		Result = Seek(Offset, SEEK_SET);
	}

	return Result;
}

/*===========================================================================
 *      End of Class Method C3dsFile::PopChunkStack()
 *=========================================================================*/


/*===========================================================================
 *
 * Class C3dsFile Method - bool PushChunkStack (const ushort ID);
 *
 * Description
 *
 *=========================================================================*/
bool C3dsFile::PushChunkStack(const ushort ID) {
	DEFINE_FUNCTION("C3dsFile::PushChunkStack()");
	bool Result;

	/* Ensure a valid stack size */
	if (m_ChunkStackSize >= CHUNK3DS_STACK_SIZE) {
		ASSERT(m_ChunkStackSize < CHUNK3DS_STACK_SIZE);
		ErrorHandler.AddError(ERR_MAXINDEX,
		                      "Maximum of %d 3DS chunk stack items exceeded!",
		                      CHUNK3DS_STACK_SIZE);
		return FALSE;
	}

	/* Store stack data */
	m_ChunkStack[m_ChunkStackSize].ID = ID;
	Result = Tell(m_ChunkStack[m_ChunkStackSize].Offset);

	/* Output the chunk header (ID + initial size) */
	if (Result) {
		Result = WriteShort(ID);
	}

	if (Result) {
		Result = WriteLong(6);
	}

	/* Increase stack size on success */
	if (Result) {
		m_ChunkStackSize++;
	}

	return Result;
}

/*===========================================================================
 *      End of Class Method C3dsFile::PushChunkStack()
 *=========================================================================*/


/*===========================================================================
 *
 * Class C3dsFile Method - bool ReadName (pBuffer);
 *
 * Read in a CString name from the current position in the file (a string
 * ended by a NULL terminator character.  Returns FALSE on any error.
 * Protected class method.
 *
 *=========================================================================*/
bool C3dsFile::ReadName(char *pBuffer) {
	bool Result;
	char InputChar;

	do {
		Result = ReadChar(InputChar);

		if (!Result) {
			return FALSE;
		}

		/* Add character to buffer if required */
		if (pBuffer != NULL) {
		}
	} while (InputChar != NULL_CHAR);

	return TRUE;
}

/*===========================================================================
 *      End of Class Method C3dsFile::ReadName()
 *=========================================================================*/


/*===========================================================================
 *
 * Class C3dsFile Method - bool StartEditChunk (void);
 *
 * Outputs the start of the main 3DS edit chunk.  Returns a FALSE on any
 * error.
 *
 *=========================================================================*/
bool C3dsFile::StartEditChunk() {
	bool Result;
	/* Output the edit chunk header and version */
	Result = PushChunkStack(CHUNK3DS_ID_EDIT);

	if (Result) {
		Result = WriteShort(CHUNK3DS_ID_EDITVERSION);
	}

	if (Result) {
		Result = WriteLong(0x0Al);
	}

	if (Result) {
		Result = WriteLong(3l);
	}

	/* Output the default master scale value */
	if (Result) {
		Result = WriteShort(CHUNK3DS_ID_MASTERSCALE);
	}

	if (Result) {
		Result = WriteLong(0x0Al);
	}

	if (Result) {
		Result = WriteFloat(1.0);
	}

	return Result;
}

/*===========================================================================
 *      End of Class Method C3dsFile::StartEditChunk()
 *=========================================================================*/


/*===========================================================================
 *
 * Class C3dsFile Method - bool StartFaceChunk (void);
 *
 * Outputs the start of the face 3DS chunk.  Returns a FALSE on any
 * error.
 *
 *=========================================================================*/
bool C3dsFile::StartFaceChunk() {
	//DEFINE_FUNCTION("C3dsFile::StartFaceChunk()");
	bool Result;
	/* Output the face chunk header */
	Result = PushChunkStack(CHUNK3DS_ID_FACEARRAY);

	if (Result) {
		Result = WriteShort(0);
	}

	m_NumFaces = 0;
	return Result;
}

/*===========================================================================
 *      End of Class Method C3dsFile::StartFaceChunk()
 *=========================================================================*/


/*===========================================================================
 *
 * Class C3dsFile Method - bool StartMainChunk (void);
 *
 * Outputs the start of the main 3DS chunk.  Returns a FALSE on any
 * error.
 *
 *=========================================================================*/
bool C3dsFile::StartMainChunk() {
	bool Result;
	/* Reset the stack contents */
	m_ChunkStackSize = 0;
	/* Output the main chunk header and version */
	Result = PushChunkStack(CHUNK3DS_ID_MAIN);

	if (Result) {
		Result = WriteShort(CHUNK3DS_ID_3DSVERSION);
	}

	if (Result) {
		Result = WriteLong(0x0Al);
	}

	if (Result) {
		Result = WriteLong(3l);
	}

	return Result;
}

/*===========================================================================
 *      End of Class Method C3dsFile::StartMainChunk()
 *=========================================================================*/


/*===========================================================================
 *
 * Class C3dsFile Method - bool StartMatGroupChunk (pMatName, Count);
 *
 * Outputs the header to the material group chunk (0x4130).  Returns FALSE
 * on any error.
 *
 *=========================================================================*/
bool C3dsFile::StartMatGroupChunk(const char *pMatName, const short Count) {
	DEFINE_FUNCTION("C3dsFile::StartMatGroupChunk()");
	bool Result;
	size_t NameLength;
	/* Ensure valid input */
	ASSERT(pMatName != NULL);
	NameLength = strlen(pMatName) + 1;
	/* Output the object chunk header, name, and array size */
	Result = PushChunkStack(CHUNK3DS_ID_MATGROUP);

	if (Result) {
		Result = Write(pMatName, NameLength);
	}

	if (Result) {
		Result = WriteShort(Count);
	}

	return Result;
}

/*===========================================================================
 *      End of Class Method C3dsFile::StartMatGroupChunk()
 *=========================================================================*/


/*===========================================================================
 *
 * Class C3dsFile Method - bool StartObjectChunk (pName);
 *
 * Outputs the start of a object 3DS chunk with the given name.
 * Returns a FALSE on any error.
 *
 *=========================================================================*/
bool C3dsFile::StartObjectChunk(const char *pName) {
	DEFINE_FUNCTION("C3dsFile::StartObjectChunk()");
	bool Result;
	size_t NameLength;
	/* Ensure valid input */
	ASSERT(pName != NULL);
	NameLength = strlen(pName) + 1;
	/* Output the object chunk header and name */
	Result = PushChunkStack(CHUNK3DS_ID_NAMEDOBJECT);

	if (Result) {
		Result = Write(pName, NameLength);
	}

	return Result;
}

/*===========================================================================
 *      End of Class Method C3dsFile::StartObjectChunk()
 *=========================================================================*/


/*===========================================================================
 *
 * Class C3dsFile Method - bool StartPointChunk (void);
 *
 * Outputs the start of the face 3DS chunk.  Returns a FALSE on any
 * error.
 *
 *=========================================================================*/
bool C3dsFile::StartPointChunk() {
	//DEFINE_FUNCTION("C3dsFile::StartPointChunk()");
	bool Result;
	/* Output the point chunk header */
	Result = PushChunkStack(CHUNK3DS_ID_POINTARRAY);

	if (Result) {
		Result = WriteShort(0);
	}

	m_NumPoints = 0;
	return Result;
}

/*===========================================================================
 *      End of Class Method C3dsFile::StartPointChunk()
 *=========================================================================*/


/*===========================================================================
 *
 * Class C3dsFile Method - bool StartTexVertChunk (void);
 *
 * Outputs the start of the texture vertices 3DS chunk.  Returns a FALSE
 * on any error.
 *
 *=========================================================================*/
bool C3dsFile::StartTexVertChunk() {
	//DEFINE_FUNCTION("C3dsFile::StartTexVertChunk()");
	bool Result;
	/* Output the face chunk header */
	Result = PushChunkStack(CHUNK3DS_ID_TEX_VERTS);

	if (Result) {
		Result = WriteShort(0);
	}

	return Result;
}

/*===========================================================================
 *      End of Class Method C3dsFile::StartTexVertChunk()
 *=========================================================================*/


/*===========================================================================
 *
 * Class C3dsFile Method - bool StartTrimeshChunk (void);
 *
 * Outputs the start of a trimesh 3DS chunk.  Returns a FALSE on any
 * error.
 *
 *=========================================================================*/
bool C3dsFile::StartTrimeshChunk() {
	return PushChunkStack(CHUNK3DS_ID_TRIMESH);
}

/*===========================================================================
 *      End of Class Method C3dsFile::StartTrimeshChunk()
 *=========================================================================*/


/*===========================================================================
 *
 * Class C3dsFile Method - bool WriteCharColor (ChunkID, Red, Green, Blue);
 *
 * Outputs a standard 3 byte RGB color to the current 3DS file.  Returns
 * FALSE on any error. The
 *
 *=========================================================================*/
bool C3dsFile::WriteCharColor(const ushort ChunkID,
                              const byte Red,
                              const byte Green,
                              const byte Blue) {
	bool Result;
	Result = WriteShort(ChunkID);

	if (Result) {
		Result = WriteLong(0x0Fl); /* Chunk size */
	}

	if (Result) {
		Result = WriteShort(CHUNK3DS_ID_COLOR24);
	}

	if (Result) {
		Result = WriteLong(0x09l); /* Subchunk size */
	}

	if (Result) {
		Result = WriteChar(Red); /* Color output */
	}

	if (Result) {
		Result = WriteChar(Green);
	}

	if (Result) {
		Result = WriteChar(Blue);
	}

	return Result;
}

/*===========================================================================
 *      End of Class Method C3dsFile::WriteCharColor()
 *=========================================================================*/


/*===========================================================================
 *
 * Class C3dsFile Method - bool WriteChunkFloat (ChunkID, Value);
 *
 * Outputs a standard float chunk with a custom chunk ID.
 * Returns FALSE on any error.
 *
 *=========================================================================*/
bool C3dsFile::WriteChunkFloat(const ushort ChunkID, const float Value) {
	bool Result;
	Result = WriteShort(ChunkID);

	if (Result) {
		Result = WriteLong(0x0Al);
	}

	if (Result) {
		Result = WriteFloat(Value);
	}

	return Result;
}

/*===========================================================================
 *      End of Class Method C3dsFile::WriteChunkFloat()
 *=========================================================================*/


/*===========================================================================
 *
 * Class C3dsFile Method - bool WriteChunkShort (ChunkID, Value);
 *
 * Outputs a standard integer chunk with a custom chunk ID.
 * Returns FALSE on any error.
 *
 *=========================================================================*/
bool C3dsFile::WriteChunkShort(const ushort ChunkID, const short Value) {
	bool Result;
	Result = WriteShort(ChunkID);

	if (Result) {
		Result = WriteLong(0x08l);
	}

	if (Result) {
		Result = WriteShort(Value);
	}

	return Result;
}

/*===========================================================================
 *      End of Class Method C3dsFile::WriteChunkShort()
 *=========================================================================*/


/*===========================================================================
 *
 * Class C3dsFile Method - bool WriteFace (Point1, Point2, Point3, Flags);
 *
 * outputs one face record to the 3DS file, returning FALSE on any error.
 *
 *=========================================================================*/
bool C3dsFile::WriteFace(const short Point1,
                         const short Point2,
                         const short Point3,
                         const short Flags) {
	bool Result;

	if (!IsOpen()) {
		return FALSE;
	}

	/* Output the 3 face points and the face default flags */
	Result = WriteShort(Point1);

	if (Result) {
		Result = WriteShort(Point2);
	}

	if (Result) {
		Result = WriteShort(Point3);
	}

	if (Result) {
		Result = WriteShort(Flags);
	}

	m_NumFaces++;
	return Result;
}

/*===========================================================================
 *      End of Class Method C3dsFile::WriteFace()
 *=========================================================================*/


/*===========================================================================
 *
 * Class C3dsFile Method - bool WriteIntPercent (ChunkID, Percentage);
 *
 * Outputs a standard integer percentage chunk with a custom chunk ID.
 * Returns FALSE on any error.
 *
 *=========================================================================*/
bool C3dsFile::WriteIntPercent(const ushort ChunkID, const short Percentage) {
	bool Result;
	Result = WriteShort(ChunkID);

	if (Result) {
		Result = WriteLong(0x0El);
	}

	if (Result) {
		Result = WriteIntPercent(Percentage);
	}

	return Result;
}

/*===========================================================================
 *      End of Class Method C3dsFile::WriteIntPercent()
 *=========================================================================*/


/*===========================================================================
 *
 * Class C3dsFile Method - bool WriteIntPercent (Percentage);
 *
 * Outputs a standard integer percentage chunk. Returns FALSE on any error.
 *
 *=========================================================================*/
bool C3dsFile::WriteIntPercent(const short Percentage) {
	bool Result;
	Result = WriteShort(CHUNK3DS_ID_INT_PERCENTAGE);

	if (Result) {
		Result = WriteLong(0x08l);
	}

	if (Result) {
		Result = WriteShort(Percentage);
	}

	return Result;
}

/*===========================================================================
 *      End of Class Method C3dsFile::WriteIntPercent()
 *=========================================================================*/


/*===========================================================================
 *
 * Class C3dsFile Method - bool WriteString (ChunkID, pString);
 *
 * Outputs a standard string chunk with the given chunk ID.
 *
 *=========================================================================*/
bool C3dsFile::WriteString(const ushort ChunkID, const char *pString) {
	DEFINE_FUNCTION("C3dsFile::WriteString()");
	bool Result;
	size_t StringLength;
	/* Ensure valid input */
	ASSERT(pString != NULL);
	StringLength = strlen(pString) + 1;
	/* Output the string chunk */
	Result = WriteShort(ChunkID);

	if (Result) {
		Result = WriteLong(StringLength + 6);
	}

	if (Result) {
		Result = Write(pString, StringLength);
	}

	return TRUE;
}

/*===========================================================================
 *      End of Class Method C3dsFile::WriteString()
 *=========================================================================*/


/*===========================================================================
 *
 * Class C3dsFile Method - bool WritePoint (X, Y, Z);
 *
 * Outputs one point record to the 3DS file, returning FALSE on any error.
 *
 *=========================================================================*/
bool C3dsFile::WritePoint(const float X, const float Y, const float Z) {
	bool Result;

	if (!IsOpen()) {
		return FALSE;
	}

	/* Output the 3 points */
	Result = WriteFloat(X);

	if (Result) {
		Result = WriteFloat(Y);
	}

	if (Result) {
		Result = WriteFloat(Z);
	}

	m_NumPoints++;
	return Result;
}

/*===========================================================================
 *      End of Class Method C3dsFile::WritePoint()
 *=========================================================================*/


/*===========================================================================
 *
 * Class C3dsFile Method - bool WriteMeshMatrix (pMeshMatrix);
 *
 * Outputs the mesh matrix chunk of a trimesh 3DS chunk.  Returns
 * FALSE on any error.  If the input mesh matrix is NULL, the default
 * untranslated matrix is used.  The mesh matrix is a 3x4 array of floats.
 *
 *=========================================================================*/
bool C3dsFile::WriteMeshMatrix(const float *pMeshMatrix) {
	static float DefaultMeshMatrix[12] = {
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0,
		0.0, 0.0, 0.0
	};
	long ChunkSize = sizeof(float) * 12 + 6;
	bool Result;

	/* Ensure file is open */
	if (!IsOpen()) {
		return FALSE;
	}

	if (pMeshMatrix == NULL) {
		pMeshMatrix = &DefaultMeshMatrix[0];
	}

	/* Output the mesh matrix chunk */
	Result = WriteShort(CHUNK3DS_ID_MESHMATRIX);

	if (Result) {
		Result = WriteLong(ChunkSize);
	}

	if (Result) {
		Result = Write((char *)pMeshMatrix, sizeof(float) * 12);
	}

	return Result;
}

/*===========================================================================
 *      End of Class Method C3dsFile::WriteMeshMatrix()
 *=========================================================================*/


/*===========================================================================
 *
 * Class C3dsFile Method - bool WriteTexVert (X, Y);
 *
 * Output one texture vertex coordinate to the TEX_VERTS chunk.  Returns
 * FALSE on any error.
 *
 *=========================================================================*/
bool C3dsFile::WriteTexVert(const float X, const float Y) {
	bool Result;
	/* Output the X-Y pair of floats */
	Result = WriteFloat(X);

	if (Result) {
		Result = WriteFloat(Y);
	}

	return Result;
}

/*===========================================================================
 *      End of Class Method C3dsFile::WriteTexVert()
 *=========================================================================*/
