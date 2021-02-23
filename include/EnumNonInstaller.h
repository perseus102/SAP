#pragma once
DWORD EnumNonInstaller(BOOLEAN(*callback)(LPVOID lpContext, LPCWSTR filename, LPCWSTR cert_name), OPTIONAL LPVOID lpContext = NULL, OPTIONAL BOOLEAN(*callback_progress)(LPVOID lpContext, ULONGLONG pos, ULONGLONG max) = NULL, OPTIONAL HANDLE hStopEvent = NULL);
