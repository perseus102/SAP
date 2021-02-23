#include "SafeParam.h"

SafeParam::SafeParam()
{
	InitializeCriticalSection(&cs);
	hStopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	pos = 0; max = 0;
	dwLastError = 0;
	bCompleted = FALSE;
	bLeftByCaller = FALSE;
}

SafeParam::~SafeParam()
{
	DeleteCriticalSection(&cs);
}

void SafeParam::lock()
{
	EnterCriticalSection(&cs);
}

void SafeParam::unlock()
{
	LeaveCriticalSection(&cs);
}

void SafeParam::stop(HANDLE hThreadToWaitFor)
{
	if (hStopEvent)
	{
		SetEvent(hStopEvent);
		if (hThreadToWaitFor) WaitForSingleObject(hThreadToWaitFor, INFINITE);
	}
}

void SafeParam::stop()
{
	stop((HANDLE)NULL);
}

BOOLEAN SafeParam::isStop()
{
	BOOLEAN bResult = FALSE;

	if (hStopEvent && WaitForSingleObject(hStopEvent, 0)==0)
	{
		bResult = TRUE;
	}

	return bResult;
}

void SafeParam::setCompleted(OUT BOOLEAN *bNeedToBeFreed)
{
	lock();
	if (bNeedToBeFreed)
	{
		if (bLeftByCaller) *bNeedToBeFreed = TRUE;
		bCompleted = TRUE;
	}
	unlock();
}

BOOLEAN SafeParam::isCompleted()
{
	return bCompleted;
}


BOOLEAN SafeParam::setLeftByCallerIfNotCompleted()
{
	BOOLEAN bResult = FALSE;

	lock();
	if (!bCompleted)
	{
		bLeftByCaller = TRUE;
		bResult = TRUE;
	}
	unlock();

	return bResult;
}
