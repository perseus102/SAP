#ifndef THREADPOPULATESCRIPT_H
#define THREADPOPULATESCRIPT_H

typedef BOOLEAN(*callback_populate_scripts)(void* obj, LPCWSTR interpreter, LPCWSTR extensions);

// Struct for thread context (param)
typedef struct _PARAM_THREAD_POPULATE_SCRIPT
{
	void* callback_parent_obj;
	callback_populate_scripts callback;
	HANDLE hStopEvent;
	HANDLE hCompletedEvent;
} PARAM_THREAD_POPULATE_SCRIPT, * PPARAM_THREAD_POPULATE_SCRIPT;

HANDLE CreateThreadPopulateScript(void* callback_parent_obj, callback_populate_scripts callback, HANDLE hStopEvent, HANDLE hCompletedEvent);
DWORD WINAPI ThreadPopulateScript(LPVOID lpParam);

#endif // THREADPOPULATESCRIPT_H
