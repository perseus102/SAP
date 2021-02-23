#include "stdafx.h"
#include "threadpopulateallowedcommandline.h"
#include "EnumWhitelistDb.h"

// Initialises the thread context (param) and runs the thread
HANDLE CreateThreadPopulateAllowedCommandLine(void* callback_parent_obj, callback_populate_allowed_cmdline callback, HANDLE hStopEvent, HANDLE hCompletedEvent)
{
	HANDLE hThread = NULL;
	PPARAM_THREAD_POPULATE_ALLOWED_COMMAND_LINE param;

	param = (PPARAM_THREAD_POPULATE_ALLOWED_COMMAND_LINE)malloc(sizeof(PARAM_THREAD_POPULATE_ALLOWED_COMMAND_LINE));
	if (param)
	{
		ZeroMemory(param, sizeof(PARAM_THREAD_POPULATE_ALLOWED_COMMAND_LINE));
		param->callback_parent_obj = callback_parent_obj;
		param->callback = callback;
		param->hStopEvent = hStopEvent;
		param->hCompletedEvent = hCompletedEvent;
		hThread = CreateThread(NULL, 0, ThreadPopulateAllowedCommandLine, param, 0, NULL);
	}

	return hThread;
}

DWORD WINAPI ThreadPopulateAllowedCommandLine(LPVOID lpParam)
{
	PPARAM_THREAD_POPULATE_ALLOWED_COMMAND_LINE param = (PPARAM_THREAD_POPULATE_ALLOWED_COMMAND_LINE)lpParam;
	DWORD dwLastError = 0;

	if (param == NULL)
	{
		dwLastError = ERROR_INVALID_PARAMETER;
		goto EXIT;
	}
	dwLastError = EnumWhitelistDatabase(param, NULL, param->callback);

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