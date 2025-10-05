/*===========================================================================
 *
 * File:    TstFile.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Monday, May 07, 2001
 *
 * Tests the DL_FILE.CPP module.
 *
 *=========================================================================*/
#include "Common/dl_file.h"

#if !UNDER_CE
	#include <direct.h>
	#include <sys/stat.h>
	#include <io.h>
	#include <dos.h>
#endif

#include <limits.h>
#include <ctype.h>


DEFINE_FILE("tstfile.cpp");


/*===========================================================================
 *
 * Begin Module Test Routines
 *
 * Functions to test this module, available only in DEBUG builds.
 *
 *=========================================================================*/
#if _DEBUG


/*===========================================================================
 *
 * Function - void Test_ChangeDirectory (void);
 *
 * Test the ChangeDirectory() function.  Depending on the computer run
 * on, the test paths may need to be changed.
 *  1. Test with several valid paths, same disk
 *  2. Test with valid paths, different disks
 *  3. Test with invalid paths
 *  4. Test with empty path
 *
 *=========================================================================*/
void Test_ChangeDirectory() {
	DEFINE_FUNCTION("Test_ChangeDirectory()");
	TCHAR Buffer[256];
	SystemLog.Printf(stdout, _T("=============== Testing ChangeDirectory() ==================="));
	ChangeDirectory(_T("c:\\"));
	SystemLog.Printf(stdout, _T("c:\\ = %s"), GetDirString(Buffer, 200));

	/* Attempt to change paths within same disk */
	ASSERT(ChangeDirectory(_T("\\temp)")) == TRUE);
	SystemLog.Printf(stdout, _T("c:\\temp = %s"), GetDirString(Buffer, 200));
	ASSERT(ChangeDirectory(_T("\\")) == TRUE);
	SystemLog.Printf(stdout, _T("c:\\ = %s"), GetDirString(Buffer, 200));
	ASSERT(ChangeDirectory(_T("temp")) == TRUE);
	SystemLog.Printf(stdout, _T("c:\\temp = %s"), GetDirString(Buffer, 200));
	ASSERT(ChangeDirectory(_T("\\windows\\temp")) == TRUE);
	SystemLog.Printf(stdout, _T("c:\\windows\\temp = %s"), GetDirString(Buffer, 200));

	/* Change paths within different disks */
// ASSERT(ChangeDirectory(_T("d:\\temp")) == TRUE);
// SystemLog.Printf(stdout, _T("d:\\temp = %s"), getcwd(Buffer, 200));
	ASSERT(ChangeDirectory(_T("c:\\temp")) == TRUE);
	SystemLog.Printf(stdout, _T("c:\\temp = %s"), GetDirString(Buffer, 200));
// ASSERT(ChangeDirectory(_T("d:\\")) == TRUE);
// SystemLog.Printf(stdout, _T("d:\\ = %s"), getcwd(Buffer, 200));

	/* Change with invalid paths */
	ASSERT(ChangeDirectory(_T("c:\\1234")) == FALSE);
	ASSERT(ChangeDirectory(_T("\\taqgad")) == FALSE);

	/* Check empty path case */
	ASSERT(ChangeDirectory(_T("")) == FALSE);
}


/*===========================================================================
 *
 * Function - void Test_ChangeExtension (void);
 *
 * Tests the ChangeExtension() function
 *  1. Test with several typical strings
 *  2. Test with new extension with/without '.'
 *  3. Test with source file containing no extension
 *  4. Test case with short strings
 *
 *=========================================================================*/
void Test_ChangeExtension() {
	DEFINE_FUNCTION("Test_ChangeExtension()");
	TCHAR TestString[101];
	TCHAR DestString[101];
	SystemLog.Printf(stdout, _T("=============== Testing ChangeExtension() ==================="));

	/* Test typical inputs */
	TSTRCPY(TestString, _T("filename.ext"));
	ChangeExtension(DestString, TestString, _T("new"), 100);
	ASSERT(TSTRCMP(DestString, _T("filename.new")) == 0);
	TSTRCPY(TestString, _T("c:\\temp\\filename.1234567"));
	ChangeExtension(DestString, TestString, _T("new"), 100);
	ASSERT(TSTRCMP(DestString, _T("c:\\temp\\filename.new")) == 0);

	/* Test with new extension with '.' character */
	TSTRCPY(TestString, _T("filename"));
	ChangeExtension(DestString, TestString, _T(".new"), 100);
	ASSERT(TSTRCMP(DestString, _T("filename.new")) == 0);

	/* Test with source file containing no extension */
	TSTRCPY(TestString, _T("filename"));
	ChangeExtension(DestString, TestString, _T("new"), 100);
	ASSERT(TSTRCMP(DestString, _T("filename.new")) == 0);

	/* Test with several short string cases */
	TSTRCPY(TestString, _T("filename.123"));
	ChangeExtension(DestString, TestString, _T("new"), 8);
	ASSERT(TSTRCMP(DestString, _T("filename")) == 0);
	TSTRCPY(TestString, _T("filename.123"));
	ChangeExtension(DestString, TestString, _T("new"), 9);
	ASSERT(TSTRCMP(DestString, _T("filename.")) == 0);
	TSTRCPY(TestString, _T("filename.123"));
	ChangeExtension(DestString, TestString, _T("new"), 10);
	ASSERT(TSTRCMP(DestString, _T("filename.n")) == 0);
	TSTRCPY(TestString, _T("filename.123"));
	ChangeExtension(DestString, TestString, _T("new"), 11);
	ASSERT(TSTRCMP(DestString, _T("filename.ne")) == 0);
	TSTRCPY(TestString, _T("filename.123"));
	ChangeExtension(DestString, TestString, _T("new"), 12);
	ASSERT(TSTRCMP(DestString, _T("filename.new")) == 0);
	TSTRCPY(TestString, _T("filename.123"));
	ChangeExtension(DestString, TestString, _T(".new"), 12);
	ASSERT(TSTRCMP(DestString, _T("filename.new")) == 0);
	TSTRCPY(TestString, _T("filename.123"));
	ChangeExtension(DestString, TestString, _T("nw"), 12);
	ASSERT(TSTRCMP(DestString, _T("filename.nw")) == 0);
}


/*===========================================================================
 *
 * Function - void Test_CompareExtension (void);
 *
 * Tests the CompareExtension() and FindExtension() functions
 *  1. Tests for several TRUE cases (with/without case differences)
 *  2. Test several FALSE cases
 *  3. Test empty string case
 *  4. Test files with no extension
 *
 *=========================================================================*/
void Test_CompareExtension() {
	DEFINE_FUNCTION("Test_CompareExtension()");
	SystemLog.Printf(stdout, _T("=============== Testing CompareExtension() ==================="));

	/* Test several positive cases */
	ASSERT(CompareExtension(_T("file.ext"), _T("ext")) == TRUE);
	ASSERT(CompareExtension(_T("file.ext"), _T("EXT")) == TRUE);
	ASSERT(CompareExtension(_T("c:\\file.123456"), _T("123456")) == TRUE);
	ASSERT(CompareExtension(_T("c:\\temp\\file.ext"), _T("ext")) == TRUE);
	ASSERT(CompareExtension(_T("c:file.ext"), _T("ext")) == TRUE);
	ASSERT(CompareExtension(_T("c:\\temp.tmp\\file.ext"), _T("ext")) == TRUE);

	/* Test several negative cases */
	ASSERT(CompareExtension(_T("file.123"), _T("ext")) == FALSE);
	ASSERT(CompareExtension(_T("c:\\"), _T("ext")) == FALSE);
	ASSERT(CompareExtension(_T("c:"), _T("ext")) == FALSE);
	ASSERT(CompareExtension(_T("c:\\temp.ext\\"), _T("ext")) == FALSE);
	ASSERT(CompareExtension(_T("c:\\temp.123\\file.ext"), _T("123")) == FALSE);
	ASSERT(CompareExtension(_T("c:\\temp.ext\\"), _T("ext")) == FALSE);

	/* Test empty string cases */
	ASSERT(CompareExtension(_T(""), _T("ext")) == FALSE);
	ASSERT(CompareExtension(_T("file.ext"), _T("")) == FALSE);
	ASSERT(CompareExtension(_T(""), _T("")) == FALSE);

	/* Test file with no extension */
	ASSERT(CompareExtension(_T("filename"), _T("ext")) == FALSE);
	ASSERT(CompareExtension(_T("filename."), _T("ext")) == FALSE);
	ASSERT(CompareExtension(_T("c:\\temp\\filename"), _T("ext")) == FALSE);
	ASSERT(CompareExtension(_T("c:\\temp.ext\\file"), _T("ext")) == FALSE);
}


/*===========================================================================
 *
 * Function - void Test_CopyFile (void);
 *
 * Tests the CopyFile() function.
 *  1. Tests copy with file less than copy buffer size
 *  2. Tests copy with file exactly copy buffer size
 *  3. Tests copy with file greater than copy buffer size
 *  4. Test with zero sized file
 *  5. Test with invalid source file
 *  6. Test with invalid destination file
 *
 *=========================================================================*/
void Test_CopyFile() {
	DEFINE_FUNCTION("Test_CopyFile()");
	SystemLog.Printf(stdout, _T("=============== Testing CopyFile() ==================="));

	/* Test function with file size less than buffer size */
	SystemLog.Printf(stdout, _T("\tTest file size less than buffer size"));
	Test_CreateRandomFile(_T("c:\\temp\\test1.dat"), COPYFILE_BUFFERSIZE / 2);
	SystemLog.Printf(stdout, _T("\t\tWrote random file"));
	ASSERT(CopyOneFile(_T("c:\\temp\\test1.dat"), _T("c:\\temp\\test2.dat")));
	SystemLog.Printf(stdout, _T("\t\tCopied file"));
	ASSERT(Test_CompareFiles(_T("c:\\temp\\test1.dat"), _T("c:\\temp\\test2.dat")));

	/* Test function with file size equal to buffer size */
	SystemLog.Printf(stdout, _T("\tTest file size equal to buffer size"));
	Test_CreateRandomFile(_T("c:\\temp\\test1.dat"), COPYFILE_BUFFERSIZE);
	ASSERT(CopyOneFile(_T("c:\\temp\\test1.dat"), _T("c:\\temp\\test2.dat")));
	ASSERT(Test_CompareFiles(_T("c:\\temp\\test1.dat"), _T("c:\\temp\\test2.dat")));

	/* Test function with file size greater than buffer size */
	SystemLog.Printf(stdout, _T("\tTest file size greater than buffer size"));
	Test_CreateRandomFile(_T("c:\\temp\\test1.dat"), COPYFILE_BUFFERSIZE * 2);
	ASSERT(CopyOneFile(_T("c:\\temp\\test1.dat"), _T("c:\\temp\\test2.dat")));
	ASSERT(Test_CompareFiles(_T("c:\\temp\\test1.dat"), _T("c:\\temp\\test2.dat")));

	/* Test function with zero size file */
	SystemLog.Printf(stdout, _T("\tTest 0 file size"));
	Test_CreateRandomFile(_T("c:\\temp\\test1.dat"), 0);
	ASSERT(CopyOneFile(_T("c:\\temp\\test1.dat"), _T("c:\\temp\\test2.dat")));
	ASSERT(Test_CompareFiles(_T("c:\\temp\\test1.dat"), _T("c:\\temp\\test2.dat")));

	/* Test function with invalid source file */
	SystemLog.Printf(stdout, _T("\tTest invalid source file"));
	ASSERT(CopyOneFile(_T("c:\\temp\\test123.dat"), _T("c:\\temp\\test2.dat")) == FALSE);

	/* Test function with invalid destination file */
	SystemLog.Printf(stdout, _T("\tTest invalid destination file"));
	Test_CreateRandomFile(_T("c:\\temp\\test1.dat"), 100);
	ASSERT(CopyOneFile(_T("c:\\temp\\test1.dat"), _T("c:\\temp123\\test2.dat")) == FALSE);
}


/*===========================================================================
 *
 * Function - bool Test_CompareFiles (pFilename1, pFilename2);
 *
 * Helper function to compare two files.  Returns TRUE if the files are
 * identical.  ASSERTs on any error.
 *
 *=========================================================================*/
bool Test_CompareFiles(const TCHAR *pFilename1, const TCHAR *pFilename2) {
	DEFINE_FUNCTION("Test_CompareFiles()");
	FILE *pFileHandle1;
	FILE *pFileHandle2;
	bool ReturnValue = TRUE;
	ASSERT(pFilename1 != NULL && pFilename2 != NULL);
	/* Attempt to open both files for input */
	pFileHandle1 = TFOPEN(pFilename1, _T("rb"));
	pFileHandle2 = TFOPEN(pFilename2, _T("rb"));
	ASSERT(pFileHandle1 != NULL && pFileHandle2 != NULL);

	/* Compare each file, byte by byte */
	while (!feof(pFileHandle1) && !feof(pFileHandle2)) {
		if (fgetc(pFileHandle1) != fgetc(pFileHandle2)) {
			ReturnValue = FALSE;
			break;
		}

		ASSERT(ferror(pFileHandle1) == 0);
		ASSERT(ferror(pFileHandle2) == 0);
	}

	/* Ensure both files are the samesize */
	if (feof(pFileHandle1) != feof(pFileHandle2)) {
		ReturnValue = FALSE;
	}

	fclose(pFileHandle1);
	fclose(pFileHandle2);
	return ReturnValue;
}


/*===========================================================================
 *
 * Function - void Test_CreatePath (void);
 *
 * Tests the CreatePath() function.
 *  1. Test several typical inputs
 *  2. Test empty string
 *  3. Test short string cases
 *
 *=========================================================================*/
void Test_CreatePath() {
	DEFINE_FUNCTION("Test_CreatePath()");
	TCHAR TestString[101];
	SystemLog.Printf(stdout, _T("=============== Testing CreatePath() ===================)"));

	/* Test several typical inputs */
	CreatePath(TestString, _T("c:\\temp\\"), 100);
	ASSERT(TSTRCMP(TestString, _T("c:\\temp\\")) == 0);
	CreatePath(TestString, _T("c:\\temp"), 100);
	ASSERT(TSTRCMP(TestString, _T("c:\\temp\\")) == 0);
	CreatePath(TestString, _T("c:"), 100);
	ASSERT(TSTRCMP(TestString, _T("c:\\")) == 0);

	/* Test empty string case */
	CreatePath(TestString, _T(""), 100);
	ASSERT(TSTRCMP(TestString, _T("\\")) == 0);

	/* Test short string cases */
	CreatePath(TestString, _T("c:\\temp\\"), 6);
	ASSERT(TSTRCMP(TestString, _T("c:\\tem")) == 0);
	CreatePath(TestString, _T("c:\\temp\\"), 7);
	ASSERT(TSTRCMP(TestString, _T("c:\\temp")) == 0);
	CreatePath(TestString, _T("c:\\temp\\"), 8);
	ASSERT(TSTRCMP(TestString, _T("c:\\temp\\")) == 0);
	CreatePath(TestString, _T("c:\\temp"), 8);
	ASSERT(TSTRCMP(TestString, _T("c:\\temp\\")) == 0);
	CreatePath(TestString, _T("c:\\temp\\"), 9);
	ASSERT(TSTRCMP(TestString, _T("c:\\temp\\")) == 0);
}


/*===========================================================================
 *
 * Function - void Test_CreateRandomFile (pFilename, FileSize, TextMode);
 *
 * Helper function to create a random file with a given size.  ASSERTs on
 * any error.  File is overwritten if it previously existed.  Creates
 * a text or binary file depending on the value of the TextMode flag.
 *
 *=========================================================================*/
void Test_CreateRandomFile(const TCHAR *pFilename, const size_t FileSize, const bool TextMode) {
	DEFINE_FUNCTION("Test_CreateRandomFile()");
	FILE *pFileHandle;
	size_t LoopCounter;
	byte Char;
	int Result;
	ASSERT(pFilename != NULL);
	/* Attempt to open file for output */
	pFileHandle = TFOPEN(pFilename, TextMode ? _T("wt") : _T("wb"));
	ASSERT(pFileHandle != NULL);

	/* Create random text bytes to fill file */
	if (TextMode) {
		char RandChars[120] =
		    "\t `01234567890-=\\~!@#$%^&*()_+|qwertyuiop[]asdfghjkl;'zxcvbnm,./QWERTYUIOP{}ASDFGHJKL:\"ZXCVBNM<>?aa";

		for (LoopCounter = 0; LoopCounter < FileSize; LoopCounter++) {
			Char = RandChars[(byte)((float)rand() * 98 / RAND_MAX)];
			Result = fputc(Char, pFileHandle);
			ASSERT(Result != EOF);
		}
	}
	/* Create random binary bytes to fill file */
	else {
		for (LoopCounter = 0; LoopCounter < FileSize; LoopCounter++) {
			Char = (byte)((float)rand() * 256 / RAND_MAX);
			Result = fputc(Char, pFileHandle);
			ASSERT(Result != EOF);
		}
	}

	ASSERT(ferror(pFileHandle) == 0);
	fclose(pFileHandle);
}


/*===========================================================================
 *
 * Function - void Test_ExtractFilename (void);
 *
 * Tests the ExtractFilename() function.  This also indirectly tests the
 * FindFilename() function.
 *  1. Test with typical inputs
 *  2. Test with path without filenames
 *  3. Test with empty string
 *  4. Test with short strings
 *
 *=========================================================================*/
void Test_ExtractFilename() {
	DEFINE_FUNCTION("Test_ExtractFilename()");
	TCHAR TestString[101];
	SystemLog.Printf(stdout, _T("=============== Testing ExtractFilename() ==================="));

	/* Test several typical inputs */
	ExtractFilename(TestString, _T("c:\\temp\\filename.ext"), 100);
	ASSERT(TSTRCMP(TestString, _T("filename.ext")) == 0);
	ExtractFilename(TestString, _T("filename.ext"), 100);
	ASSERT(TSTRCMP(TestString, _T("filename.ext")) == 0);
	ExtractFilename(TestString, _T("c:filename.ext"), 100);
	ASSERT(TSTRCMP(TestString, _T("filename.ext")) == 0);

	/* Test with paths without filenames */
	ExtractFilename(TestString, _T("c:\\temp\\"), 100);
	ASSERT(TSTRCMP(TestString, _T("")) == 0);
	ExtractFilename(TestString, _T("c:"), 100);
	ASSERT(TSTRCMP(TestString, _T("")) == 0);

	/* Test with empty string */
	ExtractFilename(TestString, _T(""), 100);
	ASSERT(TSTRCMP(TestString, _T("")) == 0);

	/* Test with short strings */
	ExtractFilename(TestString, _T("c:\\temp\\filename.ext"), 8);
	ASSERT(TSTRCMP(TestString, _T("filename")) == 0);
	ExtractFilename(TestString, _T("filename.ext"), 4);
	ASSERT(TSTRCMP(TestString, _T("file")) == 0);
}


/*===========================================================================
 *
 * Function - void Test_ExtractPath (void);
 *
 * Tests the ExtractPath() function and, indirectly, the FindFilename()
 * function.
 *  1. Tests several typical inputs
 *  2. Test with no path in string
 *  3. Test with empty string
 *  4. Test with short strings
 *
 *=========================================================================*/
void Test_ExtractPath() {
	DEFINE_FUNCTION("Test_ExtractPath()");
	TCHAR TestString[101];
	SystemLog.Printf(stdout, _T("=============== Testing ExtractPath() ==================="));

	/* Test several typical inputs */
	ExtractPath(TestString, _T("c:\\temp\\filename.ext"), 100);
	ASSERT(TSTRCMP(TestString, _T("c:\\temp\\")) == 0);
	ExtractPath(TestString, _T("temp\\filename.ext"), 100);
	ASSERT(TSTRCMP(TestString, _T("temp\\")) == 0);
	ExtractPath(TestString, _T("c:\\temp\\"), 100);
	ASSERT(TSTRCMP(TestString, _T("c:\\temp\\")) == 0);
	ExtractPath(TestString, _T("c:\\temp"), 100);
	ASSERT(TSTRCMP(TestString, _T("c:\\")) == 0);
	ExtractPath(TestString, _T("c:temp\\file"), 100);
	ASSERT(TSTRCMP(TestString, _T("c:temp\\")) == 0);
	ExtractPath(TestString, _T("c:filename"), 100);
	ASSERT(TSTRCMP(TestString, _T("c:\\")) == 0);

	/* Test with no path in filename */
	ExtractPath(TestString, _T("filename"), 100);
	ASSERT(TSTRCMP(TestString, _T("\\")) == 0);

	/* Test with empty string */
	ExtractPath(TestString, _T(""), 100);
	ASSERT(TSTRCMP(TestString, _T("\\")) == 0);

	/* Test with short strings */
	ExtractPath(TestString, _T("c:\\temp\\filename.ext"), 8);
	ASSERT(TSTRCMP(TestString, _T("c:\\temp\\")) == 0);
	ExtractPath(TestString, _T("c:\\temp\\filename.ext"), 7);
	ASSERT(TSTRCMP(TestString, _T("c:\\")) == 0);
	ExtractPath(TestString, _T("c:\\temp\\filename.ext"), 3);
	ASSERT(TSTRCMP(TestString, _T("c:\\")) == 0);
	ExtractPath(TestString, _T("c:filename"), 3);
	ASSERT(TSTRCMP(TestString, _T("c:\\")) == 0);
	ExtractPath(TestString, _T("c:filename"), 2);
	ASSERT(TSTRCMP(TestString, _T("c:")) == 0);
}


/*===========================================================================
 *
 * Function - void Test_FileExists (void);
 *
 * Tests the FileExists() function.
 *  1. Test with valid files
 *  2. Test with invalid files
 *  3. Test with empty filename
 *
 *=========================================================================*/
void Test_FileExists() {
	DEFINE_FUNCTION("Test_FileExists()");
	SystemLog.Printf(stdout, _T("=============== Testing FileExists() ==================="));

	/* Check with valid files */
	Test_CreateRandomFile(_T("c:\\temp\\test1.dat"), 10);
	ASSERT(FileExists(_T("c:\\temp\\test1.dat")) == TRUE);

	/* Check with invalid files */
	ASSERT(FileExists(_T("c:\\temp\\test123.dat")) == FALSE);

	/* Check with empty file string */
	ASSERT(FileExists(_T("")) == FALSE);
}


/*===========================================================================
 *
 * Function - void Test_GetFileSize (void);
 *
 * Tests all the GetFileSize() functions.
 *  1. Test with several valid files
 *  2. Test with invalid files
 *  3. Test with empty file strings
 *  4. Test with zero-sized files
 *
 *=========================================================================*/
void Test_GetFileSize() {
	DEFINE_FUNCTION("Test_GetFileSize()");
	long FileSize;
	SystemLog.Printf(stdout, _T("=============== Testing GetFileSize() ==================="));

	/* Test with some valid files */
	Test_CreateRandomFile(_T("c:\\temp\\test1.dat"), 101);
	ASSERT(GetFileSize(FileSize, _T("c:\\temp\\test1.dat")) == TRUE);
	ASSERT(FileSize == 101);
	ASSERT(GetFileSize(_T("c:\\temp\\test1.dat")) == 101);

	/* Test with some invalid files */
	ASSERT(GetFileSize(FileSize, _T("c:\\temp\\test123.dat")) == FALSE);
	ASSERT(GetFileSize(_T("c:\\temp\\test123.dat")) == 0);

	/* Test with empty file strings */
	ASSERT(GetFileSize(FileSize, _T("")) == FALSE);
	ASSERT(GetFileSize(_T("")) == 0);

	/* Test with zero-sized files */
	Test_CreateRandomFile(_T("c:\\temp\\test1.dat"), 0);
	ASSERT(GetFileSize(FileSize, _T("c:\\temp\\test1.dat")) == TRUE);
	ASSERT(FileSize == 0);
	ASSERT(GetFileSize(_T("c:\\temp\\test1.dat")) == 0);
}


/*===========================================================================
 *
 * Function - void Test_HasExtension (void);
 *
 * Tests the HasExtension() function.
 *  1. Test with typical extensions in filename
 *  2. Test with no extensions in filename
 *  3. Test with NULL extensions in filename
 *  4. Test with empty string
 *
 *=========================================================================*/
void Test_HasExtension() {
	DEFINE_FUNCTION("Test_HasExtension()");
	SystemLog.Printf(stdout, _T("=============== Testing HasExtension() ==================="));

	/* Check with typical inputs */
	ASSERT(HasExtension(_T("c:\\temp\\filename.ext")) == TRUE);
	ASSERT(HasExtension(_T("filename.ext")) == TRUE);

	/* Check with filename without extensions */
	ASSERT(HasExtension(_T("c:\\temp\\filename")) == FALSE);
	ASSERT(HasExtension(_T("c:\\temp.123\\filename")) == FALSE);
	ASSERT(HasExtension(_T("c:\\temp.ext\\")) == FALSE);

	/* Test with blank extensions */
	ASSERT(HasExtension(_T("c:\\temp\\filename.")) == TRUE);
	ASSERT(HasExtension(_T(".")) == TRUE);

	/* Test with empty string */
	ASSERT(HasExtension(_T("")) == FALSE);
}


/*===========================================================================
 *
 * Function - void Test_HasPath (void);
 *
 * Tests the HasPath() function.
 *  1. Test with several typical filenames
 *  2. Test with filenames without paths
 *  3. Test with empty strings
 *
 *=========================================================================*/
void Test_HasPath() {
	DEFINE_FUNCTION("Test_HasPath()");
	SystemLog.Printf(stdout, _T("=============== Testing HasPath() ==================="));

	/* Check with typical inputs */
	ASSERT(HasPath(_T("c:\\temp\\filename.ext")) == TRUE);
	ASSERT(HasPath(_T("c:filename.ext")) == TRUE);
	ASSERT(HasPath(_T("temp\\file.ext")) == TRUE);
	ASSERT(HasPath(_T("c:\\filename.ext")) == TRUE);
	ASSERT(HasPath(_T("\\")) == TRUE);
	ASSERT(HasPath(_T(":")) == TRUE);

	/* Check with files without paths */
	ASSERT(HasPath(_T("filename.ext")) == FALSE);

	/* Check with empty strings */
	ASSERT(HasPath(_T("")) == FALSE);
}


/*===========================================================================
 *
 * Function - void Test_IsDirectory (void);
 *
 * Tests the IsDirectory() function.
 *  1. Test with valid paths
 *  2. Test with invalid paths
 *  3. Test with empty path
 *
 *=========================================================================*/
void Test_IsDirectory() {
	DEFINE_FUNCTION("Test_IsDirectory()");
	SystemLog.Printf(stdout, _T("=============== Testing IsDirectory() ==================="));

	/* Check several valid paths */
	ASSERT(IsDirectory(_T("c:\\")) == TRUE);
	ASSERT(IsDirectory(_T("c:")) == TRUE);
	ASSERT(IsDirectory(_T("c:\\temp")) == TRUE);
	ASSERT(IsDirectory(_T("c:\\temp\\")) == TRUE);
	ASSERT(IsDirectory(_T("\\")) == TRUE);
	ASSERT(IsDirectory(_T(".")) == TRUE);
	ASSERT(IsDirectory(_T("..")) == TRUE);

	/* Check several invalid paths */
	ASSERT(IsDirectory(_T("c:\\aadadad")) == FALSE);
	ASSERT(IsDirectory(_T("adadc:")) == FALSE);

	/* Check empty paths */
	ASSERT(IsDirectory(_T("")) == FALSE);
}


/*===========================================================================
 *
 * Function - void Test_IsFileWriteable (void);
 *
 * Tests the IsFileWriteable() function.
 *  1. Checks for several postive cases
 *  2. Checks for several negative cases
 *  3. Tests empty filename
 *
 *=========================================================================*/
void Test_IsFileWriteable() {
	DEFINE_FUNCTION("Test_IsFileWriteable()");
	SystemLog.Printf(stdout, _T("=============== Testing IsFileWriteable() ==================="));

	/* Check several TRUE cases */
	Test_CreateRandomFile(_T("c:\\temp\\test1.dat"), 101);
	ASSERT(IsFileWriteable(_T("c:\\temp\\test1.dat")) == TRUE);
	Test_CreateRandomFile(_T("c:\\temp\\test1.dat"), 0);
	ASSERT(IsFileWriteable(_T("c:\\temp\\test1.dat")) == TRUE);

	/* Test several FALSE cases */
	ASSERT(IsFileWriteable(_T("c:\\temp")) == FALSE);
	ASSERT(IsFileWriteable(_T("t1.2. \\34.txt")) == FALSE);
	Test_CreateRandomFile(_T("c:\\temp\\test1.dat"), 10);
	chmod(("c:\\temp\\test1.dat"), S_IREAD);
	ASSERT(IsFileWriteable(_T("c:\\temp\\test1.dat")) == FALSE);
	chmod(("c:\\temp\\test1.dat"), S_IWRITE | S_IREAD);

	/* Test empty string */
	ASSERT(IsFileWriteable(_T("")) == FALSE);
}


/*===========================================================================
 *
 * Function - void Test_IsWildCard (void);
 *
 * Tests the IsWildCard() function.
 *  1. Test for several typical strings with wildcards
 *  2. Test with string without wildcards
 *  3. Test with empty string
 *
 *=========================================================================*/
void Test_IsWildCard() {
	DEFINE_FUNCTION("Test_IsWildCard()");
	SystemLog.Printf(stdout, _T("=============== Testing IsWildCard() ==================="));

	/* Test for several positive cases */
	ASSERT(IsWildCard(_T("*.*")) == TRUE);
	ASSERT(IsWildCard(_T("test.???")) == TRUE);
	ASSERT(IsWildCard(_T("test?.txt")) == TRUE);
	ASSERT(IsWildCard(_T("*.tmp")) == TRUE);
	ASSERT(IsWildCard(_T("*")) == TRUE);
	ASSERT(IsWildCard(_T("?")) == TRUE);

	/* Test the negative case */
	ASSERT(IsWildCard(_T("test")) == FALSE);

	/* Test the empty string */
	ASSERT(IsWildCard(_T("")) == FALSE);
}


/*===========================================================================
 *
 * Function - void Test_OpenFile (void);
 *
 * Test the OpenFile() function.
 *  1. Test opening valid new files for output
 *  2. Test opening invalid new files for output
 *  3. Test opening valid files for reading
 *  4. Test opening invalid files for reading
 *  5. Test empty string filenames
 *
 *=========================================================================*/
void Test_OpenFile(void) {
	DEFINE_FUNCTION("Test_OpenFile()");
	FILE *pFileHandle;
	SystemLog.Printf(stdout, _T("=============== Testing OpenFile() ==================="));

	/* Check opening valid files for output */
	ASSERT(OpenFile(&pFileHandle, _T("c:\\temp\\test1.dat"), _T("wt")) == TRUE);
	ASSERT(pFileHandle != NULL);
	fclose(pFileHandle);

	/* Check opening invalid files for output */
	ASSERT(OpenFile(&pFileHandle, _T("c:\\temp\\te:-/st1.dat"), _T("wt")) == FALSE);
	ASSERT(pFileHandle == NULL);

	/* Check opening valid files for input */
	Test_CreateRandomFile(_T("c:\\temp\\temp1.dat"), 101);
	ASSERT(OpenFile(&pFileHandle, _T("c:\\temp\\test1.dat"), _T("rb")) == TRUE);
	ASSERT(pFileHandle != NULL);
	fclose(pFileHandle);

	/* Check opening invalid files for input */
	ASSERT(OpenFile(&pFileHandle, _T("c:\\temp\\test123.dat"), _T("rb")) == FALSE);
	ASSERT(pFileHandle == NULL);

	/* Check empty file string */
	ASSERT(OpenFile(&pFileHandle, _T(""), _T("rb")) == FALSE);
	ASSERT(pFileHandle == NULL);

	/* Check invalid mode strings */
	ASSERT(OpenFile(&pFileHandle, _T("c:\\temp\\test1.dat"), _T("")) == FALSE);
	ASSERT(pFileHandle == NULL);
	ASSERT(OpenFile(&pFileHandle, _T("c:\\temp\\test1.dat"), _T("hhhh")) == FALSE);
	ASSERT(pFileHandle == NULL);
}


/*===========================================================================
 *
 * Function - void Test_ReadFile (void);
 *
 * Test the ReadFile() function.
 *  1. Test reading sample file, ensuring success
 *  2. Test reading invalid file
 *  3. Test reading zero sized file
 *
 *=========================================================================*/
void Test_ReadFile() {
	DEFINE_FUNCTION("Test_ReadFile()");
	FILE *pFileHandle;
	byte *pTestPtr;
	size_t FileSize;
	SystemLog.Printf(stdout, _T("=============== Testing ReadFile() ==================="));

	/* Test reading a sample file */
	Test_CreateRandomFile(_T("c:\\temp\\test1.dat"), 101);
	ASSERT(ReadFile(&pTestPtr, FileSize, _T("c:\\temp\\test1.dat")) == TRUE);
	ASSERT(pTestPtr != NULL);
	ASSERT(FileSize == 101);
	pFileHandle = TFOPEN(_T("c:\\temp\\test2.dat"), _T("wb"));
	ASSERT(pFileHandle != NULL);
	ASSERT(fwrite(pTestPtr, 1, 101, pFileHandle) == 101);
	fclose(pFileHandle);
	ASSERT(Test_CompareFiles(_T("c:\\temp\\test1.dat"), _T("c:\\temp\\test2.dat")) == TRUE);
	DestroyPointer(pTestPtr);

	/* Test reading an invalid file */
	ASSERT(ReadFile(&pTestPtr, FileSize, _T("c:\\tata.rzr")) == NULL);
	ASSERT(pTestPtr == NULL);

	/* Test reading a zero sized file */
	Test_CreateRandomFile(_T("c:\\temp\\test1.dat"), 0);
	ASSERT(ReadFile(&pTestPtr, FileSize, _T("c:\\temp\\test1.dat")) == TRUE);
	ASSERT(pTestPtr != NULL);
	ASSERT(FileSize == 0);
	DestroyPointer(pTestPtr);
}


/*===========================================================================
 *
 * Function - void Test_ReadFileBuffer (void);
 *
 * Test the ReadFileBuffer() function.
 *  1. Test reading sample file, ensuring success
 *  2. Test reading invalid file
 *  3. Test reading zero sized file
 *  4. Test reading a file exactly the same size as buffer
 *  5. Test reading a file bigger than buffer size
 *
 *=========================================================================*/
void Test_ReadFileBuffer() {
	DEFINE_FUNCTION("Test_ReadFileBuffer()");
	FILE *pFileHandle;
	byte *pTestPtr;
	size_t FileSize;
	SystemLog.Printf(stdout, _T("=============== Testing ReadFileBuffer() ==================="));

	/* Test reading a sample file */
	Test_CreateRandomFile(_T("c:\\temp\\test1.dat"), 101);
	CreateArrayPointer(pTestPtr, byte, 1001);
	ASSERT(pTestPtr != NULL);
	ASSERT(ReadFileBuffer(&pTestPtr, FileSize, _T("c:\\temp\\test1.dat"), 1000) == TRUE);
	ASSERT(pTestPtr != NULL);
	ASSERT(FileSize == 101);
	pFileHandle = TFOPEN(_T("c:\\temp\\test2.dat"), _T("wb"));
	ASSERT(pFileHandle != NULL);
	ASSERT(fwrite(pTestPtr, 1, 101, pFileHandle) == 101);
	fclose(pFileHandle);
	ASSERT(Test_CompareFiles(_T("c:\\temp\\test1.dat"), _T("c:\\temp\\test2.dat")) == TRUE);

	/* Test reading an invalid file */
	ASSERT(ReadFileBuffer(&pTestPtr, FileSize, _T("c:\\tata.rzr"), 1000) == NULL);
	ASSERT(FileSize == 0);

	/* Test reading a zero sized file */
	Test_CreateRandomFile(_T("c:\\temp\\test1.dat"), 0);
	ASSERT(ReadFileBuffer(&pTestPtr, FileSize, _T("c:\\temp\\test1.dat"), 1000) == TRUE);
	ASSERT(FileSize == 0);

	/* Test reading a sample file exactly the same size as buffer */
	Test_CreateRandomFile(_T("c:\\temp\\test1.dat"), 1000);
	ASSERT(ReadFileBuffer(&pTestPtr, FileSize, _T("c:\\temp\\test1.dat"), 1000) == TRUE);
	ASSERT(FileSize == 1000);

	/* Test reading a sample file bigger than buffer */
	Test_CreateRandomFile(_T("c:\\temp\\test1.dat"), 1100);
	ASSERT(ReadFileBuffer(&pTestPtr, FileSize, _T("c:\\temp\\test1.dat"), 1000) == TRUE);
	ASSERT(FileSize == 1000);
	DestroyPointer(pTestPtr);
}


/*===========================================================================
 *
 * Function - void Test_ReadLine (void);
 *
 * Tests the ReadLine() function
 *  1. Test reading in regular lines
 *  2. Test reading in short lines
 *  3. Test reading with NULL string buffer
 *  4. Test eof condition
 *  5. Test error condition
 *
 *=========================================================================*/
void Test_ReadLine() {
	DEFINE_FUNCTION("Test_ReadLine()");
	TCHAR TestString[101];
	FILE *pFileHandle;
	SystemLog.Printf(stdout, _T("=============== Testing ReadLine() ==================="));

	/* Create a sample test file */
	pFileHandle = TFOPEN(_T("c:\\temp\\test1.txt"), _T("wb"));
	ASSERT(pFileHandle != NULL);
	fprintf(pFileHandle, ("This is line 1\n"));
	fprintf(pFileHandle, ("This is line 2\n"));
	fprintf(pFileHandle, ("This is line 3333333333333333333333\n"));
	fprintf(pFileHandle, ("This is line 4\n"));
	fprintf(pFileHandle, ("\n"));
	fclose(pFileHandle);

	/* Open the sample test file */
	pFileHandle = TFOPEN(_T("c:\\temp\\test1.txt"), _T("rb"));
	ASSERT(pFileHandle != NULL);

	/* Input regular lines */
	ASSERT(ReadLine(pFileHandle, TestString, 100) == READLINE_OK);
	ASSERT(TSTRCMP(TestString, _T("This is line 1")) == 0);
	ASSERT(ReadLine(pFileHandle, TestString, 100) == READLINE_OK);
	ASSERT(TSTRCMP(TestString, _T("This is line 2")) == 0);

	/* Test reading a short line */
	ASSERT(ReadLine(pFileHandle, TestString, 4) == READLINE_MSL);
	ASSERT(TSTRCMP(TestString, _T("This")) == 0);
	ASSERT(ReadLine(pFileHandle, TestString, 8) == READLINE_MSL);
	ASSERT(TSTRCMP(TestString, _T(" is line")) == 0);

	/* Test reading with NULL string buffer*/
	ASSERT(ReadLine(pFileHandle) == READLINE_OK);
	ASSERT(ReadLine(pFileHandle) == READLINE_OK);

	/* Test the EOF condition */
	ASSERT(ReadLine(pFileHandle, TestString, 100) == READLINE_OK);
	ASSERT(TSTRCMP(TestString, _T("")) == 0);
	ASSERT(ReadLine(pFileHandle, TestString, 100) == READLINE_EOF);
	ASSERT(TSTRCMP(TestString, _T("")) == 0);
	fclose(pFileHandle);

	/* Test the error condition */
	pFileHandle = TFOPEN(_T("c:\\temp\\test1.txt"), _T("wb"));
	ASSERT(ReadLine(pFileHandle, TestString, 100) == READLINE_ERROR);
	fclose(pFileHandle);
}


/*===========================================================================
 *
 * Function - void Test_read_int (void);
 *
 * Tests the read_int() and write_int() functions.
 *  1. Output/input various integers, ensuring success
 *  2. Test error conditions
 *
 *=========================================================================*/
void Test_read_int() {
	DEFINE_FUNCTION("Test_read_int()");
	FILE *pFileHandle;
	int TestValue;
	SystemLog.Printf(stdout,
	                 _T("=============== Testing read_int() / write_int() ==================="));

	/* Output some sample integers */
	pFileHandle = TFOPEN(_T("c:\\temp\\test1.dat"), _T("wb"));
	ASSERT(pFileHandle != NULL);
	ASSERT(write_int(pFileHandle, 0) == TRUE);
	ASSERT(write_int(pFileHandle, 101) == TRUE);
	ASSERT(write_int(pFileHandle, 1) == TRUE);
	ASSERT(write_int(pFileHandle, -1) == TRUE);
	ASSERT(write_int(pFileHandle, INT_MAX) == TRUE);
	ASSERT(write_int(pFileHandle, INT_MIN) == TRUE);
	fclose(pFileHandle);

	/* Input the sample integers */
	pFileHandle = TFOPEN(_T("c:\\temp\\test1.dat"), _T("rb"));
	ASSERT(pFileHandle != NULL);
	ASSERT(read_int(pFileHandle, TestValue) == TRUE);
	ASSERT(TestValue == 0);
	ASSERT(read_int(pFileHandle, TestValue) == TRUE);
	ASSERT(TestValue == 101);
	ASSERT(read_int(pFileHandle, TestValue) == TRUE);
	ASSERT(TestValue == 1);
	ASSERT(read_int(pFileHandle, TestValue) == TRUE);
	ASSERT(TestValue == -1);
	ASSERT(read_int(pFileHandle, TestValue) == TRUE);
	ASSERT(TestValue == INT_MAX);
	ASSERT(read_int(pFileHandle, TestValue) == TRUE);
	ASSERT(TestValue == INT_MIN);

	/* Test error condition */
	ASSERT(read_int(pFileHandle, TestValue) == FALSE);
	ASSERT(write_int(pFileHandle, 0) == FALSE);
	fclose(pFileHandle);
}


/*===========================================================================
 *
 * Function - void Test_read_long (void);
 *
 * Tests the read_long() and write_long() functions.
 *  1. Output/inputs sample values, ensuring success.
 *  2. Test error conditions
 *
 *=========================================================================*/
void Test_read_long() {
	DEFINE_FUNCTION("Test_read_long()");
	FILE *pFileHandle;
	long TestValue;
	SystemLog.Printf(stdout,
	                 _T("=============== Testing read_long() / write_long() ==================="));

	/* Output some sample integers */
	pFileHandle = TFOPEN(_T("c:\\temp\\test1.dat"), _T("wb"));
	ASSERT(pFileHandle != NULL);
	ASSERT(write_long(pFileHandle, 0) == TRUE);
	ASSERT(write_long(pFileHandle, 101) == TRUE);
	ASSERT(write_long(pFileHandle, 1) == TRUE);
	ASSERT(write_long(pFileHandle, -1) == TRUE);
	ASSERT(write_long(pFileHandle, LONG_MAX) == TRUE);
	ASSERT(write_long(pFileHandle, LONG_MIN) == TRUE);
	fclose(pFileHandle);

	/* Input the sample integers */
	pFileHandle = TFOPEN(_T("c:\\temp\\test1.dat"), _T("rb"));
	ASSERT(pFileHandle != NULL);
	ASSERT(read_long(pFileHandle, TestValue) == TRUE);
	ASSERT(TestValue == 0);
	ASSERT(read_long(pFileHandle, TestValue) == TRUE);
	ASSERT(TestValue == 101);
	ASSERT(read_long(pFileHandle, TestValue) == TRUE);
	ASSERT(TestValue == 1);
	ASSERT(read_long(pFileHandle, TestValue) == TRUE);
	ASSERT(TestValue == -1);
	ASSERT(read_long(pFileHandle, TestValue) == TRUE);
	ASSERT(TestValue == LONG_MAX);
	ASSERT(read_long(pFileHandle, TestValue) == TRUE);
	ASSERT(TestValue == LONG_MIN);

	/* Test error condition */
	ASSERT(read_long(pFileHandle, TestValue) == FALSE);
	ASSERT(write_long(pFileHandle, 0) == FALSE);
	fclose(pFileHandle);
}


/*===========================================================================
 *
 * Function - void Test_read_short (void);
 *
 * Tests the read_short() and write_short() functions.
 *  1. Output/inputs sample values, ensuring success.
 *  2. Test error conditions
 *
 *=========================================================================*/
void Test_read_short() {
	DEFINE_FUNCTION("Test_read_short()");
	FILE *pFileHandle;
	short TestValue;
	SystemLog.Printf(stdout,
	                 _T("=============== Testing read_short() / write_short() ==================="));

	/* Output some sample integers */
	pFileHandle = TFOPEN(_T("c:\\temp\\test1.dat"), _T("wb"));
	ASSERT(pFileHandle != NULL);
	ASSERT(write_short(pFileHandle, 0) == TRUE);
	ASSERT(write_short(pFileHandle, 101) == TRUE);
	ASSERT(write_short(pFileHandle, 1) == TRUE);
	ASSERT(write_short(pFileHandle, -1) == TRUE);
	ASSERT(write_short(pFileHandle, SHRT_MAX) == TRUE);
	ASSERT(write_short(pFileHandle, SHRT_MIN) == TRUE);
	fclose(pFileHandle);

	/* Input the sample integers */
	pFileHandle = TFOPEN(_T("c:\\temp\\test1.dat"), _T("rb"));
	ASSERT(pFileHandle != NULL);
	ASSERT(read_short(pFileHandle, TestValue) == TRUE);
	ASSERT(TestValue == 0);
	ASSERT(read_short(pFileHandle, TestValue) == TRUE);
	ASSERT(TestValue == 101);
	ASSERT(read_short(pFileHandle, TestValue) == TRUE);
	ASSERT(TestValue == 1);
	ASSERT(read_short(pFileHandle, TestValue) == TRUE);
	ASSERT(TestValue == -1);
	ASSERT(read_short(pFileHandle, TestValue) == TRUE);
	ASSERT(TestValue == SHRT_MAX);
	ASSERT(read_short(pFileHandle, TestValue) == TRUE);
	ASSERT(TestValue == SHRT_MIN);

	/* Test error condition */
	ASSERT(read_short(pFileHandle, TestValue) == FALSE);
	ASSERT(write_short(pFileHandle, 0) == FALSE);
	fclose(pFileHandle);
}


/*===========================================================================
 *
 * Function - void Test_read_motlong (void);
 *
 * Tests the read_motlong() and write_motlong() functions
 *  1. Output/inputs sample values, ensuring success.
 *  2. Test error conditions
 *
 *=========================================================================*/
void Test_read_motlong() {
	DEFINE_FUNCTION("Test_read_motlong()");
	FILE *pFileHandle;
	long TestValue;
	SystemLog.Printf(stdout,
	                 _T("=============== Testing read_motlong() / write_motlong() ==================="));

	/* Output some sample integers */
	pFileHandle = TFOPEN(_T("c:\\temp\\test1.dat"), _T("wb"));
	ASSERT(pFileHandle != NULL);
	ASSERT(write_motlong(pFileHandle, 0) == TRUE);
	ASSERT(write_motlong(pFileHandle, 101) == TRUE);
	ASSERT(write_motlong(pFileHandle, 1) == TRUE);
	ASSERT(write_motlong(pFileHandle, -1) == TRUE);
	ASSERT(write_motlong(pFileHandle, LONG_MAX) == TRUE);
	ASSERT(write_motlong(pFileHandle, LONG_MIN) == TRUE);
	fclose(pFileHandle);

	/* Input the sample integers */
	pFileHandle = TFOPEN(_T("c:\\temp\\test1.dat"), _T("rb"));
	ASSERT(pFileHandle != NULL);
	ASSERT(read_motlong(pFileHandle, TestValue) == TRUE);
	ASSERT(TestValue == 0);
	ASSERT(read_motlong(pFileHandle, TestValue) == TRUE);
	ASSERT(TestValue == 101);
	ASSERT(read_motlong(pFileHandle, TestValue) == TRUE);
	ASSERT(TestValue == 1);
	ASSERT(read_motlong(pFileHandle, TestValue) == TRUE);
	ASSERT(TestValue == -1);
	ASSERT(read_motlong(pFileHandle, TestValue) == TRUE);
	ASSERT(TestValue == LONG_MAX);
	ASSERT(read_motlong(pFileHandle, TestValue) == TRUE);
	ASSERT(TestValue == LONG_MIN);

	/* Test error condition */
	ASSERT(read_long(pFileHandle, TestValue) == FALSE);
	ASSERT(write_motlong(pFileHandle, 0) == FALSE);
	fclose(pFileHandle);
}


/*===========================================================================
 *
 * Function - void Test_RemoveExtension (void);
 *
 * Tests the RemoveExtension() function.  The function is also indirectly
 * tested by the ChangeExtension() function.
 *  1. Test several typical cases
 *  2. Test with filename without extension
 *  3. Test with empty string
 *
 *=========================================================================*/
void Test_RemoveExtension() {
	DEFINE_FUNCTION("Test_RemoveExtension()");
	TCHAR TestString[101];
	SystemLog.Printf(stdout, _T("=============== Testing RemoveExtension() ==================="));

	/* Test several typical cases */
	TSTRCPY(TestString, _T("filename.ext"));
	RemoveExtension(TestString);
	ASSERT(TSTRCMP(TestString, _T("filename")) == 0);
	TSTRCPY(TestString, _T("c:\\temp\\filename.ext"));
	RemoveExtension(TestString);
	ASSERT(TSTRCMP(TestString, _T("c:\\temp\\filename")) == 0);
	TSTRCPY(TestString, _T("temp.123\\filename.1234567"));
	RemoveExtension(TestString);
	ASSERT(TSTRCMP(TestString, _T("temp.123\\filename")) == 0);
	TSTRCPY(TestString, _T("filename."));
	RemoveExtension(TestString);
	ASSERT(TSTRCMP(TestString, _T("filename")) == 0);

	/* Test with no extension */
	TSTRCPY(TestString, _T("temp.123\\filename"));
	RemoveExtension(TestString);
	ASSERT(TSTRCMP(TestString, _T("temp.123\\filename")) == 0);
	TSTRCPY(TestString, _T("filename"));
	RemoveExtension(TestString);
	ASSERT(TSTRCMP(TestString, _T("filename")) == 0);

	/* Test empty string case */
	TSTRCPY(TestString, _T(""));
	RemoveExtension(TestString);
	ASSERT(TSTRCMP(TestString, _T("")) == 0);
}


/*===========================================================================
 *
 * Function - void Test_RWFile (NumTests);
 *
 * Tests the ReadFile() / ReadFileBuffer() / WriteFile() functions a number
 * of times with random sized files.  Tests both binary and text mode inputs.
 *  - Creates a randomly sized binary file (up to TEST_RWFILE_MAXFILESIZE)
 *  - Reads file, writes to new file, and compares the two files
 *  - Similarly tests with a randomly sized text file
 *
 *=========================================================================*/
void Test_RWFile(const size_t NumTests) {
	DEFINE_FUNCTION("Test_RWFile()");
	size_t LoopCounter;
	size_t FileSize;
	size_t BytesRead;
	byte *pInputBuffer;
	byte *pBuffer;
	size_t BufferSize = TEST_RWFILE_MAXFILESIZE / 2;
	SystemLog.Printf(stdout,
	                 _T("=============== Repeated Testing of ReadFile() / WriteFile() ==================="));
	CreateArrayPointer(pBuffer, byte, BufferSize);

	for (LoopCounter = 0; LoopCounter < NumTests; LoopCounter++) {
		/* Text randomly sized binary file */
		FileSize = (size_t)((float)rand() * TEST_RWFILE_MAXFILESIZE / RAND_MAX);
		Test_CreateRandomFile(_T("c:\\temp\\test1.dat"), FileSize, FILE_BINARY);
		SystemLog.Printf(stdout, _T("\t%d) Testing %u byte file..."), LoopCounter, FileSize);
		ASSERT(ReadFile(&pInputBuffer, BytesRead, _T("c:\\temp\\test1.dat"), FILE_BINARY) == TRUE);
		ASSERT(BytesRead == FileSize);
		ASSERT(WriteFile(pInputBuffer, BytesRead, _T("c:\\temp\\test2.dat"), FILE_BINARY) == TRUE);
		ASSERT(Test_CompareFiles(_T("c:\\temp\\test1.dat"), _T("c:\\temp\\test2.dat")) == TRUE);
		ASSERT(ReadFileBuffer(&pBuffer,
		                      BytesRead,
		                      _T("c:\\temp\\test1.dat"),
		                      BufferSize,
		                      FILE_BINARY) == TRUE);
		ASSERT(BytesRead <= FileSize);
		ASSERT(BytesRead <= BufferSize);
		ASSERT(pInputBuffer != NULL);
		ASSERT(pBuffer != NULL);
		DestroyPointer(pInputBuffer);

		/* Test a randomly created text file */
		Test_CreateRandomFile(_T("c:\\temp\\test1.dat"), FileSize, FILE_TEXT);
		ASSERT(ReadFile(&pInputBuffer, BytesRead, _T("c:\\temp\\test1.dat"), FILE_TEXT) == TRUE);
		ASSERT(pInputBuffer != NULL);
		ASSERT(BytesRead <= FileSize);
		ASSERT(WriteFile(pInputBuffer, BytesRead, _T("c:\\temp\\test2.dat"), FILE_TEXT) == TRUE);
		ASSERT(Test_CompareFiles(_T("c:\\temp\\test1.dat"), _T("c:\\temp\\test2.dat")) == TRUE);
///*
		ASSERT(ReadFileBuffer(&pBuffer,
		                      BytesRead,
		                      _T("c:\\temp\\test1.dat"),
		                      BufferSize,
		                      FILE_TEXT) == TRUE);
		ASSERT(pBuffer != NULL);
		ASSERT(BytesRead <= FileSize);
		ASSERT(BytesRead <= BufferSize); //*/
		DestroyPointer(pInputBuffer); //*/
	}

	DestroyArrayPointer(pBuffer);
}


/*===========================================================================
 *
 * Function - void Test_RWNumbers (NumTests);
 *
 * Repeatedly tests the read/write int/short/long/motlong type functions.
 *
 *=========================================================================*/
void Test_RWNumbers(const size_t NumTests) {
	DEFINE_FUNCTION("Test_RWNumbers()");
	size_t LoopCounter;
	FILE *pFileHandle;
	long *pLongArray;
	long InputLong;
	short *pShortArray;
	short InputShort;
	int *pIntArray;
	int InputInt;
	SystemLog.Printf(stdout,
	                 _T("=============== Repeated Testing of the read/write integer functions ==============="));

	/* Create number arrays */
	CreateArrayPointer(pLongArray, long, NumTests);
	CreateArrayPointer(pIntArray, int, NumTests);
	CreateArrayPointer(pShortArray, short, NumTests);

	/* Generate random numbers, outtputing them to a file */
	pFileHandle = TFOPEN(_T("c:\\temp\\test1.dat"), _T("wb"));
	ASSERT(pFileHandle != NULL);

	for (LoopCounter = 0; LoopCounter < NumTests; LoopCounter++) {
		if (LoopCounter % 10 == 0) {
			SystemLog.Printf(stdout, _T("\t\tWriting test %u of %u..."), LoopCounter, NumTests);
		}

		pLongArray[LoopCounter] = (long)rand() * (long)rand();
		pIntArray[LoopCounter] = (int)rand() * (int)rand();
		pShortArray[LoopCounter] = (short)rand();
		ASSERT(write_long(pFileHandle, pLongArray[LoopCounter]) == TRUE);
		ASSERT(write_motlong(pFileHandle, pLongArray[LoopCounter]) == TRUE);
		ASSERT(write_int(pFileHandle, pIntArray[LoopCounter]) == TRUE);
		ASSERT(write_short(pFileHandle, pShortArray[LoopCounter]) == TRUE);
	}

	fclose(pFileHandle);
	/* Input the random numbers, ensure success */
	pFileHandle = TFOPEN(_T("c:\\temp\\test1.dat"), _T("rb"));
	ASSERT(pFileHandle != NULL);

	for (LoopCounter = 0; LoopCounter < NumTests; LoopCounter++) {
		if (LoopCounter % 10 == 0) {
			SystemLog.Printf(stdout, _T("\t\tReading test %u of %u..."), LoopCounter, NumTests);
		}

		ASSERT(read_long(pFileHandle, InputLong) == TRUE);
		ASSERT(pLongArray[LoopCounter] == InputLong);
		ASSERT(read_motlong(pFileHandle, InputLong) == TRUE);
		ASSERT(pLongArray[LoopCounter] == InputLong);
		ASSERT(read_int(pFileHandle, InputInt) == TRUE);
		ASSERT(pIntArray[LoopCounter] == InputInt);
		ASSERT(read_short(pFileHandle, InputShort) == TRUE);
		ASSERT(pShortArray[LoopCounter] == InputShort);
	}

	fclose(pFileHandle);
	/* Delete allocated arrays */
	DestroyArrayPointer(pLongArray);
	DestroyArrayPointer(pIntArray);
	DestroyArrayPointer(pShortArray);
}


/*===========================================================================
 *
 * Function - void Test_TerminatePath (void);
 *
 * Tests the TerminatePath() function.  Assumes the LocalePathChar == '\\'
 *  1. Test several typical path strings
 *  2. Test empty string
 *
 *=========================================================================*/
void Test_TerminatePath() {
	DEFINE_FUNCTION("Test_TerminatePath()");
	TCHAR TestString[101];
	SystemLog.Printf(stdout, _T("=============== Testing TerminatePath() ==================="));

	/* Test typical path inputs */
	TSTRCPY(TestString, _T("c:\\temp\\"));
	TerminatePath(TestString);
	ASSERT(TSTRCMP(TestString, _T("c:\\temp\\")) == 0);
	TSTRCPY(TestString, _T("c:\\temp"));
	TerminatePath(TestString);
	ASSERT(TSTRCMP(TestString, _T("c:\\temp\\")) == 0);

	/* Test empty path input */
	TSTRCPY(TestString, _T(""));
	TerminatePath(TestString);
	ASSERT(TSTRCMP(TestString, _T("\\")) == 0);
}


/*===========================================================================
 *
 * Function - void Test_WriteFile (void);
 *
 * Tests the WriteFile() function.
 *  1. Tests outputting a sample file, ensuring success
 *  2. Test outputting a zero sized file
 *  3. Test outputting an invalid file
 *
 *=========================================================================*/
void Test_WriteFile() {
	DEFINE_FUNCTION("Test_WriteFile()");
	byte TestString[101];
	byte InputString[101];
	FILE *pFileHandle;
	SystemLog.Printf(stdout, _T("=============== Testing WriteFile() ==================="));

	/* Output a test file */
	memcpy(TestString, "0123456789", 11);
	ASSERT(WriteFile((byte *)TestString, 11, _T("c:\\temp\\test1.dat")) == TRUE);
	pFileHandle = TFOPEN(_T("c:\\temp\\test1.dat"), _T("rb"));
	ASSERT(pFileHandle != NULL);
	ASSERT(fread((byte *)InputString, 1, 11, pFileHandle) == 11);
	fclose(pFileHandle);
	ASSERT(memcmp(TestString, InputString, 11) == 0);

	/* Output a zero-sized file */
	ASSERT(WriteFile(TestString, 0, _T("c:\\temp\\test1.dat")) == TRUE);
	ASSERT(FileExists(_T("c:\\temp\\test1.dat")) == TRUE);

	/* Test outputting an invalid file */
	ASSERT(WriteFile(TestString, 10, _T("c:\\temp123\\tes.t1.dat")) == FALSE);
}


/*===========================================================================
 *
 * Function - void Test_WildcardCompare (void);
 *
 * Tests the WildcardCompare() function.
 *  1. Test exact match (case sensitive and insensitive)
 *  2. Test non matches
 *  3. Test blank/null strings
 *  4. Test positive matches using ? wildcard
 *  5. Test negative matches using ? wildcard
 *  6. Test positive matches using * wildcard
 *  7. Test negative matches using * wildcard
 *  8. Test *? combination wildcards
 *
 *=========================================================================*/
void Test_WildcardCompare() {
	DEFINE_FUNCTION("Test_WildcardCompare()");
	bool Result;
	SystemLog.Printf(stdout, _T("=============== Testing WildcardCompare() ==================="));

	/* Test exact match with/without case differences */
	Result = WildcardCompare(_T("test.txt"), _T("test.txt"));
	ASSERT(Result);
	Result = WildcardCompare(_T("TEST.txt"), _T("test.txt"));
	ASSERT(Result);
	Result = WildcardCompare(_T("test.txt"), _T("TEST.txt"));
	ASSERT(Result);

	/* Test non-matches */
	Result = WildcardCompare(_T("123456"), _T("aaaaa"));
	ASSERT(!Result);
	Result = WildcardCompare(_T("aa"), _T("bb"));
	ASSERT(!Result);

	/* Test blank/null strings */
	Result = WildcardCompare(_T(""), _T(""));
	ASSERT(Result);
	Result = WildcardCompare(NULL, _T(""));
	ASSERT(Result);
	Result = WildcardCompare(_T(""), NULL);
	ASSERT(Result);
	Result = WildcardCompare(NULL, NULL);
	ASSERT(Result);

	/* Test positive ? wildcards */
	Result = WildcardCompare(_T("123456"), _T("123?56"));
	ASSERT(Result);
	Result = WildcardCompare(_T("123456"), _T("12??56"));
	ASSERT(Result);
	Result = WildcardCompare(_T("123456"), _T("?2??56"));
	ASSERT(Result);
	Result = WildcardCompare(_T("123456"), _T("????56"));
	ASSERT(Result);
	Result = WildcardCompare(_T("123456"), _T("????5?"));
	ASSERT(Result);
	Result = WildcardCompare(_T("123456"), _T("??????"));
	ASSERT(Result);
	Result = WildcardCompare(_T("123456"), _T("123456?"));
	ASSERT(Result);

	/* Test negative ? wildcards */
	Result = WildcardCompare(_T("12345"), _T("123456?"));
	ASSERT(!Result);
	Result = WildcardCompare(_T("12345"), _T("123?456"));
	ASSERT(!Result);
	Result = WildcardCompare(_T("12345"), _T("?123456"));
	ASSERT(!Result);
	Result = WildcardCompare(_T(""), _T("?"));
	ASSERT(!Result);

	/* Test positive * wildcards */
	Result = WildcardCompare(_T("123456"), _T("123*"));
	ASSERT(Result);
	Result = WildcardCompare(_T("123456"), _T("*456"));
	ASSERT(Result);
	Result = WildcardCompare(_T("123456"), _T("1*6"));
	ASSERT(Result);
	Result = WildcardCompare(_T("123456"), _T("*"));
	ASSERT(Result);
	Result = WildcardCompare(_T("123456"), _T("**"));
	ASSERT(Result);
	Result = WildcardCompare(_T("123456"), _T("*4*"));
	ASSERT(Result);
	Result = WildcardCompare(_T(""), _T("*"));
	ASSERT(Result);

	/* Test negative * wildcards */
	Result = WildcardCompare(_T("123456"), _T("123*7"));
	ASSERT(!Result);
	Result = WildcardCompare(_T("123456"), _T("*7"));
	ASSERT(!Result);
	Result = WildcardCompare(_T("123456"), _T("7*"));
	ASSERT(!Result);
	Result = WildcardCompare(_T("123456"), _T("*X*"));
	ASSERT(!Result);
	Result = WildcardCompare(_T("123456"), _T("125*"));
	ASSERT(!Result);

	/* Test combination *? wildcards */
	Result = WildcardCompare(_T("123456"), _T("*4??"));
	ASSERT(Result);
	Result = WildcardCompare(_T("123456"), _T("*7??"));
	ASSERT(!Result);
	Result = WildcardCompare(_T("123456"), _T("?2*6"));
	ASSERT(Result);
	Result = WildcardCompare(_T("123456"), _T("?2*69"));
	ASSERT(!Result);
	Result = WildcardCompare(_T("123456"), _T("??*?"));
	ASSERT(Result);
	Result = WildcardCompare(_T("123456"), _T("?*?"));
	ASSERT(Result);
	Result = WildcardCompare(_T("123456"), _T("*?"));
	ASSERT(Result);
}


/*===========================================================================
 *
 * Function - void Test_DL_File (void);
 *
 * Tests all functions in this module.
 *  1. Tests ChangeDirectory()
 *  2. Test the CompareExtension() / FindExtension() functions
 *  3. Test the CopyFile() function
 *  4. Test the ChangeExtension() function
 *  5. Test the RemoveExtension() function
 *  6. Test the CreatePath() function
 *  7. Test the ExtractFilename() / FindFilename() functions
 *  8. Test the ExtractPath() function
 *  9. Test the FileExists() function
 *  10.Test the GetFileSize() functions
 *  11.Test the HasExtension() function
 *  12.Test the HasPath() function
 *  13.Test the IsDirectory() function
 *  14.Test the IsFileWriteable() function
 *  15.Test the IsWildCard() function
 *  16.Test the OpenFile() function
 *  17.Test the ReadFile() and ReadFileBuffer() functions
 *  18.Test the ReadLine() function
 *  19.Test the TerminatePath() function
 *  20.Tests all the read/write_int/short/long/motlong functions
 *  21.Test the WriteFile() function
 *
 *=========================================================================*/
void Test_DL_File() {
	//DEFINE_FUNCTION("Test_DL_File()");
	/* Ensure randomly generated numbers */
	//srand(clock());
	//Test_ChangeDirectory();
	Test_ChangeExtension();
	Test_CompareExtension();
	Test_CopyFile();
	Test_CreatePath();
	Test_ExtractFilename();
	Test_ExtractPath();
	Test_FileExists();
	Test_GetFileSize();
	Test_HasExtension();
	Test_HasPath();
	Test_IsDirectory();
	Test_IsFileWriteable();
	Test_IsWildCard();
	Test_OpenFile();
	Test_ReadFile();
	Test_ReadFileBuffer();
	Test_read_int();
	Test_ReadLine();
	Test_read_long();
	Test_read_motlong();
	Test_read_short();
	Test_RemoveExtension();
	Test_TerminatePath();
	Test_WriteFile();
	Test_RWFile();
	Test_RWNumbers();
	Test_WildcardCompare();
}


#endif
