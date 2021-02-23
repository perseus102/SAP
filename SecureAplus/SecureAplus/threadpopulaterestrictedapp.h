#ifndef THREADPOPULATESCRIPT_H
#define THREADPOPULATESCRIPT_H

typedef BOOLEAN(*callback_populate_restricted_app)(void* obj, LPCWSTR filename, LPCWSTR certCN);

// Struct for thread context (param)
typedef struct _PARAM_THREAD_POPULATE_RESTRICTED_APP
{
	void* callback_parent_obj;
	callback_populate_restricted_app callback;
	HANDLE hStopEvent;
	HANDLE hCompletedEvent;
} PARAM_THREAD_POPULATE_RESTRICTED_APP, * PPARAM_THREAD_POPULATE_RESTRICTED_APP;

HANDLE CreateThreadPopulateRestrictedApp(void* callback_parent_obj, callback_populate_restricted_app callback, HANDLE hStopEvent, HANDLE hCompletedEvent);
DWORD WINAPI ThreadPopulateRestrictedApp(LPVOID lpParam);

#endif // THREADPOPULATESCRIPT_H
