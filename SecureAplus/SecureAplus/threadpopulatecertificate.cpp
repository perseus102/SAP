#include "stdafx.h"
#include "threadpopulatecertificate.h"
#include "EnumTrustedCertificate.h"

// Initialises the thread context (param) and runs the thread
HANDLE CreateThreadPopulateCertificate(void* callback_parent_obj, callback_populate_certificate callback, HANDLE hStopEvent, HANDLE hCompletedEvent)
{
	HANDLE hThread = NULL;
	PPARAM_THREAD_POPULATE_CERTIFICATE param;

	param = (PPARAM_THREAD_POPULATE_CERTIFICATE)malloc(sizeof(PARAM_THREAD_POPULATE_CERTIFICATE));
	if (param)
	{
		ZeroMemory(param, sizeof(PARAM_THREAD_POPULATE_CERTIFICATE));
		param->callback_parent_obj = callback_parent_obj;
		param->callback = callback;
		param->hStopEvent = hStopEvent;
		param->hCompletedEvent = hCompletedEvent;
		hThread = CreateThread(NULL, 0, ThreadPopulateCertificate, param, 0, NULL);
	}

	return hThread;
}

DWORD WINAPI ThreadPopulateCertificate(LPVOID lpParam)
{
	PPARAM_THREAD_POPULATE_CERTIFICATE param = (PPARAM_THREAD_POPULATE_CERTIFICATE)lpParam;
	DWORD dwLastError = 0;

	if (param == NULL)
	{
		dwLastError = ERROR_INVALID_PARAMETER;
		goto EXIT;
	}
	dwLastError = EnumTrustedCertificate(param->callback, param->callback_parent_obj, NULL, param->hStopEvent);

EXIT:
	if (param)
	{
		if (param->hCompletedEvent) SetEvent(param->hCompletedEvent);
		free(param);
	}

	if (dwLastError != 0)
	{
		// TODO: handle error
		/*char* error_msg_utf8;

		SetErrorMessageDisplayErrorCodeW(dwLastError, L"");
		error_msg_utf8 = wchar_to_utf8(GetErrorMessageW());
		if (error_msg_utf8)
		{
			add_vector_theme_msg(error_msg_utf8);
		}*/
	}

	return dwLastError;
}