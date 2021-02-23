#pragma once

DWORD EnumScript(BOOLEAN(*callback)(LPVOID lpContext, LPCWSTR interpreter, LPCWSTR extensions), OPTIONAL LPVOID lpContext = NULL, OPTIONAL BOOLEAN(*callback_progress)(LPVOID lpContext, ULONGLONG pos, ULONGLONG max) = NULL, OPTIONAL HANDLE hStopEvent = NULL);

