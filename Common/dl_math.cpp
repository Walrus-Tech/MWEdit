/*===========================================================================
 *
 * File:    DL_Math.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Tuesday, May 08, 2001
 *
 * Contains implementation of math related functions for Dave's Library
 * of common code.
 *
 * Version History
 * -------------------------------------------------------------------------
 * 2 December 2002 (Dave Humphrey)
 *  - Moved from regular char to TCHAR type to support wide characters
 *    under Windows. Successfully tested.
 *
 * 18 September 2003
 *  - Added the GetNiceTickLengthC() function.
 *
 * 17 February 2004
 *  - Added the Metricize() buffered function.
 *
 *=========================================================================*/

/* Include Files */
#include "dl_math.h"
#include "dl_str.h"
#include <time.h>
#include <string.h>
#include <limits.h>
#include <float.h>


/*===========================================================================
 *
 * Begin Local Variable Definitions
 *
 *=========================================================================*/
DEFINE_FILE("dl_math.cpp");

/* Variables for custom random number generation */
ulong RandomSeed = 1;
ulong RandomAdd  = 1725;
ulong RandomMult = 621;

/*===========================================================================
 *      End of Local Variable Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Global Hexadecimal Value Array
 *
 * Is not a static variable as it is used in the inline function
 * HexCharToInt(), found in dl_math.h.
 *
 *=========================================================================*/
char HexCharValues[128] = {
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	1,
	2,
	3,
	4,
	5,
	6,
	7,
	8,
	9,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	10,
	11,
	12,
	13,
	14,
	15,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	10,
	11,
	12,
	13,
	14,
	15,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0
};
/*===========================================================================
 *      End of Global Hexadecimal Value Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Unit Prefixes Array
 *
 * Static array of numeric unit prefixes used by functions in this
 * module.
 *
 *=========================================================================*/
const static int NumUnitPrefixes = 17;

/* LogBase10, PrefixChar, Prefix */
unit_prefix_t UnitPrefixes[] = {
	{
		-24,
		(TCHAR)'y',
		_T("yocto")
	},
	{
		-21,
		(TCHAR)'z',
		_T("zepto")
	},
	{
		-18,
		(TCHAR)'a',
		_T("atto")
	},
	{
		-15,
		(TCHAR)'f',
		_T("femto")
	},
	{
		-12,
		(TCHAR)'p',
		_T("pico")
	},
	{
		-9,
		(TCHAR)'n',
		_T("nano")
	},
//	{
//		-6,
//		(TCHAR)230,
//		_T("micro")
//	},
	{
		-3,
		(TCHAR)'m',
		_T("milli")
	},
	{
		0,
		(TCHAR)' ',
		_T("")
	},
	{
		3,
		(TCHAR)'k',
		_T("kilo")
	},
	{
		6,
		(TCHAR)'M',
		_T("Mega")
	},
	{
		9,
		(TCHAR)'G',
		_T("Giga")
	},
	{
		12,
		(TCHAR)'T',
		_T("Tera")
	},
	{
		15,
		(TCHAR)'P',
		_T("Peta")
	},
	{
		18,
		(TCHAR)'E',
		_T("Exa")
	},
	{
		21,
		(TCHAR)'Z',
		_T("Zetta")
	},
	{
		24,
		(TCHAR)'Y',
		_T("Yotto")
	}
};
/*===========================================================================
 *      End of Unit Prefixes Array
 *=========================================================================*/


/*===========================================================================
 *
 * Function - double GetNiceTickLength (AxisStart, AxisEnd, NumTicks);
 *
 * Attempts to compute a 'nice' tick length based on the given axis length.
 * A nice tick length is usually 1, 2, 4, 5, or 10 units.  The number of ticks
 * is used as a first approximate to the number of desired ticks.  The actual
 * number of ticks based on the returned tick length may be different.
 * Modifies the input Start and End Axis values to be 'nice' values as well.
 *
 *=========================================================================*/
double GetNiceTickLength(double &AxisStart, double &AxisEnd, const int NumTicks) {
	//DEFINE_FUNCTION("GetNiceTickLength()");
	double AxisWidth;
	double NewAxisStart;
	double NewAxisEnd;
	double NiceRange;
	double NiceTick;
	/* Check for special cases */
	AxisWidth = AxisEnd - AxisStart;

	if (AxisWidth == 0.0) {
		return 0.0;
	}

	/* Compute the new nice range and ticks */
	NiceRange = NiceNumber(AxisEnd - AxisStart, 0);
	NiceTick = NiceNumber(NiceRange / (NumTicks - 1), 1);

	/* Compute the new nice start and end values */
	NewAxisStart = floor(AxisStart / NiceTick) * NiceTick;
	NewAxisEnd = ceil(AxisEnd / NiceTick) * NiceTick;

	//NumFrac = MAX(-floor(log10(NiceTick)), 0);
	AxisStart = NewAxisStart;
	AxisEnd = NewAxisEnd;
	return NiceTick;
}

/*===========================================================================
 *      End of Function GetNiceTickLength()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - double GetNiceTickLengthC (AxisStart, AxisEnd, NumTicks);
 *
 * Attempts to compute a 'nice' tick length based on the given axis length.
 * A nice tick length is usually 1, 2, 4, 5, or 10 units.  The number of ticks
 * is used as a first approximate to the number of desired ticks.  The actual
 * number of ticks based on the returned tick length may be different.
 *
 *=========================================================================*/
double GetNiceTickLengthC(const double AxisStart, const double AxisEnd, const int NumTicks) {
	//DEFINE_FUNCTION("GetNiceTickLengthC()");
	double AxisWidth;
	double NewAxisStart;
	double NewAxisEnd;
	double NiceRange;
	double NiceTick;
	/* Check for special cases */
	AxisWidth = AxisEnd - AxisStart;

	if (AxisWidth == 0.0) {
		return 0.0;
	}

	/* Compute the new nice range and ticks */
	NiceRange = NiceNumber(AxisEnd - AxisStart, 0);
	NiceTick = NiceNumber(NiceRange / (NumTicks - 1), 1);

	/* Compute the new nice start and end values */
	NewAxisStart = floor(AxisStart / NiceTick) * NiceTick;
	NewAxisEnd = ceil(AxisEnd / NiceTick) * NiceTick;
	//NumFrac = MAX(-floor(log10(NiceTick)), 0);
	return NiceTick;
}

/*===========================================================================
 *      End of Function GetNiceTickLengthC()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - unit_prefix_t GetUnitPrefix (OverFlow, Value);
 *
 * Attempt to return unit prefix element which best represents the given
 * value.  Returns a pointer to the prefix record. The OverFlow flag is
 * set to TRUE if the given value is smaller than the smallest prefix, or
 * larger by a factor of 1000 than the largest prefix.
 *
 *=========================================================================*/
unit_prefix_t *GetUnitPrefix(boolean &OverFlow, const double Value) {
	//DEFINE_FUNCTION("GetUnitPrefix()");
	int LoopCounter;
	int Base10 = 0;

	/* Compute the proper base-10 of input value */
	if (Value != 0.0) {
		Base10 = (int)floor(log10(fabs(Value)));
	}

	OverFlow = FALSE;

	/* Check special small cases */
	if (Base10 < UnitPrefixes[0].LogBase10) {
		OverFlow = TRUE;
		return &UnitPrefixes[0];
	}

	/* Find the best prefix in the array for the value */
	for (LoopCounter = 1; LoopCounter < NumUnitPrefixes; LoopCounter++) {
		if (Base10 < UnitPrefixes[LoopCounter].LogBase10) {
			return &UnitPrefixes[LoopCounter - 1];
		}
	}

	/* Use last prefix in array, check overflow case */
	if (Base10 > UnitPrefixes[NumUnitPrefixes - 1].LogBase10 + 3) {
		OverFlow = TRUE;
	}

	return &UnitPrefixes[NumUnitPrefixes - 1];
}

/*===========================================================================
 *      End of Function GetUnitPrefix()
 *=========================================================================*/


/*===========================================================================
 *
 * Function -   TCHAR* Metricize (Value, pUnits);
 *      TCHAR* Metricize (Buffer, BufferSize, Value, pUnits);
 *
 * Converts a metric type value to a string with the given units using
 * the best possible representation.  For instance:
 *  Metricize(1.23,    "\m") = "1.23 m"
 *  Metricize(0.00123, "\m") = "123 mm"
 *  Metricize(1230,    "\m") = "1.23 km"
 * Returns a pointer to the string buffer.  Uses a static buffer to
 * generate the results.
 *
 *=========================================================================*/
TCHAR *Metricize(const double Value, const TCHAR *pUnits) {
	static TCHAR OutputBuffer[256];
	return Metricize(OutputBuffer, 255, Value, pUnits);
}

TCHAR *Metricize(TCHAR *Buffer, const int BufferSize, const double Value, const TCHAR *pUnits) {
	DEFINE_FUNCTION("Metricize()");
	unit_prefix_t *pUnitPrefix;
	int Result;
	boolean OverFlow;
	/* Ensure valid input */
	ASSERT(pUnits != NULL);
	/* Get the appropiate unit prefix structure */
	pUnitPrefix = GetUnitPrefix(OverFlow, Value);

	/* Output the modified value to the string */
	if (OverFlow) {
		Result = snprintf(Buffer,
		                  BufferSize,
		                  _T("%g %c%s"),
		                  Value / exp10(pUnitPrefix->LogBase10),
		                  pUnitPrefix->PrefixChar,
		                  pUnits);
	} else if (pUnitPrefix->LogBase10 == 0) {
		Result = snprintf(Buffer,
		                  BufferSize,
		                  _T("%3g %s"),
		                  Value / exp10(pUnitPrefix->LogBase10),
		                  pUnits);
	} else {
		Result = snprintf(Buffer,
		                  BufferSize,
		                  _T("%3g %c%s"),
		                  Value / exp10(pUnitPrefix->LogBase10),
		                  pUnitPrefix->PrefixChar,
		                  pUnits);
	}

	/* Check for errors */
	if (Result < 0) {
		ErrorHandler.AddError(ERR_SYSTEM, errno, _T("Error creating string buffer!"));
		return Buffer;
	}

	return Buffer;
}

/*===========================================================================
 *      End of Function Metricize()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - double NiceNumber (Value, Round);
 *
 * Taken from Graphics Gems, Volume 1
 * (Heckbert, Paul S., Nice Numbers for Graph Labels, p. 61-63, code: p. 657-659).
 * Find a "nice" number approximately equal to Value. Round the number if
 * Round=1, take ceiling if Round=0.
 *
 *=========================================================================*/
double NiceNumber(const double Value, const int Round) {
	int Exponent;                               /* Exponent of x */
	double Fraction;                            /* Fractional part of x */
	double NiceFraction;                        /* Nice, rounded fraction */
	Exponent = (int)floor(log10(Value));
	Fraction = Value / pow10((double)Exponent); /* between 1 and 10 */

	if (Round) {
		if (Fraction < 1.5) {
			NiceFraction = 1.0;
		} else if (Fraction < 3.0) {
			NiceFraction = 2.0;
		} else if (Fraction < 7.0) {
			NiceFraction = 5.0;
		} else {
			NiceFraction = 10.0;
		}
	} else {
		if (Fraction <= 1.0) {
			NiceFraction = 1.0;
		} else if (Fraction <= 2.0) {
			NiceFraction = 2.0;
		} else if (Fraction <= 5.0) {
			NiceFraction = 5.0;
		} else {
			NiceFraction = 10.0;
		}
	}

	return NiceFraction * pow10((double)Exponent);
}

/*===========================================================================
 *      End of Function NiceNumber()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - ulong Random (void);
 *
 * Custom random number generator.  Returns the next pseudo-random unsigned
 * long integer in the sequence (0 to ULONG_MAX).
 *
 *=========================================================================*/
ulong Random() {
	//DEFINE_FUNCTION("Random()");
	RandomSeed *= RandomMult;
	RandomSeed += RandomAdd;
	return RandomSeed;
}

/*===========================================================================
 *      End of Function Random()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int Random (MaxNumber);
 *
 * Generates a random number between 0 and MaxNumber (inclusive).
 *
 *=========================================================================*/
int Random(const int MaxNumber) {
	//DEFINE_FUNCTION("Random()");
	return (int)((double)Random()
	             * ((double)sign(MaxNumber) + (double)MaxNumber)
	             / (double)ULONG_MAX);
}

/*===========================================================================
 *      End of Function Random()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int Random (MaxNumber);
 *
 * Generates an unisnged long random number between 0 and MaxNumber
 * (inclusive).
 *
 *=========================================================================*/
ulong Random(const ulong MaxNumber) {
	//DEFINE_FUNCTION("Random()");
	return (ulong)((double)Random() * ((double)1 + (double)MaxNumber) / (double)ULONG_MAX);
}

/*===========================================================================
 *      End of Function Random()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int Random (MinNumber, MaxNumber);
 *
 * Generates a random number between the given integer range (inclusive).
 *
 *=========================================================================*/
int Random(const int MinNumber, const int MaxNumber) {
	//DEFINE_FUNCTION("Random()");
	double Range = (double)MaxNumber - (double)MinNumber;
	return (int)((double) Random()
	             * ((double)sign(Range) + Range)
	             / (double)ULONG_MAX
	             + (double)MinNumber);
}

/*===========================================================================
 *      End of Function Random()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void RandomizeTimer (void);
 *
 * Much like the Visual Basic function of the same name, this function
 * seeds the random number generator with the current time (number of
 * elasped seconds since Jan 1, 1970).  Seeds both the CRT rand()
 * as well as the custom Random() functions.
 *
 *=========================================================================*/
void RandomizeTimer() {
	//DEFINE_FUNCTION("RandomizeTimer()");
	srand((uint)time(NULL));
	SeedRandom((ulong)time(NULL));
}

/*===========================================================================
 *      End of Function RandomizeTimer()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void SeedRandom (NewSeed);
 *
 * Seeds the custom long integer random number generator.
 *
 *=========================================================================*/
void SeedRandom(const ulong NewSeed) {
	//DEFINE_FUNCTION("SeedRandom()");
	RandomSeed = NewSeed;
}

/*===========================================================================
 *      End of Function SeedRandom()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Test Module Routines
 *
 * Debug build only functions for testing functions in this module.
 *
 *=========================================================================*/
#if defined(_DEBUG)

/* Turn off several warnings associated with the test code */
#if defined(__BCPLUSPLUS__)
	#pragma warn -rch
	#pragma warn -ccc
#endif

/*===========================================================================
 *
 * Function - void Test_HexCharToInt (void);
 *
 * Tests the HexCharToInt() macro.
 *  1. Test all hex characters to ensure success
 *
 *=========================================================================*/
void Test_HexCharToInt() {
	DEFINE_FUNCTION("Test_HexCharToInt()");
	SystemLog.Printf(stdout, _T("================= Testing Test_HexCharToInt() ==================="));

	/* Test all hex characters to ensure success */
	ASSERT(HexCharToInt((TCHAR)'0') == 0);
	ASSERT(HexCharToInt((TCHAR)'1') == 1);
	ASSERT(HexCharToInt((TCHAR)'2') == 2);
	ASSERT(HexCharToInt((TCHAR)'3') == 3);
	ASSERT(HexCharToInt((TCHAR)'4') == 4);
	ASSERT(HexCharToInt((TCHAR)'5') == 5);
	ASSERT(HexCharToInt((TCHAR)'6') == 6);
	ASSERT(HexCharToInt((TCHAR)'7') == 7);
	ASSERT(HexCharToInt((TCHAR)'8') == 8);
	ASSERT(HexCharToInt((TCHAR)'9') == 9);
	ASSERT(HexCharToInt((TCHAR)'a') == 10);
	ASSERT(HexCharToInt((TCHAR)'b') == 11);
	ASSERT(HexCharToInt((TCHAR)'c') == 12);
	ASSERT(HexCharToInt((TCHAR)'d') == 13);
	ASSERT(HexCharToInt((TCHAR)'e') == 14);
	ASSERT(HexCharToInt((TCHAR)'f') == 15);
	ASSERT(HexCharToInt((TCHAR)'A') == 10);
	ASSERT(HexCharToInt((TCHAR)'B') == 11);
	ASSERT(HexCharToInt((TCHAR)'C') == 12);
	ASSERT(HexCharToInt((TCHAR)'D') == 13);
	ASSERT(HexCharToInt((TCHAR)'E') == 14);
	ASSERT(HexCharToInt((TCHAR)'F') == 15);
}

/*===========================================================================
 *      End of Function Test_HexCharToInt()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void Test_Metricize (void);
 *
 * Tests the Metricize() function.
 *  1. Test typical positive inputs
 *  2. Test 0 input
 *  3. Test some negative inputs
 *  4. Test very small/large values
 *  5. Test with different unit strings
 *
 *=========================================================================*/
void Test_Metricize() {
	DEFINE_FUNCTION("Test_Metricize()");
	TCHAR *pString;
	SystemLog.Printf(stdout, _T("================= Testing Metricize() ==================="));

	/* Test with typical strings */
	pString = Metricize(123456789.0f, _T("m"));
	ASSERT(pString != NULL);
	SystemLog.Printf(stdout, _T("\tMetricize(123456789) = '%s'"), pString);
	pString = Metricize(12345678.9f, _T("m"));
	ASSERT(pString != NULL);
	SystemLog.Printf(stdout, _T("\tMetricize(12345678.9) = '%s'"), pString);
	pString = Metricize(1234567.89f, _T("m"));
	ASSERT(pString != NULL);
	SystemLog.Printf(stdout, _T("\tMetricize(1234567.89) = '%s'"), pString);
	pString = Metricize(123456.789f, _T("m"));
	ASSERT(pString != NULL);
	SystemLog.Printf(stdout, _T("\tMetricize(123456.789) = '%s'"), pString);
	pString = Metricize(12345.6789f, _T("m"));
	ASSERT(pString != NULL);
	SystemLog.Printf(stdout, _T("\tMetricize(12345.6789) = '%s'"), pString);
	pString = Metricize(1234.56789f, _T("m"));
	ASSERT(pString != NULL);
	SystemLog.Printf(stdout, _T("\tMetricize(1234.56789) = '%s'"), pString);
	pString = Metricize(123.456789f, _T("m"));
	ASSERT(pString != NULL);
	SystemLog.Printf(stdout, _T("\tMetricize(123.456789) = '%s'"), pString);
	pString = Metricize(12.3456789f, _T("m"));
	ASSERT(pString != NULL);
	SystemLog.Printf(stdout, _T("\tMetricize(12.3456789) = '%s'"), pString);
	pString = Metricize(1.23456789f, _T("m"));
	ASSERT(pString != NULL);
	SystemLog.Printf(stdout, _T("\tMetricize(1.23456789) = '%s'"), pString);
	pString = Metricize(0.12345f, _T("m"));
	ASSERT(pString != NULL);
	SystemLog.Printf(stdout, _T("\tMetricize(0.12345) = '%s'"), pString);
	pString = Metricize(0.012345f, _T("m"));
	ASSERT(pString != NULL);
	SystemLog.Printf(stdout, _T("\tMetricize(0.012345) = '%s'"), pString);
	pString = Metricize(0.0012345f, _T("m"));
	ASSERT(pString != NULL);
	SystemLog.Printf(stdout, _T("\tMetricize(0.0012345) = '%s'"), pString);
	pString = Metricize(0.00012345f, _T("m"));
	ASSERT(pString != NULL);
	SystemLog.Printf(stdout, _T("\tMetricize(0.00012345) = '%s'"), pString);
	pString = Metricize(0.000012345f, _T("m"));
	ASSERT(pString != NULL);
	SystemLog.Printf(stdout, _T("\tMetricize(0.000012345) = '%s'"), pString);
	pString = Metricize(0.0000012345f, _T("m"));
	ASSERT(pString != NULL);
	SystemLog.Printf(stdout, _T("\tMetricize(0.0000012345) = '%s'"), pString);
	pString = Metricize(0.00000012345f, _T("m"));
	ASSERT(pString != NULL);
	SystemLog.Printf(stdout, _T("\tMetricize(0.00000012345) = '%s'"), pString);
	pString = Metricize(0.000000012345f, _T("m"));
	ASSERT(pString != NULL);
	SystemLog.Printf(stdout, _T("\tMetricize(0.000000012345) = '%s'"), pString);

	/* Test 0 input */
	pString = Metricize(0.0f, _T("m"));
	ASSERT(pString != NULL);
	SystemLog.Printf(stdout, _T("\tMetricize(0) = '%s'"), pString);

	/* Test some negative inputs */
	pString = Metricize(-12345.6f, _T("m"));
	ASSERT(pString != NULL);
	SystemLog.Printf(stdout, _T("\tMetricize(-12345.6) = '%s'"), pString);
	pString = Metricize(-1.23456f, _T("m"));
	ASSERT(pString != NULL);
	SystemLog.Printf(stdout, _T("\tMetricize(-1.23456) = '%s'"), pString);
	pString = Metricize(-0.00000123456f, _T("m"));
	ASSERT(pString != NULL);
	SystemLog.Printf(stdout, _T("\tMetricize(-0.00000123456) = '%s'"), pString);

	/* Test some very small/large values */
	pString = Metricize(1.23456e30f, _T("m"));
	ASSERT(pString != NULL);
	SystemLog.Printf(stdout, _T("\tMetricize(1.23456e30) = '%s'"), pString);
	pString = Metricize(1.23456e-30f, _T("m"));
	ASSERT(pString != NULL);
	SystemLog.Printf(stdout, _T("\tMetricize(1.23456e-30) = '%s'"), pString);

	/* Test with various unit strings */
	pString = Metricize(-12345.6e12f, _T(""));
	ASSERT(pString != NULL);
	SystemLog.Printf(stdout, _T("\tMetricize(-12345.6e12, '') = '%s'"), pString);
	pString = Metricize(-12345.6e12f, _T("UNIT"));
	ASSERT(pString != NULL);
	SystemLog.Printf(stdout, _T("\tMetricize(-12345.6e12, 'UNIT') = '%s'"), pString);
}

/*===========================================================================
 *      End of Function Test_Metricize()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void Test_Random (NumTests);
 *
 * Tests the Random() function.
 *  1. Outputs multiple random numbers to a test file for analyse
 *  2. Outputs the frequency of the numbers (0 to 65535)
 *
 *=========================================================================*/
void Test_Random(const size_t NumTests) {
	DEFINE_FUNCTION("Test_Random()");
#if defined(__BCPLUSPLUS__)
	const size_t ArraySize = 4000u;
	const size_t ShiftSize = 17;
#elif defined(__TURBOC__)
	const size_t ArraySize = 32767u;
	const size_t ShiftSize = 17;
#else
	const size_t ArraySize = 65535u;
	const size_t ShiftSize = 16;
#endif
	size_t *NumberCount;
	size_t *NumberCount1;
	size_t LoopCounter;
	ulong RandNumber;
	FILE *pFileHandle;

	/* Allocate arrays due to problem with large stack variables in Win16 */
	NumberCount = (size_t *)CreateString(ArraySize * sizeof(size_t));
	NumberCount1 = (size_t *)CreateString(ArraySize * sizeof(size_t));
	SystemLog.Printf(stdout, _T("================= Testing Random() ==================="));
	memset(NumberCount, 0, sizeof(size_t) * (size_t)ArraySize);
	memset(NumberCount1, 0, sizeof(size_t) * (size_t)ArraySize);

	/* Output random number data */
	pFileHandle = TFOPEN(_T("c:\\temp\\rand1.dat"), _T("wt"));
	ASSERT(pFileHandle != NULL);
	TFPRINTF(pFileHandle, _T("     Index,     Random,    HiBytes,   LowBytes\n"));

	for (LoopCounter = 0; LoopCounter < NumTests; LoopCounter++) {
		RandNumber = Random();
		TFPRINTF(pFileHandle,
		         _T("%10u, %10lu, %10lu, %10lu\n"),
		         LoopCounter,
		         RandNumber,
		         (RandNumber >> ShiftSize),
		         RandNumber & ArraySize);
		NumberCount[size_t((RandNumber >> ShiftSize) & ArraySize)]++;
		NumberCount1[size_t(RandNumber & ArraySize)]++;
	}

	fclose(pFileHandle);
	/* Output random number frequency data */
	pFileHandle = TFOPEN(_T("c:\\temp\\rand2.dat"), _T("wt"));
	ASSERT(pFileHandle != NULL);
	TFPRINTF(pFileHandle, _T("     Number, HighCount,  LowCount\n"));

	for (LoopCounter = 0; LoopCounter < ArraySize; LoopCounter++) {
		TFPRINTF(pFileHandle,
		         _T("%10lu, %10u, %10u\n"),
		         LoopCounter,
		         NumberCount[LoopCounter],
		         NumberCount1[LoopCounter]);
	}

	fclose(pFileHandle);
	DestroyPointer(NumberCount);
	DestroyPointer(NumberCount1);
}

/*===========================================================================
 *      End of Function Test_Random()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void Test_Random1 (const size_t NumTests);
 *
 * Tests the Random(int) function.
 *  1. Tests against a sample range of 1000 and outputs frequency
 *     results to file
 *  2. Tests against a range of 0 to 1 and outputs frequency results
 *  3. Test for range 0 to -2, outputting frequency results
 *
 *=========================================================================*/
void Test_Random1(const size_t NumTests) {
	DEFINE_FUNCTION("Test_Random1()");
	size_t LoopCounter;
	size_t NumberCount1[1001];
	size_t NumberCount2[3];
	size_t NumberCount3[4];
	FILE* pFileHandle;
	int RandNumber;

	SystemLog.Printf(stdout, _T("================= Testing Random(int) ==================="));
	memset(NumberCount1, 0, sizeof(size_t) * (size_t)1001);
	memset(NumberCount2, 0, sizeof(size_t) * (size_t)3);
	memset(NumberCount3, 0, sizeof(size_t) * (size_t)4);

	/* Generate random numbers from 0 to 1000 */
	for (LoopCounter = 0; LoopCounter < NumTests; LoopCounter++) {
		RandNumber = Random(1000);
		ASSERT(RandNumber >= 0 && RandNumber <= 1000);
		NumberCount1[RandNumber]++;
	}

	/* Generate random numbers from 0 to 1 */
	for (LoopCounter = 0; LoopCounter < NumTests; LoopCounter++) {
		RandNumber = Random(1);
		ASSERT(RandNumber >= 0 && RandNumber <= 1);
		NumberCount2[RandNumber]++;
	}

	/* Generate random numbers from 0 to -2 */
	for (LoopCounter = 0; LoopCounter < NumTests; LoopCounter++) {
		RandNumber = Random(-2);
		ASSERT(RandNumber <= 0 && RandNumber >= -2);
		NumberCount3[-RandNumber]++;
	}

	/* Output random number frequency data for 0 to 1000 */
	pFileHandle = TFOPEN(_T("c:\\temp\\rnd1000f.dat"), _T("wt"));
	ASSERT(pFileHandle != NULL);
	TFPRINTF(pFileHandle, _T("     Number,     Count\n"));

	for (LoopCounter = 0; LoopCounter < 1001; LoopCounter++) {
		TFPRINTF(pFileHandle, _T("%10lu, %10u\n"), LoopCounter, NumberCount1[LoopCounter]);
	}

	fclose(pFileHandle);
	/* Output random number frequency data for 0 to 1 */
	pFileHandle = TFOPEN(_T("c:\\temp\\rnd1f.dat"), _T("wt"));
	ASSERT(pFileHandle != NULL);
	TFPRINTF(pFileHandle, _T("     Number,     Count\n"));

	for (LoopCounter = 0; LoopCounter < 2; LoopCounter++) {
		TFPRINTF(pFileHandle, _T("%10lu, %10u\n"), LoopCounter, NumberCount2[LoopCounter]);
	}

	fclose(pFileHandle);
	/* Output random number frequency data for 0 to -2 */
	pFileHandle = TFOPEN(_T("c:\\temp\\rnd-2f.dat"), _T("wt"));
	ASSERT(pFileHandle != NULL);
	TFPRINTF(pFileHandle, _T("     Number,     Count\n"));

	for (LoopCounter = 0; LoopCounter < 3; LoopCounter++) {
		TFPRINTF(pFileHandle, _T("-%10lu, %10u\n"), LoopCounter, NumberCount3[LoopCounter]);
	}

	fclose(pFileHandle);
}

/*===========================================================================
 *      End of Function Test_Random1()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void Test_Random2 (NumTests);
 *
 * Tests the Random(int, int) function
 *  1. Output frequency data for a range of 905 to 1905.
 *  1. Output frequency data for a range of 1001 to 1002
 *  3. Output frequency data for a range of -6105 to -6107
 *
 *=========================================================================*/
void Test_Random2(const size_t NumTests) {
	DEFINE_FUNCTION("Test_Random2()");
	size_t LoopCounter;
	size_t NumberCount1[1001];
	size_t NumberCount2[3];
	size_t NumberCount3[4];
	FILE* pFileHandle;
	int RandNumber;

	SystemLog.Printf(stdout, _T("================= Testing Random(int, int) ==================="));
	memset(NumberCount1, 0, sizeof(size_t) * (size_t)1001);
	memset(NumberCount2, 0, sizeof(size_t) * (size_t)3);
	memset(NumberCount3, 0, sizeof(size_t) * (size_t)4);

	/* Generate random numbers from 0 to 1000 */
	for (LoopCounter = 0; LoopCounter < NumTests; LoopCounter++) {
		RandNumber = Random(905, 1905);
		ASSERT(RandNumber >= 905 && RandNumber <= 1905);
		NumberCount1[RandNumber - 905]++;
	}

	/* Generate random numbers from 0 to 1 */
	for (LoopCounter = 0; LoopCounter < NumTests; LoopCounter++) {
		RandNumber = Random(1001, 1002);
		ASSERT(RandNumber >= 1001 && RandNumber <= 1002);
		NumberCount2[RandNumber - 1001]++;
	}

	/* Generate random numbers from 0 to -2 */
	for (LoopCounter = 0; LoopCounter < NumTests; LoopCounter++) {
		RandNumber = Random(-6105, -6107);
		ASSERT(RandNumber <= -6105 && RandNumber >= -6107);
		NumberCount3[RandNumber + 6107]++;
	}

	/* Output random number frequency data for 905 to 1005 */
	pFileHandle = TFOPEN(_T("c:\\temp\\rnd905f.dat"), _T("wt"));
	ASSERT(pFileHandle != NULL);
	TFPRINTF(pFileHandle, _T("     Number,     Count\n"));

	for (LoopCounter = 0; LoopCounter < 1001; LoopCounter++) {
		TFPRINTF(pFileHandle, _T("%10lu, %10u\n"), LoopCounter + 905, NumberCount1[LoopCounter]);
	}

	fclose(pFileHandle);
	/* Output random number frequency data for 1001 to 1002 */
	pFileHandle = TFOPEN(_T("c:\\temp\\rnd1001f.dat"), _T("wt"));
	ASSERT(pFileHandle != NULL);
	TFPRINTF(pFileHandle, _T("     Number,     Count\n"));

	for (LoopCounter = 0; LoopCounter < 2; LoopCounter++) {
		TFPRINTF(pFileHandle, _T("%10lu, %10u\n"), LoopCounter + 1001, NumberCount2[LoopCounter]);
	}

	fclose (pFileHandle);
	/* Output random number frequency data for -6105 to -6107 */
	pFileHandle = TFOPEN(_T("c:\\temp\\rnd-6105f.dat"), _T("wt"));
	ASSERT(pFileHandle != NULL);
	TFPRINTF(pFileHandle, _T("     Number,     Count\n"));

	for (LoopCounter = 0; LoopCounter < 3; LoopCounter++) {
		TFPRINTF(pFileHandle,
		         _T("%10ld, %10u\n"),
		         (long)LoopCounter - 6107,
		         NumberCount3[LoopCounter]);
	}

	fclose(pFileHandle);
}

/*===========================================================================
 *      End of Function Test_Random2()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void Test_RandomRate (NumTests);
 *
 * Tests the number of times the Random() function can be called
 * before returning to the original seed.  A random seed is chosen
 * for each test.
 *
 *=========================================================================*/
void Test_RandomRate(const size_t NumTests) {
	//DEFINE_FUNCTION("Test_RandomRate()");
	size_t LoopCounter;
	ulong Counter;
	ulong InitialSeed;

	SystemLog.Printf(stdout, _T("================= Testing Random Turnover Rate ==================="));
	Random();
	SeedRandom(Random());

	/* Perform each test a number of times */
	for (LoopCounter = 0; LoopCounter < NumTests; LoopCounter++) {
		InitialSeed = RandomSeed;
		Counter = 0;
		SystemLog.Printf(stdout,
		                 _T("\t%u) Testing turnover rate of seed %lu..."),
		                 LoopCounter + 1,
		                 InitialSeed);

		while (Random() != InitialSeed) {
			Counter++;

			if ((Counter % 1000000ul) == 0) {
				TPRINTF(_T("\t\t%lu million\n"), Counter / 1000000ul);
			}
		}

		SystemLog.Printf(stdout,
		                 _T("\t\tSeed of %lu turned over in %lu calls..."),
		                 InitialSeed,
		                 Counter);
	}
}

/*===========================================================================
 *      End of Function Test_RandomRate()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void Test_sign (void);
 *
 * Tests the various sign() type functions.
 *  1. Ensures each version gives a valid -1/0/1 result.
 *
 *=========================================================================*/
void Test_sign() {
	DEFINE_FUNCTION("Test_sign()");
	SystemLog.Printf(stdout, _T("================= Testing sign() Functions ==================="));

	/* Test positive numbers */
	ASSERT(sign((int)10) == 1);
	ASSERT(sign((int)INT_MAX) == 1);
	ASSERT(sign((long)101) == 1);
	ASSERT(sign((long)LONG_MAX) == 1);
	ASSERT(sign((float)1012.9) == 1.0);
	ASSERT(sign((float)FLT_MAX) == 1.0);
	ASSERT(sign((float)FLT_MIN) == 1.0);
	ASSERT(sign((double)10381.1) == 1.0);
	ASSERT(sign((double)DBL_MAX) == 1.0);
	ASSERT(sign((double)DBL_MIN) == 1.0);

	/* Test zero numbers */
	ASSERT(sign((int)0) == 0);
	ASSERT(sign((long)0) == 0);
	ASSERT(sign((float)0.0) == 0.0);
	ASSERT(sign((double)0.0) == 0.0);

	/* Test negative numbers */
	ASSERT(sign((int)-10) == -1);
	ASSERT(sign((int)INT_MIN) == -1);
	ASSERT(sign((long)-101) == -1);
	ASSERT(sign((long)LONG_MIN) == -1);
	ASSERT(sign((float)-1012.9) == -1.0);
	ASSERT(sign((float)-FLT_MAX) == -1.0);
	ASSERT(sign((float)-FLT_MIN) == -1.0);
	ASSERT(sign((double)-10381.1) == -1.0);
	ASSERT(sign((double)-DBL_MAX) == -1.0);
	ASSERT(sign((double)-DBL_MIN) == -1.0);
}

/*===========================================================================
 *      End of Function Test_sign()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void Test_DL_Math (void);
 *
 * Tests all the routines in this module.
 *  1. Tests the Random() function
 *  2. Tests the Random(int) and Random(int, int) functions
 *  3. Test the various sign() functions
 *  4. Test the turnover rate of the random function
 *  5. Tests the Metricize() function
 *
 *=========================================================================*/
void Test_DL_Math() {
	//DEFINE_FUNCTION("Test_DL_Math()");
	Test_sign();
	Test_HexCharToInt();
	Test_Metricize();

	//RandomizeTimer();
	Test_Random();
	Test_Random1();
	Test_Random2();
	//Test_RandomRate();
}

/*===========================================================================
 *      End of Function Test_DL_Math()
 *=========================================================================*/

/* Restore compiler warning options */
#if defined(__BCPLUSPLUS__)
	#pragma warn .rch
	#pragma warn .ccc
#endif

#endif
/*===========================================================================
 *      End of Test Module Routines
 *=========================================================================*/
