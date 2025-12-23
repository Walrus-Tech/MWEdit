/*===========================================================================
 *
 * File:    TaskTime.H
 * Author:  Dave Humphrey (uesp@m0use.net)
 * Created On:  Friday, May 25, 2001
 *
 * Implements the CTaskTimer class for handling a simple timer which
 * calls functions every so many seconds.
 *
 *=========================================================================*/
#ifndef __TASKTIME_H
#define __TASKTIME_H


#include "Common/dl_err.h"


/* Number of different tasks we can handle */
#define MAX_TIMER_TASKS 20

/* The first valid task handle */
#define INITIAL_TASK_HANDLE 1

/* The timer interrupt under DOS */
#define DOS_TIMER_INT 0x1C


/* DOS timer interrupt function type */
SYS_MSDOS(typedef void interrupt (*PDOS_TIMER_INT)(...));

/* The task callback function type */
typedef int (*PTASK_FUNC)(const ulong LastCalled, long UserData);

/* Task handle used to identify tasks */
typedef int HTIMERTASK;

/* Holds the information for one task */
typedef struct {
	HTIMERTASK Handle; /* Used to identify the task */
	boolean Active;    /* Is the task currently active? */
	ulong TaskRate;    /* How many ms between task calls? */
	ulong LastCalled;  /* Number of ms since last call */
	PTASK_FUNC pFunc;  /* The task function to call */
	long UserData;     /* User data to pass to function */
} task_t;


/*===========================================================================
 *
 * Begin Class CTaskTimer Definition
 *
 * Handles a list of functions that should be called every so many
 * seconds.
 *
 *=========================================================================*/
class CTaskTimer {
  private:
	task_t m_Tasks[MAX_TIMER_TASKS]; /* Array of task information */
	int m_NumTasks;

	boolean m_Active;                /* Are we processing tasks? */
	boolean m_Initialized;           /* Is the timer initialized? */
	HTIMERTASK m_FreeTaskHandle;     /* Keeps track of available task handle */

	SYS_WIN32(uint m_TimerID;)       /* The timer ID in Win32 */


  protected:
	/* Find a task array index with the given handle */
	int GetTaskIndex(const HTIMERTASK hTask) const;


  public:
	/* Class Constructors/Destructors */
	CTaskTimer();
	virtual ~CTaskTimer() {
		Destroy();
	}

	virtual void Destroy();

	/* Add a new task to the list */
	virtual boolean AddTask(HTIMERTASK &hTask,
	                        const ulong Rate,
	                        PTASK_FUNC pFunc,
	                        const long UserData);

	/* Main task function */
	virtual boolean DoTasks(const ulong Count);

	/* Get class members */
	virtual int GetNumTasks() const;
	virtual boolean IsActive() const;
	virtual ulong GetTaskRate(const HTIMERTASK hTask) const;
	virtual ulong GetLastCalled(const HTIMERTASK hTask) const;
	virtual boolean IsActive(const HTIMERTASK hTask) const;
	virtual boolean IsValidTask(const HTIMERTASK hTask) const;
	virtual boolean IsValidTaskIndex(const int iTask) const;
	virtual boolean IsInitialized() const;

	/* Attempt to intialize the task timer */
	virtual boolean Initialize();

	/* Attempt to remove a task from the task array */
	virtual boolean RemoveTask(const HTIMERTASK hTask);

	/* Set class members */
	virtual void SetActive(const boolean Flag);
	virtual void SetActive(const HTIMERTASK hTask, const boolean Flag);
	virtual void SetTaskRate(const HTIMERTASK hTask, const ulong Rate);
	virtual void SetTaskFunc(const HTIMERTASK hTask, const PTASK_FUNC pFunc);
	virtual void SetUserData(const HTIMERTASK hTask, const long UserData);

	/* To store the previous timer in DOS */
	SYS_MSDOS(PDOS_TIMER_INT m_PrevTimerFunc;)
};


/* Get class members */
inline int CTaskTimer::GetNumTasks() const {
	return m_NumTasks;
}

inline boolean CTaskTimer::IsActive() const {
	return m_Active;
}

inline boolean CTaskTimer::IsInitialized() const {
	return m_Initialized;
}

inline boolean CTaskTimer::IsValidTaskIndex(const int TaskIndex) const {
	return (TaskIndex >= 0 && TaskIndex < m_NumTasks) ? TRUE : FALSE;
}

/* Set class members */
inline void CTaskTimer::SetActive(const boolean Flag) {
	m_Active = Flag;
}


/* The one and only task handler */
extern CTaskTimer TaskTimer;


#endif
