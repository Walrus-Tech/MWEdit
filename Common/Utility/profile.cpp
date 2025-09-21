/*===========================================================================
 *
 * File:    Profile.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Monday, June 25, 2001
 *
 * Description
 *
 *=========================================================================*/

#include "common/utility/profile.h"


DEFINE_FILE();


/* Only open log file in debug builds */
#if defined(_DEBUG)

	/* Define and automatically open the profile log file */
	CLogFile ProfileLog;
	//boolean  OpenLog = ProfileLog.Open("profile.log");

	/* Used as a hack for internal static function profiles */
	extern profile_t *g_pLastStaticProfile = NULL;

#endif
