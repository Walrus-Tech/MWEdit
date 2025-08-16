/*===========================================================================
 *
 * File:    DL_Time.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Friday, May 25, 2001
 *
 * Defines common time related routines for Dave's Library of common code.
 * Should be portable to DOS, Win32, and Unix systems.
 *
 *=========================================================================*/
#ifndef __DL_TIME_H
#define __DL_TIME_H


#include "dl_err.h"
#include <time.h>

#if defined(_WIN32)
	#include "windows.h"
#endif


/* Types of counters used */
#define HICLOCK_PERFORMANCE 1
#define HICLOCK_CLOCK       0


/* Type for recording high-resolution counters */
typedef struct hiclock_t {
	union {
		clock_t ClockCount;       /* For the standard clock() counter */

#if defined(_WIN32)
		LARGE_INTEGER TimerCount; /* Windows performance counter */
#endif
	};

	int CountType;                /* Stores what type of counter is used */


	/* Overloaded copy operator */
	hiclock_t &operator =(const hiclock_t &Value);
	hiclock_t &operator =(const ulong& lValue);

	/* Overloaded comparison operators */
	int operator ==(const hiclock_t &Value);
	int operator >(const hiclock_t &Value);
	int operator <(const hiclock_t &Value);

	/* Conversion to a double value */
	operator double() const;

	/* Overloaded assignment operators */
	hiclock_t &operator +=(const hiclock_t &Value);
	hiclock_t &operator -=(const hiclock_t &Value);

	/* Overloaded addition/subtraction operators */
	friend hiclock_t operator +(const hiclock_t &Value1, const hiclock_t &Value2);
	friend hiclock_t operator -(const hiclock_t &Value1, const hiclock_t &Value2);
	friend hiclock_t operator +(const hiclock_t &Value1);
	friend hiclock_t operator -(const hiclock_t &Value1);
} hiclock_t;


/* High-resolution counter copy operator */
inline hiclock_t &hiclock_t::operator =(const hiclock_t &Value) {
	CountType = Value.CountType;
#if defined(WIN32)
	TimerCount = Value.TimerCount;
#else
	ClockCount = Value.ClockCount;
#endif
	return *this;
}

/* High-resolution counter copy operator from a long value */
inline hiclock_t &hiclock_t::operator =(const ulong &lValue) {
#if defined(WIN32)
	TimerCount.QuadPart = (LONGLONG)lValue;
#else
	ClockCount = (clock_t)lValue;
#endif
	return *this;
}

/* Compare two high-resolution counter values */
inline int HiClockCompare(const hiclock_t &Value1, const hiclock_t &Value2) {
	/* Ensure the counters are the same counter type */
	if (Value1.CountType != Value2.CountType) {
		return 1;
	}

	switch (Value1.CountType) {
		case HICLOCK_PERFORMANCE: {
#if defined(_WIN32)
			LONGLONG Diff = Value1.TimerCount.QuadPart - Value2.TimerCount.QuadPart;

			if (Diff == (LONGLONG)0) {
				return 0;
			}

			if (Diff < (LONGLONG)0) {
				return -1;
			}

			return 1;
#else
			return (int)1;
#endif
		}

		case HICLOCK_CLOCK:
			return (int)(Value1.ClockCount > Value2.ClockCount);

		default:
			return 1;
	}
}

/* High-resolution counter comparisons */
inline int hiclock_t::operator >(const hiclock_t &Value) {
	return HiClockCompare(*this, Value) > 0;
}

inline int hiclock_t::operator <(const hiclock_t &Value) {
	return HiClockCompare(*this, Value) < 0;
}

inline int hiclock_t::operator ==(const hiclock_t &Value) {
	return HiClockCompare(*this, Value) == 0;
}

/* Overloaded addition assignment operator */
inline hiclock_t &hiclock_t::operator +=(const hiclock_t &Value) {
	/* Ensure same clock types */
	if (Value.CountType == CountType) {
		if (Value.CountType == HICLOCK_PERFORMANCE) {
#if defined(_WIN32)
			TimerCount.QuadPart += Value.TimerCount.QuadPart;
#endif
		} else {
			ClockCount += Value.ClockCount;
		}
	}

	return *this;
}

/* Overloaded subtraction assignment operator */
inline hiclock_t &hiclock_t::operator -=(const hiclock_t &Value) {
	/* Ensure same clock types */
	if (Value.CountType == CountType) {
		if (Value.CountType == HICLOCK_PERFORMANCE) {
#if defined(_WIN32)
			TimerCount.QuadPart -= Value.TimerCount.QuadPart;
#endif
		} else {
			ClockCount -= Value.ClockCount;
		}
	}

	return *this;
}

/* Add two high-resolution counters */
inline hiclock_t operator +(const hiclock_t &Value1, const hiclock_t &Value2) {
	hiclock_t TempTime;

	/* Ignore if timer types are not equivalent */
	if (Value1.CountType != Value2.CountType) {
		return Value1;
	}

	TempTime.CountType = Value1.CountType;

	switch (Value1.CountType) {
		case HICLOCK_PERFORMANCE:
#if defined(_WIN32)
			TempTime.TimerCount.QuadPart = Value1.TimerCount.QuadPart + Value2.TimerCount.QuadPart;
			return TempTime;
#else
			return Value1;
#endif

		case HICLOCK_CLOCK:
			TempTime.ClockCount = Value1.ClockCount + Value2.ClockCount;
			return TempTime;

		default:
			return Value1;
	}
}

/* Subtract two high-resolution counters */
inline hiclock_t operator -(const hiclock_t &Value1, const hiclock_t &Value2) {
	hiclock_t TempTime;

	/* Ignore if timer types are not equivalent */
	if (Value1.CountType != Value2.CountType) {
		return Value1;
	}

	TempTime.CountType = Value1.CountType;

	switch (Value1.CountType) {
		case HICLOCK_PERFORMANCE:
#if defined(_WIN32)
			TempTime.TimerCount.QuadPart = Value1.TimerCount.QuadPart - Value2.TimerCount.QuadPart;
			return TempTime;
#else
			return Value1;
#endif

		case HICLOCK_CLOCK:
			TempTime.ClockCount = Value1.ClockCount - Value2.ClockCount;
			return TempTime;

		default:
			return Value1;
	}
}

/* High-resolution counter unary positive operator */
inline hiclock_t operator +(const hiclock_t &Value) {
	return Value;
}

/* High-resolution counter negative operator*/
inline hiclock_t operator -(const hiclock_t &Value) {
	hiclock_t TempTime;
	TempTime.CountType = Value.CountType;

	switch (Value.CountType) {
		case HICLOCK_PERFORMANCE:
#if defined(_WIN32)
			TempTime.TimerCount.QuadPart = -Value.TimerCount.QuadPart;
			return TempTime;
#else
			return Value1;
#endif

		case HICLOCK_CLOCK:
			TempTime.ClockCount = -Value.ClockCount;
			return TempTime;

		default:
			return TempTime;
	}
}

/* Convert a high-resolution counter to a double value */
inline hiclock_t::operator double() const {
	switch (CountType) {
		case HICLOCK_PERFORMANCE:
#if defined(_WIN32)
			return (double)TimerCount.QuadPart;
#else
			return (double)0.0;
#endif

		case HICLOCK_CLOCK:
			return (double)ClockCount;

		default:
			return (double)0.0;
	}
}


/* Retrieves the systems high-resolution counter */
void GetHiClock(hiclock_t &Counter);
double GetHiClockTime();

/* Get the frequency of the system's high-resolution counter */
double GetHiClockFreq();


#endif
