#ifndef THREADPOPULATESCRIPT_H
#define THREADPOPULATESCRIPT_H
#include "WhitelistDb.h"

typedef BOOLEAN(*callback_populate_allowed_cmdline)(LPVOID lpContext, PWHITELIST_KEY pKey, PWHITELIST_DATA pData, ULONGLONG pos, ULONGLONG max);

// Struct for thread context (param)
typedef struct _PARAM_THREAD_POPULATE_ALLOWED_COMMAND_LINE
{
	void* callback_parent_obj;
	callback_populate_allowed_cmdline callback;
	HANDLE hStopEvent;
	HANDLE hCompletedEvent;
} PARAM_THREAD_POPULATE_ALLOWED_COMMAND_LINE, * PPARAM_THREAD_POPULATE_ALLOWED_COMMAND_LINE;

HANDLE CreateThreadPopulateAllowedCommandLine(void* callback_parent_obj, callback_populate_allowed_cmdline callback, HANDLE hStopEvent, HANDLE hCompletedEvent);
DWORD WINAPI ThreadPopulateAllowedCommandLine(LPVOID lpParam);

#endif // THREADPOPULATESCRIPT_H
