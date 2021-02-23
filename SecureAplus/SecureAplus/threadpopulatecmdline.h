#ifndef THREADPOPULATESCRIPT_H
#define THREADPOPULATESCRIPT_H

typedef BOOLEAN(*callback_populate_certificate)(void *context, const wchar_t *command, int rule, BOOLEAN bCaseInsensitive, const wchar_t *param, int action);

// Struct for thread context (param)
typedef struct _PARAM_THREAD_POPULATE_CMDLINE
{
	void* callback_parent_obj;
	callback_populate_cmdline callback;
	HANDLE hStopEvent;
	HANDLE hCompletedEvent;
} PARAM_THREAD_POPULATE_CMDLINE, * PPARAM_THREAD_POPULATE_CMDLINE;

HANDLE CreateThreadPopulateCmdline(void* callback_parent_obj, callback_populate_cmdline callback, HANDLE hStopEvent, HANDLE hCompletedEvent);
DWORD WINAPI ThreadPopulateCmdline(LPVOID lpParam);

#endif // THREADPOPULATESCRIPT_H
