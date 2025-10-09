/*===========================================================================
 *
 * File:    File3ds.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Friday, June 22, 2001
 *
 * Implements the C3dsFile class for handling 3DS files.
 *
 *=========================================================================*/
#ifndef __FILE3DS_H
#define __FILE3DS_H


#include "Common/File/GenFile.h"
#include "Common/Images/rgbpal.h"


/* Flags for the 3DS chunk types */
#define CHUNK3DS_FLAG_SIMPLECONTAINER 1

/* Size of the chunk stack in elements */
#define CHUNK3DS_STACK_SIZE 64

/* Chunk IDs */
#define CHUNK3DS_ID_NULL              ((ushort)0x0000)
#define CHUNK3DS_ID_3DSVERSION        ((ushort)0x0002)
#define CHUNK3DS_ID_COLOR24           ((ushort)0x0011)
#define CHUNK3DS_ID_INT_PERCENTAGE    ((ushort)0x0030)
#define CHUNK3DS_ID_MAIN              ((ushort)0x4D4D)
#define CHUNK3DS_ID_EDIT              ((ushort)0x3D3D)
#define CHUNK3DS_ID_EDITVERSION       ((ushort)0x3D3E)
#define CHUNK3DS_ID_MASTERSCALE       ((ushort)0x0100)
#define CHUNK3DS_ID_NAMEDOBJECT       ((ushort)0x4000)
#define CHUNK3DS_ID_TRIMESH           ((ushort)0x4100)
#define CHUNK3DS_ID_POINTARRAY        ((ushort)0x4110)
#define CHUNK3DS_ID_FACEARRAY         ((ushort)0x4120)
#define CHUNK3DS_ID_MATGROUP          ((ushort)0x4130)
#define CHUNK3DS_ID_TEX_VERTS         ((ushort)0x4140)
#define CHUNK3DS_ID_SMOOTHGROUP       ((ushort)0x4150)
#define CHUNK3DS_ID_MESHMATRIX        ((ushort)0x4160)
#define CHUNK3DS_MAT_ENTRY            ((ushort)0xAFFF)
#define CHUNK3DS_MAT_NAME             ((ushort)0xA000)
#define CHUNK3DS_MAT_AMBIENT          ((ushort)0xA010)
#define CHUNK3DS_MAT_DIFFUSE          ((ushort)0xA020)
#define CHUNK3DS_MAT_SPECULAR         ((ushort)0xA030)
#define CHUNK3DS_MAT_SHININESS        ((ushort)0xA040)
#define CHUNK3DS_MAT_SHIN2PCT         ((ushort)0xA041)
#define CHUNK3DS_MAT_TRANSPARENCY     ((ushort)0xA050)
#define CHUNK3DS_MAT_XPFALL           ((ushort)0xA052)
#define CHUNK3DS_MAT_REFBLUR          ((ushort)0xA053)
#define CHUNK3DS_MAT_SHADING          ((ushort)0xA100)
#define CHUNK3DS_MAT_SELF_ILPCT       ((ushort)0xA084)
#define CHUNK3DS_MAT_XPFALLIN         ((ushort)0xA08A)
#define CHUNK3DS_MAT_WIRESIZE         ((ushort)0xA087)
#define CHUNK3DS_MAT_TEXMAP           ((ushort)0xA200)
#define CHUNK3DS_MAT_MAPNAME          ((ushort)0xA300)
#define CHUNK3DS_MAT_MAP_TILING       ((ushort)0xA351)
#define CHUNK3DS_MAT_MAP_TEXBLUR      ((ushort)0xA353)
#define CHUNK3DS_MAT_ENTRY            ((ushort)0xAFFF)
#define CHUNK3DS_ID_LAST              ((ushort)0xFFFF)


/* Holds information on the chunk types */
typedef struct {
	ushort ID;
	int Flags;
	const char *pName;
} chunk3ds_t;

/* Chunk stack record type */
typedef struct {
	ushort ID;
	long Offset;
} chunk3dsstack_t;


/*===========================================================================
 *
 * Begin Class C3dsFile Definition
 *
 * Handles simple Input/Output of 3DS type files.
 *
 *=========================================================================*/
class C3dsFile : public CGenFile {
  private:
	long m_MainChunkOffset; /* Keeps track of the chunk starting offsets */
	long m_EditChunkOffset;
	long m_ObjectChunkOffset;
	long m_TrimeshChunkOffset;
	long m_PointChunkOffset;
	long m_FaceChunkOffset;

	long m_MainChunkSize; /* Keeps track of the chunk sizes */
	long m_EditChunkSize;
	long m_ObjectChunkSize;
	long m_TrimeshChunkSize;
	long m_PointChunkSize;
	long m_FaceChunkSize;

	short m_NumFaces;
	short m_NumPoints;


	chunk3dsstack_t m_ChunkStack[CHUNK3DS_STACK_SIZE];
	int m_ChunkStackSize;


  protected:
	/* Helper function to dump chunks recursively */
	bool DumpChunk(FILE *pFileHandle);
	bool DumpMeshMatrix(FILE *pFileHandle);

	/* Helper input functions */
	bool ReadName(char *pBuffer);

	/* Chunk stack manipulation */
	bool PushChunkStack(const ushort ID);
	bool PopChunkStack(const ushort ID);
	bool PopChunkStack(const ushort ID, const short Value);


  public:
	/* Class Constructors/Destructors */
	//C3dsFile();
	//virtual ~C3dsFile() { Destroy(); }
	//virtual void Destroy (void);

	/* Create a translation mesh matrix */
	static void CreateMeshMatrix(float *pMeshMatrix,
	                             const float XPos,
	                             const float YPos,
	                             const float ZPos,
	                             const float XScale,
	                             const float YScale,
	                             const float ZScale,
	                             const float XAngle,
	                             const float YAngle,
	                             const float ZAngle);

	/* Dump the chunks found in the 3DS file */
	bool DumpContents(FILE *pFileHandle);

	/* End writing major chunk sections */
	bool EndMainChunk();
	bool EndEditChunk();
	bool EndObjectChunk();
	bool EndTrimeshChunk();
	bool EndFaceChunk();
	bool EndPointChunk();
	bool EndChunk(const ushort ID);
	bool EndMatGroupChunk();
	bool EndTexVertChunk(const short Count);

	/* Attempts to find a chunk info structure */
	static const char *GetChunkName(const ushort ChunkID);
	static int GetChunkFlag(const ushort ChunkID);
	static chunk3ds_t *FindChunk(const ushort ChunkID);

	/* Start writing major chunk sections */
	bool StartMainChunk();
	bool StartEditChunk();
	bool StartObjectChunk(const char *pName);
	bool StartTrimeshChunk();
	bool StartFaceChunk();
	bool StartPointChunk();
	bool StartChunk(const ushort ID);
	bool StartMatGroupChunk(const char *pMatName, const short Count);
	bool StartTexVertChunk();

	/* Output a standard material section */
	bool OutputMatEntry(const char *pMatName, const char *pTextureName);
	bool OutputMatEntry(const char *pMatName, const rgbpal_t &PalEntry);

	/* Write trimesh elements */
	bool WriteFace(const short Point1,
	               const short Point2,
	               const short Point3,
	               const short Flags = 0);
	bool WritePoint(const float X, const float Y, const float Z);
	bool WriteMeshMatrix(const float *pMeshMatrix = NULL);

	/* Standard output methods */
	bool WriteCharColor(const ushort ChunkID, const byte Red, const byte Green, const byte Blue);
	bool WriteIntPercent(const ushort ChunkID, const short Percentage);
	bool WriteIntPercent(const short Percentage);
	bool WriteChunkShort(const ushort ChunkID, const short Value);
	bool WriteChunkFloat(const ushort ChunkID, const float Value);
	bool WriteString(const ushort ChunkID, const char *pString);
	bool WriteTexVert(const float X, const float Y);
};


/* End outputting chunk sections */
inline bool C3dsFile::EndTexVertChunk(const short Count) {
	return PopChunkStack(CHUNK3DS_ID_TEX_VERTS, Count);
}

inline bool C3dsFile::EndEditChunk() {
	return PopChunkStack(CHUNK3DS_ID_EDIT);
}

inline bool C3dsFile::EndFaceChunk() {
	return PopChunkStack(CHUNK3DS_ID_FACEARRAY, m_NumFaces);
}

inline bool C3dsFile::EndMainChunk() {
	return PopChunkStack(CHUNK3DS_ID_MAIN);
}

inline bool C3dsFile::EndMatGroupChunk() {
	return PopChunkStack(CHUNK3DS_ID_MATGROUP);
}

inline bool C3dsFile::EndObjectChunk() {
	return PopChunkStack(CHUNK3DS_ID_NAMEDOBJECT);
}

inline bool C3dsFile::EndPointChunk() {
	return PopChunkStack(CHUNK3DS_ID_POINTARRAY, m_NumPoints);
}

inline bool C3dsFile::EndTrimeshChunk() {
	return PopChunkStack(CHUNK3DS_ID_TRIMESH);
}

/* Start/end arbitrary chunks */
inline bool C3dsFile::EndChunk(const ushort ID) {
	return PopChunkStack(ID);
}

inline bool C3dsFile::StartChunk(const ushort ID) {
	return PushChunkStack(ID);
}


#endif
