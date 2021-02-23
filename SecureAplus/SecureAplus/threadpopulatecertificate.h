#ifndef THREADPOPULATESCRIPT_H
#define THREADPOPULATESCRIPT_H

typedef BOOLEAN(*callback_populate_certificate)(LPVOID lpContext, LPCWSTR name, LPCWSTR thumbprint, FILETIME valid_from, FILETIME valid_to);

// Struct for thread context (param)
typedef struct _PARAM_THREAD_POPULATE_CERTIFICATE
{
	void* callback_parent_obj;
	callback_populate_certificate callback;
	HANDLE hStopEvent;
	HANDLE hCompletedEvent;
} PARAM_THREAD_POPULATE_CERTIFICATE, * PPARAM_THREAD_POPULATE_CERTIFICATE;

HANDLE CreateThreadPopulateCertificate(void* callback_parent_obj, callback_populate_certificate callback, HANDLE hStopEvent, HANDLE hCompletedEvent);
DWORD WINAPI ThreadPopulateCertificate(LPVOID lpParam);

#endif // THREADPOPULATESCRIPT_H
