/*===========================================================================
 *
 * File:    Dl_time.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Wednesday, June 20, 2001
 *
 * Contains common time related routines.
 *
 *=========================================================================*/

#include "dl_time.h"


DEFINE_FILE("dl_time.h");


/*===========================================================================
 *
 * Function - void GetHiClock (Counter);
 *
 * Gets the current value of the system's high-resolution counter, if any.
 * The counter used depends on the system.  By default the standard clock()
 * routine is used.
 *
 *=========================================================================*/
void GetHiClock(hiclock_t &Counter) {
	/* Attempt to use the performance counter */
#if defined(_WIN32)
	boolean Result;
	/* Attempt to get the performance timer count */
	Result = QueryPerformanceCounter(&Counter.TimerCount);

	/* Set the counter type and return on success */
	if (Result) {
		Counter.CountType = HICLOCK_PERFORMANCE;
		return;
	}

#endif
	/* Use the clock() count by default */
	Counter.ClockCount = clock();
	Counter.CountType = HICLOCK_CLOCK;
}


/*===========================================================================
 *
 * Function - double GetHiClockTime (void);
 *
 * Returns the time of the system clock in seconds.
 *
 *=========================================================================*/
double GetHiClockTime() {
	hiclock_t CurrentClock;
	GetHiClock(CurrentClock);
	return ((double)CurrentClock) / GetHiClockFreq();
}


/*===========================================================================
 *
 * Function - double GetHiClockFreq (void);
 *
 * Returns the frequency of the system's high-resolution counter in Hz.
 *
 *=========================================================================*/
double GetHiClockFreq() {
	/* Attempt to use the performance counter */
#if defined(_WIN32)
	LARGE_INTEGER Freq;
	int Result;
	Result = QueryPerformanceFrequency(&Freq);

	if (!Result || Freq.QuadPart == 0) {
		return (double)1.0;
	}

	return (double)Freq.QuadPart;
	/* Use the clock() frequency */
#else
	return (double)CLOCKS_PER_SEC;
#endif
}
