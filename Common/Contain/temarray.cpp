/*===========================================================================
 *
 * File:    TemArray.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Friday, May 11, 2001
 *
 * Implements the TTemplateArray template for handling a simple array
 * of typed pointers.
 *
 *=========================================================================*/
#include "Common/Contain/temarray.h"


DEFINE_FILE("TemArray.cpp");


/*===========================================================================
 *
 * Begin Module Test Routines
 *
 *=========================================================================*/
#if _DEBUG
#include <float.h>
#include <time.h>
#include <string.h>

/* Test structure used for testing */
typedef struct {
	int Number;
	char Message[32];
	long lNumber;
} testdata_t;

/* Test type definitions */
typedef TTemplateArray<testdata_t> CTestDataArray;
typedef TTemplateArray<char> CPCharArray;


/*===========================================================================
 *
 * Function - void Test_StressTemplateArray (NumTests);
 *
 * Runs a stress test of the TTemplateArray class a number of times,
 * attempting to 'force' an error of some sort.  For each tests, a
 * random number of random sized strings are added to two char* arrays.
 *
 *=========================================================================*/
void Test_StressTemplateArray(const size_t NumTests) {
	DEFINE_FUNCTION("Test_StressTemplateArray()");
	CPCharArray StringArray1(100);
	size_t LoopCounter;
	size_t LoopCounter1;
	size_t NumAllocs;
	size_t TestSize;
	SystemLog.Printf(stdout,
	                 "================ Stressing the TTemplateArray Class ====================");
	srand((size_t)time(NULL));
	ErrorHandler.ClearErrors();
	ErrorDatabase.ClearErrors();
	OutputBlockInfo();

	for (LoopCounter = 0; LoopCounter < NumTests; LoopCounter++) {
		/* Create a random sized array */
		TestSize = (size_t)((float)rand() * 100000l / RAND_MAX) + 1;
		CPCharArray StringArray2(TestSize, 0);
		NumAllocs = (size_t)((float)rand() * 1100 / RAND_MAX) + 1;
		SystemLog.Printf(stdout,
		                 "\t%u) Adding %u random sized strings...",
		                 LoopCounter,
		                 NumAllocs);

		/* Add random sized strings */
		for (LoopCounter1 = 0; LoopCounter1 < NumAllocs; LoopCounter1++) {
			TestSize = (size_t)((float)rand() * 24000 / RAND_MAX);
			StringArray1.AddElement(CreateString(TestSize));
			StringArray2.AddElement(CreateString(TestSize));

			/* Run the DeleteElement() method */
			if ((rand() % 4) == 0) {
				StringArray1.DeleteElement((int)((float)rand() * (StringArray1.GetNumElements() - 1) / RAND_MAX));
				StringArray2.DeleteElement((int)((float)rand() * (StringArray2.GetNumElements() - 1) / RAND_MAX));
			}
			/* Run the FreeExtra() method */
			else if ((rand() % 10) == 0) {
				StringArray1.FreeExtra();
			}
		}

		/* Delete allocated memory */
		StringArray2.AssertValid();
		StringArray1.AssertValid();
		StringArray2.Destroy();
		StringArray1.Destroy();
		ErrorHandler.ClearErrors();
		ASSERT(DebugHeapCheckMemory());
		OutputBlockInfo();
	}
}


/*===========================================================================
 *
 * Function - void Test_TemplateArray (void);
 *
 * Tests the TTemplateArray class.
 *  1. Tests construction with typical sample templates
 *  2. Test the GetMaxElements() and GetNumElements() methods
 *  3. Test the AddElement() method
 *  4. Test the GetElement() method
 *  5. Test the [] operator
 *  6. Test the DeleteElement() method
 *  7. Test th Destroy() method
 *  8. Test the IsValidIndex() method
 *  9. Test the class destructor
 *  10. Test the SetGrowSize() method
 *  11. Test the FreeExtra() method

 *
 *=========================================================================*/
void Test_TemplateArray() {
	DEFINE_FUNCTION("Test_TemplateArray()");
	long *pTestInt;
	char *pTestPtr;
	testdata_t *pTestData;
	SystemLog.Printf(stdout, "================ Testing the TTemplateArray Class ====================");

	/* Test construction of sample templates */
	TTemplateArray<long> IntArray(100);
	TTemplateArray<char> StringArray2(2, 0);
	TTemplateArray<char> StringArray(2, 0);
	CTestDataArray TestDataArray(1, 10);

	/* Test the GetMaxElements() method */
	ASSERT(IntArray.GetMaxElements() == 100);
	ASSERT(StringArray.GetMaxElements() == 2);
	ASSERT(TestDataArray.GetMaxElements() == 1);

	/* Test the GetNumElements() methods */
	ASSERT(IntArray.GetNumElements() == 0);
	ASSERT(StringArray.GetNumElements() == 0);
	ASSERT(TestDataArray.GetNumElements() == 0);

	/* Test the AddElement() method */
	CreatePointer(pTestInt, (long)(12345678l));
	ASSERT(IntArray.AddElement(pTestInt) == TRUE);
	CreatePointer(pTestInt, (long)(22345678l));
	ASSERT(IntArray.AddElement(pTestInt) == TRUE);
	CreatePointer(pTestInt, (long)(32345678l));
	ASSERT(IntArray.AddElement(pTestInt) == TRUE);
	ASSERT(StringArray.AddElement(CreateString("Test String #1")) == TRUE);
	ASSERT(StringArray.AddElement(CreateString("Test String #2")) == TRUE);
	pTestPtr = CreateString("Invalid element String");
	ASSERT(StringArray.AddElement(pTestPtr) == FALSE);
	DestroyArrayPointer(pTestPtr);
	CreatePointer(pTestData, testdata_t);
	pTestData->Number = 123;
	pTestData->lNumber = 222222l;
	strcpy(pTestData->Message, "Test Message");
	ASSERT(TestDataArray.AddElement(pTestData) == TRUE);

	/* Test the GetNumElements() methods */
	ASSERT(IntArray.GetNumElements() == 3);
	ASSERT(StringArray.GetNumElements() == 2);
	ASSERT(TestDataArray.GetNumElements() == 1);

	/* Test the IsValidIndex() method */
	ASSERT(IntArray.IsValidIndex(0) == TRUE);
	ASSERT(IntArray.IsValidIndex(1) == TRUE);
	ASSERT(IntArray.IsValidIndex(2) == TRUE);
	ASSERT(IntArray.IsValidIndex(3) == FALSE);
	ASSERT(IntArray.IsValidIndex(-1) == FALSE);

	/* Test the GetElement() method */
	ASSERT(IntArray.GetElement(&pTestInt, 0) == TRUE);
	ASSERT(*pTestInt == 12345678l);
	ASSERT(IntArray.GetElement(&pTestInt, 1) == TRUE);
	ASSERT(*pTestInt == 22345678l);
	ASSERT(IntArray.GetElement(&pTestInt, 2) == TRUE);
	ASSERT(*pTestInt == 32345678l);
	ASSERT(StringArray.GetElement(&pTestPtr, 0) == TRUE);
	ASSERT(strcmp(pTestPtr, "Test String #1") == 0);
	ASSERT(StringArray.GetElement(&pTestPtr, 1) == TRUE);
	ASSERT(strcmp(pTestPtr, "Test String #2") == 0);
	ASSERT(TestDataArray.GetElement(&pTestData, 0) == TRUE);
	ASSERT(pTestData->Number == 123);
	ASSERT(pTestData->lNumber == 222222l);
	ASSERT(strcmp(pTestData->Message, "Test Message") == 0);

	/* Test the [] operator */
	ASSERT(*IntArray[0] == 12345678l);
	ASSERT(*IntArray[1] == 22345678l);
	ASSERT(*IntArray[2] == 32345678l);
	ASSERT(strcmp(StringArray[0], "Test String #1") == 0);
	ASSERT(strcmp(StringArray[1], "Test String #2") == 0);
	pTestData = TestDataArray[0];
	ASSERT(pTestData->Number == 123);
	ASSERT(pTestData->lNumber == 222222l);
	ASSERT(strcmp(pTestData->Message, "Test Message") == 0);

	/* Test the DeleteElement() method */
	IntArray.DeleteElement(1);
	ASSERT(IntArray.GetNumElements() == 2);
	ASSERT(*IntArray[0] == 12345678l);
	ASSERT(*IntArray[1] == 32345678l);
	IntArray.DeleteElement(0);
	ASSERT(IntArray.GetNumElements() == 1);
	ASSERT(*IntArray[0] == 32345678l);
	IntArray.DeleteElement(0);
	ASSERT(IntArray.GetNumElements() == 0);

	/* Test the Destroy() method */
	StringArray.Destroy();
	ASSERT(StringArray.GetNumElements() == 0);

	/* Test the IsValidIndex() method again */
	ASSERT(IntArray.IsValidIndex(0) == FALSE);
	ASSERT(StringArray.IsValidIndex(0) == FALSE);

	/* Test the SetGrowSize() method */
	ASSERT(StringArray2.AddElement(CreateString("Test String #1")) == TRUE);
	ASSERT(StringArray2.AddElement(CreateString("Test String #2")) == TRUE);
	pTestPtr = CreateString("Invalid element String");
	ASSERT(StringArray2.AddElement(pTestPtr) == FALSE);
	StringArray2.SetGrowSize(1);
	ASSERT(StringArray2.AddElement(pTestPtr) == TRUE);
	ASSERT(StringArray2.GetMaxElements() == 3);
	ASSERT(StringArray2.GetNumElements() == 3);
	StringArray2.SetGrowSize(-1);
	ASSERT(StringArray2.AddElement(CreateString("Test String #4")) == TRUE);
	ASSERT(StringArray2.AddElement(CreateString("Test String #5")) == TRUE);

	/* Test the FreeExtra() method */
	ASSERT(StringArray2.GetMaxElements() > StringArray2.GetNumElements());
	StringArray2.FreeExtra();
	ASSERT(StringArray2.GetMaxElements() == StringArray2.GetNumElements());
	ASSERT(strcmp(StringArray2[0], "Test String #1") == 0);
	ASSERT(strcmp(StringArray2[1], "Test String #2") == 0);
	ASSERT(strcmp(StringArray2[2], "Invalid element String") == 0);
	ASSERT(strcmp(StringArray2[3], "Test String #4") == 0);
	ASSERT(IsValidPointer(StringArray2[0]));
	ASSERT(IsValidPointer(StringArray2[1]));
	ASSERT(IsValidPointer(StringArray2[2]));
	ASSERT(IsValidPointer(StringArray2[3]));
	StringArray2.AssertValid();
	StringArray2.Destroy();
}

#endif
