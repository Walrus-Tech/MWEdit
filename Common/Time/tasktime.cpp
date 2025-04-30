/*===========================================================================
 *
 * File:    TaskTime.CPP
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Friday, May 25, 2001
 *
 * Implements the CTaskTimer class.
 *
 *=========================================================================*/

/* Include Files */
#include "time\tasktime.h"

#if defined(_WIN32)
	#include <windows.h>
	#include "mmsystem.h"
#elif defined(__MSDOS__)
	#include <time.h>
	#include <dos.h>
#endif


/*===========================================================================
 *
 * Begin Local Variable Definitions
 *
 *=========================================================================*/
//DEFINE_FILE();
/*===========================================================================
 *      End of Local Variable Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Global Variable Definitions
 *
 *=========================================================================*/

/* The one and only task timer */
CTaskTimer TaskTimer;

/*===========================================================================
 *      End of Global Variable Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Local System-Specific Timer Functions
 *
 *=========================================================================*/
#if defined(__MSDOS__)

/* The new timer interrupt for MSDOS */
void interrupt far l_DosTimerProc(...) {
	TaskTimer.DoTasks((ulong)(1000.0 / (float)CLK_TCK));
	/* Chain to the old timer interrupt */
	TaskTimer.m_PrevTimerFunc();
}



#elif defined(_WIN32)

/* The callback function for the timeSetEvent() Windows function */
VOID CALLBACK l_Win32TimerProc(UINT, UINT, DWORD, DWORD, DWORD) {
	static DWORD LastTime = timeGetTime();
	DWORD CurrentTime = timeGetTime();
	TaskTimer.DoTasks((ulong)(CurrentTime - LastTime));
	LastTime = CurrentTime;
}

#endif
/*===========================================================================
 *      End of Local System-Specific Timer Functions
 *=========================================================================*/


/*===========================================================================
 *
 * Class CTaskTimer Constructor
 *
 *=========================================================================*/
CTaskTimer::CTaskTimer() {
	//DEFINE_FUNCTION("CTaskTimer::CTaskTimer()");
	m_NumTasks = 0;
	m_Active = FALSE;
	m_Initialized = FALSE;
	m_FreeTaskHandle = INITIAL_TASK_HANDLE;
	SYS_MSDOS(m_PrevTimerFunc = NULL);
	SYS_WIN32(m_TimerID = 0);
}

/*===========================================================================
 *      End of Class CTaskTimer Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CTaskTimer Method - void Destroy (void);
 *
 * Uninstalls any set timers and deletes tasks.
 *
 *=========================================================================*/
void CTaskTimer::Destroy(void) {
	//DEFINE_FUNCTION("CTaskTimer::Destroy()");

	/* Restore the previous timer int in DOS or
	 * kill the timer in Win32. */
	if (m_Initialized) {
		SYS_MSDOS( _dos_setvect(DOS_TIMER_INT, m_PrevTimerFunc) );
		SYS_WIN32( timeKillEvent(m_TimerID) );
	}

	m_NumTasks = 0;
	m_Active = FALSE;
	m_Initialized = FALSE;
	SYS_WIN32(m_TimerID = 0);
	SYS_MSDOS(m_PrevTimerFunc = NULL);
}

/*===========================================================================
 *      End of Class Method CTaskTimer::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CTaskTimer Method - boolean AddTask (hTask, Rate, pFunc, UserData);
 *
 * Adds a new task to the task list. Returns FALSE on any error.  On
 * success the set task Handle can be used to identify the task.
 *
 *=========================================================================*/
boolean CTaskTimer::AddTask(HTIMERTASK &hTask, const ulong Rate, PTASK_FUNC pFunc,
                            const long UserData) {
	/* Ensure the array size is not exceeded */
	if (m_NumTasks >= MAX_TIMER_TASKS) {
		ErrorHandler.AddError(ERR_MAXINDEX,
		                      "Exceeded the maximum task list size of %d!",
		                      MAX_TIMER_TASKS);
		return (FALSE);
	}

	/* Initialize the new task */
	m_Tasks[m_NumTasks].Active = FALSE;
	m_Tasks[m_NumTasks].LastCalled = 0;
	m_Tasks[m_NumTasks].TaskRate = Rate;
	m_Tasks[m_NumTasks].pFunc = pFunc;
	m_Tasks[m_NumTasks].UserData = UserData;
	m_Tasks[m_NumTasks].Handle = m_FreeTaskHandle;
	hTask = m_FreeTaskHandle;
	m_FreeTaskHandle++;
	m_NumTasks++;
	return (TRUE);
}

/*===========================================================================
 *      End of Class Method CTaskTimer::AddTask()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CTaskTimer Method - boolean DoTasks (ElaspedTime);
 *
 * Main task handling method called by the timer functions.
 *
 *=========================================================================*/
boolean CTaskTimer::DoTasks(const ulong ElaspedTime) {
	int LoopCounter;

	/* Ignore if not active or initialized */
	if (!IsInitialized()) {
		return (FALSE);
	}

	if (!m_Active) {
		return (TRUE);
	}

	/* To prevent method from being called twice from the timer */
	m_Active = FALSE;

	for (LoopCounter = 0; LoopCounter < m_NumTasks; LoopCounter++) {
		if (m_Tasks[LoopCounter].Active) {
			m_Tasks[LoopCounter].LastCalled += ElaspedTime;

			/* Do we need to call the function? */
			if (m_Tasks[LoopCounter].LastCalled >= m_Tasks[LoopCounter].TaskRate) {
				if (m_Tasks[LoopCounter].pFunc != NULL) {
					m_Tasks[LoopCounter].pFunc(m_Tasks[LoopCounter].LastCalled,
					                           m_Tasks[LoopCounter].UserData);
				}

				m_Tasks[LoopCounter].LastCalled -= m_Tasks[LoopCounter].TaskRate;
			}
		}
	}

	m_Active = TRUE;
	return (TRUE);
}

/*===========================================================================
 *      End of Class Method CTaskTimer::DoTasks()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CTaskTimer Method - int GetTaskIndex (hTask) const;
 *
 * Attempts to find and return the task array index with the given
 * task handle.  Returns -1 on any error.  Protected class method.
 *
 *=========================================================================*/
int CTaskTimer::GetTaskIndex(const HTIMERTASK hTask) const {
	int LoopCounter;

	for (LoopCounter = 0; LoopCounter < m_NumTasks; LoopCounter++) {
		if (hTask == m_Tasks[LoopCounter].Handle) {
			return (LoopCounter);
		}
	}

	/* No match found */
	return (-1);
}

/*===========================================================================
 *      End of Class Method CTaskTimer::GetTaskIndex()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CTaskTimer Get Task Information Methods
 *
 *=========================================================================*/
ulong CTaskTimer::GetTaskRate(const HTIMERTASK hTask) const {
	int TaskIndex = GetTaskIndex(hTask);
	return (IsValidTaskIndex(TaskIndex) ? m_Tasks[TaskIndex].TaskRate : 0);
}

ulong CTaskTimer::GetLastCalled(const HTIMERTASK hTask) const {
	int TaskIndex = GetTaskIndex(hTask);
	return (IsValidTaskIndex(TaskIndex) ? m_Tasks[TaskIndex].LastCalled : 0);
}

boolean CTaskTimer::IsActive(const HTIMERTASK hTask) const {
	int TaskIndex = GetTaskIndex(hTask);
	return (IsValidTaskIndex(TaskIndex) ? m_Tasks[TaskIndex].Active : FALSE);
}

boolean CTaskTimer::IsValidTask(const HTIMERTASK hTask) const {
	int TaskIndex = GetTaskIndex(hTask);
	return ((TaskIndex >= 0 && TaskIndex < m_NumTasks) ? TRUE : FALSE);
}

/*===========================================================================
 *      End of Class CTaskTimer Get Task Information Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Class CTaskTimer Method - boolean Initialize (void);
 *
 * Attempt to initialize the task timer.  This has different methods
 * depending on the system:
 *
 *   WIN32
 *  The timeSetEvent() function is used to call the local function
 *  l_Win32TaskProc() which updates and calls the task list every
 *  55ms to approximate the 18.2 Hz DOS timer.
 *   DOS
 *  A custom timer interrupt handler is created and the local
 *  function l_DosTaskProc() called 18.2x per second (default)
 *  to update the task list.
 *
 * The function returns FALSE if the timer could not be initialized.
 * The task timer is initially not active.
 *
 *=========================================================================*/
boolean CTaskTimer::Initialize(void) {
	/* Ignore if already intialized */
	if (IsInitialized()) {
		return (TRUE);
	}

	/* Setup a Win32 timer */
	SYS_WIN32(m_TimerID = timeSetEvent(55, 22, l_Win32TimerProc, 0, TIME_PERIODIC));

	SYS_WIN32(if (m_TimerID == 0) {
	         )
	SYS_WIN32( ErrorHandler.AddError(ERR_BADINPUT,
	                                  "Failed to initialize the timer using SetTimer()!") );
		SYS_WIN32( return (FALSE) );
		SYS_WIN32(
	} )
	/* Replace the DOS timer interrupt */
	SYS_MSDOS(m_PrevTimerFunc = _dos_getvect(DOS_TIMER_INT));
	SYS_MSDOS(_dos_setvect(DOS_TIMER_INT, l_DosTimerProc));
	/* Unknown system! */
	SYS_NONE(ErrorHandler.AddError(ERR_BADINPUT, "Unknown system, failed to initialize task timer!"));
	SYS_NONE(return (FALSE));
	m_Initialized = TRUE;
	return (TRUE);
}

/*===========================================================================
 *      End of Class Method CTaskTimer::Initialize()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CTaskTimer Method - boolean RemoveTask (hTask);
 *
 * Attempt to remove the given task from the task list.  Returns FALSE
 * on any error.
 *
 *=========================================================================*/
boolean CTaskTimer::RemoveTask(const HTIMERTASK hTask) {
	boolean PrevActive;
	int Index;
	int LoopCounter;
	/* Ensure a valid task handle was given */
	Index = GetTaskIndex(hTask);

	if (!IsValidTaskIndex(Index)) {
		return (FALSE);
	}

	/* Prevent the tasker from being called during array manipulation */
	PrevActive = m_Active;
	m_Active = FALSE;
	m_NumTasks--;

	/* Shift the array to remove task */
	for (LoopCounter = Index; LoopCounter < m_NumTasks; LoopCounter++) {
		m_Tasks[LoopCounter] = m_Tasks[LoopCounter + 1];
	}

	m_Active = PrevActive;
	return (TRUE);
}

/*===========================================================================
 *      End of Class Method CTaskTimer::RemoveTask()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Set Task Information
 *
 *=========================================================================*/
void CTaskTimer::SetActive(const HTIMERTASK hTask, const boolean Flag) {
	int TaskIndex = GetTaskIndex(hTask);

	if (IsValidTaskIndex(TaskIndex)) {
		m_Tasks[TaskIndex].Active = Flag;
	}
}

void CTaskTimer::SetTaskRate(const HTIMERTASK hTask, const ulong Rate) {
	int TaskIndex = GetTaskIndex(hTask);

	if (IsValidTaskIndex(TaskIndex)) {
		m_Tasks[TaskIndex].TaskRate = Rate;
	}
}

void CTaskTimer::SetTaskFunc(const HTIMERTASK hTask, const PTASK_FUNC pFunc) {
	int TaskIndex = GetTaskIndex(hTask);

	if (IsValidTaskIndex(TaskIndex)) {
		m_Tasks[TaskIndex].pFunc = pFunc;
	}
}

void CTaskTimer::SetUserData(const HTIMERTASK hTask, const long UserData) {
	int TaskIndex = GetTaskIndex(hTask);

	if (IsValidTaskIndex(TaskIndex)) {
		m_Tasks[TaskIndex].UserData = UserData;
	}
}

/*===========================================================================
 *      End of Set Task Information
 *=========================================================================*/
