#pragma once
DWORD EnumTrustedCertificate(BOOLEAN(*callback)(LPVOID lpContext, LPCWSTR name, LPCWSTR thumbprint, FILETIME valid_from, FILETIME valid_to), OPTIONAL LPVOID lpContext = NULL, OPTIONAL BOOLEAN(*callback_progress)(LPVOID lpContext, ULONGLONG pos, ULONGLONG max) = NULL, OPTIONAL HANDLE hStopEvent = NULL);
