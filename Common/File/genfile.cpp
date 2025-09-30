/*===========================================================================
 *
 * File:    GenFile.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Thursday, May 17, 2001
 *
 * Implements the CGenFile class which handles simple file stream I/O
 * operations.
 *
 *=========================================================================*/
#include "file\genfile.h"


DEFINE_FILE("GenFile.cpp");


/*===========================================================================
 *
 * Begin Module Test Routines
 *
 *=========================================================================*/
#if _DEBUG
#include "dl_math.h"


/*===========================================================================
 *
 * Function - void Test_GenFileOpen (void);
 *
 * Tests the Open() method.
 *  1. Test the constructor open version with valid/invalid inputs
 *  2. Test the Open() method with a variety of inputs
 *  3. Also indirectly tests the Close() method and destructor
 *
 *=========================================================================*/
void Test_GenFileOpen() {
	DEFINE_FUNCTION("Test_GenFileOpen()");
	SystemLog.Printf(stdout, "================= Testing Open Method of CGenFile ================");
	Test_CreateRandomFile ("c:\\temp\\test1.dat", 10, FILE_BINARY);

	/* Test the constructor open version */
	CGenFile File1("c:\\temp\\test1.dat", "rb");
	CGenFile File2("c:\\tempxyt\\test1.dat", "rb");
	CGenFile File3("", "wb");
	CGenFile File4("c:\\temp\\test2.dat", "wb");
	CGenFile File5("c:\\temp\\t- =asasd&*!@#()$*.. . . .est2.dat", "wb");
	CGenFile File6("c:\\temp\\test1.dat", "");
	ASSERT(File1.IsOpen() == TRUE);
	ASSERT(File2.IsOpen() == FALSE);
	ASSERT(File3.IsOpen() == FALSE);
	ASSERT(File4.IsOpen() == TRUE);
	ASSERT(File5.IsOpen() == FALSE);
	ASSERT(File6.IsOpen() == FALSE);

	/* Test the open method with a variety of inputs */
	ASSERT(File1.Open("c:\\temp\\test1.dat", "rb") == TRUE);
	ASSERT(File2.Open("c:\\tempxyt\\test1.dat", "rb") == FALSE);
	ASSERT(File3.Open("", "wb") == FALSE);
	ASSERT(File4.Open("c:\\temp\\test2.dat", "wb") == TRUE);
	ASSERT(File5.Open("c:\\temp\\t- =asasd&*!@#()$*.. . . .est2.dat", "wb") == FALSE);
	ASSERT(File6.Open("c:\\temp\\test1.dat", "") == FALSE);
}


/*===========================================================================
 *
 * Function - void Test_GenFilePrint (void);
 *
 * Tests the Printf() and VPrintf() methods.
 *  1. Test with typical inputs
 *
 *=========================================================================*/
void Test_GenFilePrint() {
	DEFINE_FUNCTION("Test_GenFilePrint()");
	CGenFile File1("c:\\temp\\test1.dat", "wt");
	SystemLog.Printf(stdout,
	                 "================= Testing Printf/VPrintf Methods of CGenFile ================");
	ASSERT(File1.IsOpen());

	/* Test with typical inputs */
	ASSERT(File1.Printf("Testing with no vars") == TRUE);
	ASSERT(File1.Printf("Next string is blank") == TRUE);
	ASSERT(File1.Printf("") == TRUE);
	ASSERT(File1.Printf("Testing with one vars, 101 = %d", 101) == TRUE);
	ASSERT(File1.Printf("Testing with two vars, 123 = %s, 2.222e22=%f", "123", 2.222e22) == TRUE);
	ASSERT(File1.IsEOF() == FALSE);
	ASSERT(File1.IsError() == FALSE);
}


/*===========================================================================
 *
 * Function - void Test_GenFileSeekTell (NumTests);
 *
 * Repeatedly tests the Seek/Tell/Rewind methods.
 *  1. Randomly seeks to a valid file position
 *  2. Ensure the seek/tell positions match
 *  3. Attempt to seek to an invalid position
 *  4. Ensure the position has not changed
 *  5. Test the Rewind() method and ensure Tell returns 0
 *
 *=========================================================================*/
void Test_GenFileSeekTell(const size_t NumTests) {
	DEFINE_FUNCTION("Test_GenFileSeekTell()");
	size_t LoopCounter;
	filepos_t FilePos;
	filepos_t FilePos1;
	filepos_t TellPos;
	CGenFile TestFile;
	SystemLog.Printf(stdout,
	                 "================= Testing Seek/Tell/Rewind Method of CGenFile ================");
	Test_CreateRandomFile("c:\\temp\\test1.dat", TEST_GENFILE_SEEKFILESIZE, FILE_BINARY);
	ASSERT(TestFile.Open("c:\\temp\\test1.dat", "rb") == TRUE);
	RandomizeTimer();

	/* Repeat each test a number of times */
	for (LoopCounter = 0; LoopCounter < NumTests; LoopCounter++) {
		SystemLog.Printf(stdout, "\t%u of %u Tell/Seek/Rewind test", LoopCounter + 1, NumTests);
		FilePos = (filepos_t)Random(TEST_GENFILE_SEEKFILESIZE);
		FilePos1 = FilePos - TEST_GENFILE_SEEKFILESIZE / 2;

		/* Seek to valid file positions and test with Tell */
		ASSERT(TestFile.Seek(-FilePos, SEEK_END) == TRUE);
		ASSERT(TestFile.Tell(TellPos) == TRUE);
		ASSERT(TellPos == TEST_GENFILE_SEEKFILESIZE - FilePos);
		ASSERT(TestFile.Seek(TEST_GENFILE_SEEKFILESIZE / 2, SEEK_SET) == TRUE);
		ASSERT(TestFile.Seek(FilePos1, SEEK_CUR) == TRUE);
		ASSERT(TestFile.Tell(TellPos) == TRUE);
		ASSERT(TellPos == TEST_GENFILE_SEEKFILESIZE / 2 + FilePos1);
		ASSERT(TestFile.Seek(FilePos, SEEK_SET) == TRUE);
		ASSERT(TestFile.Tell(TellPos) == TRUE);
		ASSERT(TellPos == FilePos);
		ASSERT(TestFile.IsEOF() == FALSE);
		ASSERT(TestFile.IsError() == FALSE);

		/* Attempt seeking to invalid positions */
		ASSERT(TestFile.Seek(-1, SEEK_SET) == FALSE);
		ASSERT(TestFile.Tell(TellPos) == TRUE);
		ASSERT(TellPos == FilePos);
		ASSERT(TestFile.Seek(TEST_GENFILE_SEEKFILESIZE * 2, SEEK_CUR) == TRUE);
		ASSERT(TestFile.Tell(TellPos) == TRUE);
		ASSERT(TestFile.IsEOF() == FALSE);
		ASSERT(TestFile.IsError() == FALSE);
		ASSERT(TestFile.Seek(10000, SEEK_END) == TRUE);
		ASSERT(TestFile.Tell(TellPos) == TRUE);
		ASSERT(TestFile.IsEOF() == FALSE);
		ASSERT(TestFile.IsError() == FALSE);
		ASSERT(TellPos == TEST_GENFILE_SEEKFILESIZE + 10000);

		/* Test the rewind method */
		TestFile.Rewind();
		ASSERT(TestFile.Tell(TellPos) == TRUE);
		ASSERT(TellPos == 0);
		ASSERT(TestFile.IsError() == FALSE);
		ASSERT(TestFile.IsEOF() == FALSE);
	}
}


/*===========================================================================
 *
 * Function - void Test_RWGenFile (NumTests);
 *
 * Repeatedly tests the Read/Write routines on randomly sized files.
 *
 *=========================================================================*/
void Test_RWGenFile(const size_t NumTests) {
	DEFINE_FUNCTION("Test_RWGenFile()");
	CGenFile InputFile;
	CGenFile OutputFile;
	size_t FileSize;
	size_t LoopCounter;
	size_t BytesIO;
	char *pBuffer;
	char IOChar;
	SystemLog.Printf(stdout,
	                 "================= Testing Read/Write Methods of CGenFile ================");
	RandomizeTimer();
	pBuffer = CreateString(TEST_RWFILE_MAXFILESIZE);

	/* Perform each test a number of times */
	for (LoopCounter = 0; LoopCounter < NumTests; LoopCounter++) {
		/* Create randomly sized file */
		FileSize = Random((int)TEST_RWFILE_MAXFILESIZE);
		SystemLog.Printf(stdout, "\t%u) Testing file with size %u...", LoopCounter + 1, FileSize);
		Test_CreateRandomFile ("c:\\temp\\test1.dat", FileSize, FILE_BINARY);

		/* Attempt to open and read file */
		ASSERT(InputFile.Open("c:\\temp\\test1.dat", "rb") == TRUE);
		ASSERT(InputFile.Read(pBuffer, BytesIO, FileSize) == TRUE);
		ASSERT(BytesIO == FileSize);
		ASSERT(InputFile.IsError() == FALSE);
		ASSERT(InputFile.IsEOF() == FALSE);
		ASSERT(InputFile.ReadChar(IOChar) == FALSE);
		ASSERT(InputFile.IsEOF() == TRUE);
		ASSERT(InputFile.IsError() == FALSE);
		InputFile.Close();

		/* Attempt to open and write file */
		ASSERT(OutputFile.Open("c:\\temp\\test2.dat", "wb") == TRUE);
		ASSERT(OutputFile.Write(pBuffer, BytesIO, FileSize) == TRUE);
		ASSERT(BytesIO == FileSize);
		ASSERT(OutputFile.IsError() == FALSE);
		OutputFile.Close();

		/* Attempt to open and read file */
		ASSERT(InputFile.Open("c:\\temp\\test2.dat", "rb") == TRUE);
		ASSERT(InputFile.Read(pBuffer, FileSize) == TRUE);
		ASSERT(InputFile.IsError() == FALSE);
		ASSERT(InputFile.IsEOF() == FALSE);
		ASSERT(InputFile.ReadChar(IOChar) == FALSE);
		ASSERT(InputFile.IsEOF() == TRUE);
		ASSERT(InputFile.IsError() == FALSE);
		InputFile.Close();

		/* Attempt to open and write file */
		ASSERT(OutputFile.Open("c:\\temp\\test3.dat", "wb") == TRUE);
		ASSERT(OutputFile.Write(pBuffer, FileSize) == TRUE);
		ASSERT(OutputFile.IsError() == FALSE);
		OutputFile.Close();

		/* Ensure the files were successfully read and output */
		ASSERT(Test_CompareFiles("c:\\temp\\test1.dat", "c:\\temp\\test2.dat") == TRUE);
		ASSERT(Test_CompareFiles("c:\\temp\\test1.dat", "c:\\temp\\test3.dat") == TRUE);
	}

	DestroyArrayPointer(pBuffer);
}


/*===========================================================================
 *
 * Function - void Test_RWCharGenFile (NumTests);
 *
 * Repeatedly tests the ReadChar() and WriteChar() methods
 *
 *=========================================================================*/
void Test_RWCharGenFile(const size_t NumTests) {
	DEFINE_FUNCTION("Test_RWCharGenFile()");
	CGenFile InputFile;
	CGenFile OutputFile;
	size_t FileSize;
	size_t LoopCounter;
	size_t IOCounter;
	char IOChar;
	SystemLog.Printf(stdout,
	                 "================= Testing ReadChar/WriteChar Methods of CGenFile ================");
	RandomizeTimer();

	for (LoopCounter = 0; LoopCounter < NumTests; LoopCounter++) {
		/* Create randomly sized file */
		FileSize = Random((int)TEST_RWFILE_MAXFILESIZE);
		SystemLog.Printf(stdout, "\t%u) Testing file with size %u...", LoopCounter + 1, FileSize);
		Test_CreateRandomFile ("c:\\temp\\test1.dat", FileSize, FILE_BINARY);
		/* Open input/output files */
		ASSERT(InputFile.Open("c:\\temp\\test1.dat", "rb") == TRUE);
		ASSERT(OutputFile.Open("c:\\temp\\test2.dat", "wb") == TRUE);

		/* Copy the file, byte by byte */
		for (IOCounter = 0; IOCounter < FileSize; IOCounter++) {
			ASSERT(InputFile.ReadChar(IOChar) == TRUE);
			ASSERT(OutputFile.WriteChar(IOChar) == TRUE);
		}

		/* Check file status */
		ASSERT(InputFile.IsError() == FALSE);
		ASSERT(InputFile.IsEOF() == FALSE);
		ASSERT(InputFile.ReadChar(IOChar) == FALSE);
		ASSERT(InputFile.IsError() == FALSE);
		ASSERT(InputFile.IsEOF() == TRUE);
		ASSERT(OutputFile.IsError() == FALSE);
		ASSERT(OutputFile.IsEOF() == FALSE);
		InputFile.Close();
		OutputFile.Close();
		/* Ensure the files were successfully read and output */
		ASSERT(Test_CompareFiles("c:\\temp\\test1.dat", "c:\\temp\\test2.dat") == TRUE);
	}
}


/*===========================================================================
 *
 * Function - void Test_GenFileRWNumbers (NumTests);
 *
 * Repeatedly tests the Read/Write Int/Short/Long/Float methods.
 *
 *=========================================================================*/

#define OUTPUTSET(Array, Function) NumCounter = 0; while (TRUE) { \
		ASSERT(OutputFile.Function(Array[NumCounter])); if (Array[NumCounter] == 0) break; NumCounter++; }

#define INPUTSET(Array, Input, Function) NumCounter = 0; while (TRUE) { \
		ASSERT(InputFile.Read##Function(Input)); ASSERT(Input == Array[NumCounter]); ASSERT(OutputFile.Write##Function(Input)); if (Array[NumCounter] == 0) break; NumCounter++; }


void Test_GenFileRWNumbers(const size_t NumTests) {
	DEFINE_FUNCTION("Test_GenFileRWNumbers()");
	static short ShortNumbers[] = {
		1,
		-1,
		SHRT_MIN,
		SHRT_MAX,
		(short)USHRT_MAX,
		0,
		0
	};
	static int IntNumbers[] = {
		1,
		-1,
		INT_MIN,
		INT_MAX,
		(int)UINT_MAX,
		0,
		0
	};
	static long LongNumbers[] = {
		1,
		-1,
		LONG_MIN,
		LONG_MAX,
		(long)ULONG_MAX,
		0,
		0
	};
	static float FloatNumbers[] = {
		1,
		-1,
		SHRT_MIN,
		SHRT_MAX,
		USHRT_MAX,
		0,
		0
	};

	CGenFile InputFile;
	CGenFile OutputFile;
	size_t NumCounter;
	size_t TestCounter;
	ulong RandomSeed;
	size_t NumRandomNumbers;
	short InputShort, OutputShort;
	int InputInt, OutputInt;
	long InputLong, OutputLong;
	float InputFloat, OutputFloat;
	SystemLog.Printf(stdout,
	                 "================= Testing Read/Write Number Methods of CGenFile ================");
	RandomizeTimer();

	/* Main test loop, create random file and duplicate */
	for (TestCounter = 0; TestCounter < NumTests; TestCounter++) {
		ASSERT(OutputFile.Open ("c:\\temp\\gfnum1.dat", "wb"));
		SystemLog.Printf(stdout, "\t%4d) Testing...", TestCounter + 1);
		RandomSeed = Random((ulong)0x7FFFFFFFul);
		NumRandomNumbers = Random((int)TEST_GENFILE_RWNUMSIZE);
		SeedRandom(RandomSeed);

		/* Output set numbers */
		OUTPUTSET(ShortNumbers, WriteShort);
		OUTPUTSET(IntNumbers, WriteInt);
		OUTPUTSET(LongNumbers, WriteLong);
		OUTPUTSET(FloatNumbers, WriteFloat);

		/* Output random numbers */
		for (NumCounter = 0; NumCounter < NumRandomNumbers; NumCounter++) {
			OutputShort = (short)Random((ulong) USHRT_MAX);
			OutputInt = (int)Random((ulong)UINT_MAX);
			OutputLong = (long)Random();
			OutputFloat = (float)(Random() / (Random() * 0.8 + 1));
			ASSERT(OutputFile.WriteShort(OutputShort));
			ASSERT(OutputFile.WriteInt(OutputInt));
			ASSERT(OutputFile.WriteLong(OutputLong));
			ASSERT(OutputFile.WriteFloat(OutputFloat));
		}

		/* Reopen file for input */
		OutputFile.Close();
		ASSERT(InputFile.Open("c:\\temp\\gfnum1.dat", "rb"));
		ASSERT(OutputFile.Open("c:\\temp\\gfnum2.dat", "wb"));
		SeedRandom(RandomSeed);

		/* Input and verify set numbers */
		INPUTSET(ShortNumbers, InputShort, Short);
		INPUTSET(IntNumbers, InputInt, Int);
		INPUTSET(LongNumbers, InputLong, Long);
		INPUTSET(FloatNumbers, InputFloat, Float);

		/* Input and verify random numbers */
		for (NumCounter = 0; NumCounter < NumRandomNumbers; NumCounter++) {
			OutputShort = (short)Random((ulong) USHRT_MAX);
			OutputInt = (int)Random((ulong)UINT_MAX);
			OutputLong = (long)Random();
			OutputFloat = (float)(Random() / (Random() * 0.8 + 1));
			ASSERT(InputFile.ReadShort(InputShort));
			ASSERT(InputFile.ReadInt(InputInt));
			ASSERT(InputFile.ReadLong(InputLong));
			ASSERT(InputFile.ReadFloat(InputFloat));
			ASSERT(InputShort == OutputShort);
			ASSERT(InputInt == OutputInt);
			ASSERT(InputLong == OutputLong);
			ASSERT(InputFloat == OutputFloat);
			ASSERT(OutputFile.WriteShort(InputShort));
			ASSERT(OutputFile.WriteInt(InputInt));
			ASSERT(OutputFile.WriteLong(InputLong));
			ASSERT(OutputFile.WriteFloat(InputFloat));
		}

		InputFile.Close();
		OutputFile.Close();
		/* Ensure the files were successfully read and output */
		ASSERT(Test_CompareFiles("c:\\temp\\gfnum1.dat", "c:\\temp\\gfnum2.dat") == TRUE);
	}
}


/*===========================================================================
 *
 * Function - void Test_GenFile (void);
 *
 * Tests the CGenFile class.
 *  1. Repeatedly tests the Read/Write methods
 *  2. Repeatedly tests the ReadChar/WriteChar methods
 *  3. Tests the Open() Method
 *  4. Repeatedly tests the Read/Write number methods
 *
 *=========================================================================*/
void Test_GenFile() {
	//DEFINE_FUNCTION("Test_GenFile()");
	Test_GenFileOpen();
	Test_GenFilePrint();
	Test_GenFileSeekTell();
	Test_RWGenFile();
	Test_RWCharGenFile();
	Test_GenFileRWNumbers();
}

#endif
