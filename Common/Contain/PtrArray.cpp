/*===========================================================================
 *
 * File:    PtrArray.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Friday, May 11, 2001
 *
 * Implements the TPtrArray template for handling a simple array
 * of typed pointers which do not belong to the array.
 *
 *=========================================================================*/

/* Include Files */
#include "Common/Contain/PtrArray.h"


/*===========================================================================
 *
 * Begin Local Variable Definitions
 *
 *=========================================================================*/
DEFINE_FILE("PrtArray.cpp");
/*===========================================================================
 *      End of Local Variable Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Module Test Routines
 *
 *=========================================================================*/
#if defined(_DEBUG)
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
typedef TPtrArray<testdata_t> CTestDataArray;
typedef TPtrArray<char> CPCharArray;


/*===========================================================================
 *
 * Function - void Test_StressPtrArray (NumTests);
 *
 * Runs a stress test of the TPtrArray class a number of times,
 * attempting to 'force' an error of some sort.  For each tests, a
 * random number of random sized strings are added to two char* arrays.
 *
 *=========================================================================*/
void Test_StressPtrArray(const size_t NumTests) {
	DEFINE_FUNCTION("Test_StressPtrArray()");
	CPCharArray StringArray1(100);
	size_t LoopCounter;
	size_t LoopCounter1;
	size_t NumAllocs;
	size_t TestSize;
	char *pBuffer;
	SystemLog.Printf(stdout, "================ Stressing the TPtrArray Class ====================");
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
		TestSize = (size_t)((float)rand() * 24000 / RAND_MAX);
		pBuffer = CreateString(TestSize);

		/* Add random sized strings */
		for (LoopCounter1 = 0; LoopCounter1 < NumAllocs; LoopCounter1++) {
			StringArray1.AddElement(pBuffer);
			StringArray2.AddElement(pBuffer);

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
		DestroyArrayPointer(pBuffer);
		OutputBlockInfo();
	}
}

/*===========================================================================
 *      End of Function Test_StressPtrArray()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void Test_PtrArray (void);
 *
 * Tests the TPtrArray class.
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
void Test_PtrArray() {
	DEFINE_FUNCTION("Test_PtrArray()");
	long TestInt;
	long *pTestInt;
	char TestString[] = "Test String #1";
	char *pTestPtr;
	testdata_t TestData;
	testdata_t *pTestData;
	SystemLog.Printf(stdout, "================ Testing the TPtrArray Class ====================");

	/* Test construction of sample templates */
	TPtrArray<long> IntArray(100);
	TPtrArray<char> StringArray2(2, 0);
	TPtrArray<char> StringArray(2, 0);
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
	TestInt = 12345678l;
	ASSERT(IntArray.AddElement(&TestInt) == TRUE);
	TestInt = 22345678l;
	ASSERT(IntArray.AddElement(&TestInt) == TRUE);
	TestInt = 32345678l;
	ASSERT(IntArray.AddElement(&TestInt) == TRUE);
	ASSERT(StringArray.AddElement(TestString) == TRUE);
	ASSERT(StringArray.AddElement(TestString) == TRUE);
	ASSERT(StringArray.AddElement(TestString) == FALSE);
	TestData.Number = 123;
	TestData.lNumber = 222222l;
	strcpy(TestData.Message, "Test Message");
	ASSERT(TestDataArray.AddElement(&TestData) == TRUE);

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
	ASSERT(*pTestInt == 32345678l);
	ASSERT(IntArray.GetElement(&pTestInt, 1) == TRUE);
	ASSERT(*pTestInt == 32345678l);
	ASSERT(IntArray.GetElement(&pTestInt, 2) == TRUE);
	ASSERT(*pTestInt == 32345678l);
	ASSERT(StringArray.GetElement(&pTestPtr, 0) == TRUE);
	ASSERT(strcmp(pTestPtr, TestString) == 0);
	ASSERT(StringArray.GetElement(&pTestPtr, 1) == TRUE);
	ASSERT(strcmp(pTestPtr, TestString) == 0);
	ASSERT(TestDataArray.GetElement(&pTestData, 0) == TRUE);
	ASSERT(pTestData->Number == 123);
	ASSERT(pTestData->lNumber == 222222l);
	ASSERT(strcmp(pTestData->Message, "Test Message") == 0);

	/* Test the [] operator */
	ASSERT(*IntArray[0] == 32345678l);
	ASSERT(*IntArray[1] == 32345678l);
	ASSERT(*IntArray[2] == 32345678l);
	ASSERT(strcmp(StringArray[0], TestString) == 0);
	ASSERT(strcmp(StringArray[1], TestString) == 0);
	pTestData = TestDataArray[0];
	ASSERT(pTestData->Number == 123);
	ASSERT(pTestData->lNumber == 222222l);
	ASSERT(strcmp(pTestData->Message, "Test Message") == 0);

	/* Test the DeleteElement() method */
	IntArray.DeleteElement(1);
	ASSERT(IntArray.GetNumElements() == 2);
	ASSERT(*IntArray[0] == 32345678l);
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
	ASSERT(StringArray2.AddElement(TestString) == TRUE);
	ASSERT(StringArray2.AddElement(TestString) == TRUE);
	ASSERT(StringArray2.AddElement(TestString) == FALSE);
	StringArray2.SetGrowSize(1);
	ASSERT(StringArray2.AddElement(TestString) == TRUE);
	ASSERT(StringArray2.GetMaxElements() == 3);
	ASSERT(StringArray2.GetNumElements() == 3);
	StringArray2.SetGrowSize(-1);
	ASSERT(StringArray2.AddElement(TestString) == TRUE);
	ASSERT(StringArray2.AddElement(TestString) == TRUE);

	/* Test the FreeExtra() method */
	ASSERT(StringArray2.GetMaxElements() > StringArray2.GetNumElements());
	StringArray2.FreeExtra();
	ASSERT(StringArray2.GetMaxElements() == StringArray2.GetNumElements());
	ASSERT(strcmp(StringArray2[0], TestString) == 0);
	ASSERT(strcmp(StringArray2[1], TestString) == 0);
	ASSERT(strcmp(StringArray2[2], TestString) == 0);
	ASSERT(strcmp(StringArray2[3], TestString) == 0);
	StringArray2.AssertValid();
	StringArray2.Destroy();
}

/*===========================================================================
 *      End of Function Test_PtrArray()
 *=========================================================================*/


#endif
/*===========================================================================
 *      End of Module Test Routines
 *=========================================================================*/
