/*===========================================================================
 *
 * File:    Profile.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Monday, June 25, 2001
 *
 * Defines custom profiling definitions and routines.
 *
 *=========================================================================*/
#ifndef __PROFILE_H
#define __PROFILE_H


/*===========================================================================
 *
 * Begin Required Include Files
 *
 *=========================================================================*/
#include "common/dl_err.h"
#include "common/dl_time.h"
/*===========================================================================
 *      End of Required Include Files
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Defines
 *
 *=========================================================================*/

/* Macros for inserting profiles, only valid in debug builds */
#if defined(_DEBUG)

/* Define a profile variable */
#define DEFINE_PROFILE(ProfName) \
	profile_t ProfName = { { 0ul }, { 0ul }, { 0ul }, 0.0, { 0ul }, 0.0, { 0ul } };

/* Define a static profile variable */
#define DEFINE_STATIC_PROFILE(ProfName) \
	static profile_t ProfName = { { 0ul }, { 0ul }, { 0ul }, 0.0, { 0ul }, 0.0, { 0ul } }; \
	CProfileEndFunc _tmpVar(ProfName); \
	GetHiClock((ProfName).StartClock);

/* Start a profile block */
#define START_PROFILE(ProfName) GetHiClock((ProfName).StartClock);

/* End a profile block */
#define END_PROFILE(ProfName) \
	GetHiClock((ProfName).EndClock); \
	(ProfName).DiffClock = (ProfName).EndClock - (ProfName).StartClock; \
	(ProfName).DiffTime = ((double)(ProfName).DiffClock) / GetHiClockFreq(); \
	(ProfName).Count++; \
	(ProfName).TotalClock += (ProfName).DiffClock; \
	(ProfName).TotalTime += (ProfName).DiffTime;

/* End a profile block with a save flag to indicate whether to
 * update the accumlated profile results */
#define END_PROFILE_F(ProfName, SaveProfile) \
	GetHiClock((ProfName).EndClock); \
	(ProfName).DiffClock = (ProfName).EndClock - (ProfName).StartClock; \
	(ProfName).DiffTime = ((double)(ProfName).DiffClock) / GetHiClockFreq(); \
	if (SaveProfile) { \
		(ProfName).Count++; \
		(ProfName).TotalClock += (ProfName).DiffClock; \
		(ProfName).TotalTime += (ProfName).DiffTime; \
	}

/* Access profile data */
#define GET_PROFILE_DIFFTIME(ProfName)   ((ProfName).DiffTime)
#define GET_PROFILE_TOTALTIME(ProfName)  ((ProfName).TotalTime)
#define GET_PROFILE_COUNT(ProfName)      ((ProfName).Count)
#define GET_PROFILE_AVGTIME(ProfName)    ((double) (((ProfName).Count == 0) ? 0.0 : (ProfName).TotalTime/(double)(ProfName).Count ) )


/* Define profile macros to nothing in non-debug builds */
#else
#define DEFINE_PROFILE(ProfName) { ; }
#define DEFINE_STATIC_PROFILE(ProfName) { ; }
#define START_PROFILE(ProfName) { ; }
#define END_PROFILE(ProfName)   { ; }
#define END_PROFILE_F(ProfName, SaveProfile)   { ; }
#define GET_PROFILE_DIFFTIME(ProfName)   ((double)0.0)
#define GET_PROFILE_TOTALTIME(ProfName)  ((double)0.0)
#define GET_PROFILE_COUNT(ProfName)      (0ul)
#define GET_PROFILE_AVGTIME(ProfName)    ((double)0.0)

#endif
/*===========================================================================
 *      End of Defines
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type and Structure Definitions
 *
 *=========================================================================*/

/* Main profile type */
typedef struct {
	hiclock_t StartClock;   /* Start time for last profile block */
	hiclock_t EndClock;     /* End time for last profile block */
	hiclock_t DiffClock;    /* Time taken in clock periods for last profile */
	double DiffTime;     /* Time taken in seconds for last profile */

	hiclock_t TotalClock;   /* Total time for multiple profiles */
	double TotalTime;    /* Total seconds for multiple profiles */
	ulong Count;        /* Used for multiple profiling */
} profile_t;


/* Class used only by the profiler for automatically calling
 * things at end of functions */
#if defined(_DEBUG)

/* Used as a hack for internal static function profiles */
extern profile_t *g_pLastStaticProfile;


class CProfileEndFunc {
  protected:
	profile_t &m_rProfile;      /* Referenced profile object */

  public:

	/* Constructor / destructor */
	CProfileEndFunc(profile_t &Profile) : m_rProfile(Profile) { ; }

	~CProfileEndFunc() {
		END_PROFILE(m_rProfile);
		g_pLastStaticProfile = &m_rProfile;
	}
};

#endif

/*===========================================================================
 *      End of Type and Structure Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/

/*===========================================================================
 *      End of Function Prototypes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin External Variables
 *
 *=========================================================================*/

/* The default destination for all profiling output */
extern CLogFile ProfileLog;


/*===========================================================================
 *      End of External Variables
 *=========================================================================*/

#endif
/*===========================================================================
 *      End of File Profile.H
 *=========================================================================*/
