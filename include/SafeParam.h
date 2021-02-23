#pragma once

#include "stdafx.h"

class SafeParam
{
public:
	SafeParam();
	~SafeParam();

	void lock();
	void unlock();

	void stop(HANDLE hThreadToWaitFor);
	void stop();
	BOOLEAN isStop();

	void setCompleted(OUT BOOLEAN *bNeedToBeFreed);
	BOOLEAN isCompleted();

	//if returned TRUE, the caller can hands off the responsibility to free the allocated memory
	BOOLEAN setLeftByCallerIfNotCompleted();

public:
	HANDLE hStopEvent;
	ULONGLONG pos, max;
	DWORD dwLastError;

private:
	CRITICAL_SECTION cs;
	BOOLEAN bLeftByCaller;
	BOOLEAN bCompleted;
};

