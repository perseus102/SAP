/*
Requires:
	registry.cpp, error.cpp, FileVersionInfo.cpp, files.cpp, version.cpp

Library:
	Version.lib
*/

#ifndef _LOG_H_
#define _LOG_H_

#ifndef COMPANY_NAME
#define COMPANY_NAME _T("SecureAge")
#endif

#ifndef LOG_FILENAME
#define LOG_FILENAME _T("SecureAPlus.log")
#endif

void SetProcessTag();

wchar_t *GetTimeStampW();
char *GetTimeStampA();

wchar_t *GetLogFolderW();
TCHAR *GetLogFilename();

void AddHashToLog(IN OUT char *buffer, size_t buffer_len);

BOOLEAN WriteLogStringToFileW(LPCWSTR filename, const wchar_t *buffer);
#define WriteLogStringW(buffer) WriteLogStringToFileW(GetLogFilename(), buffer);

BOOL WriteLogA(LPCSTR format, ...);
BOOL WriteLogW(LPCWSTR format, ...);

/*
BOOL WriteErrorLogW(DWORD ErrorCode, LPCWSTR format, ...);
BOOL WriteErrorLogA(DWORD ErrorCode, LPCSTR format, ...);
*/

// automatically add \r\n at the back
#define write_logW(format, ...) WriteLogW(format L"\r\n", __VA_ARGS__)
#define write_logA(format, ...) WriteLogA(format "\r\n", __VA_ARGS__)

/*
BOOL write_logW(LPCWSTR format, ...);
BOOL write_logA(LPCSTR format, ...);
*/
BOOLEAN write_error_logW(DWORD ErrorCode, LPCWSTR format, ...);
BOOLEAN write_error_logA(DWORD ErrorCode, LPCSTR format, ...);

void init_log(HMODULE hMODULE=NULL);

BOOLEAN write_log_check_redundancy(BOOLEAN bNoRedundant, LPCWSTR format, ...);
BOOLEAN write_error_log_check_redundancy(BOOLEAN bNoRedundant, DWORD ErrorCode, LPCWSTR format, ...);

#define write_log_no_redundant(format, ...) write_log_check_redundancy(TRUE, format , __VA_ARGS__)
#define write_error_log_no_redundant(error_code, format, ...) write_error_log_check_redundancy(TRUE, error_code, format , __VA_ARGS__)
//BOOL write_log_no_redundant(LPCWSTR format, ...);

#ifndef __cplusplus
void write_log_hex(BYTE *source, int length, const char *spaces_in_front);
#else
void write_log_hex(BYTE *source, int length, const char *spaces_in_front="");
#endif

BOOL debug_write_logW(LPCWSTR format, ...);
BOOL debug_write_logA(LPCWSTR format, ...);

void log_http_error(DWORD dwLastError, BOOLEAN bSSL, LPCSTR Hostname, WORD nServerPort, LPCSTR lpszObjectName, OPTIONAL LPWSTR status_code = NULL);

#if (UNICODE || _UNICODE)
#define GetTimeStamp GetTimeStampW
#define _write_log WriteLogW
#define write_log write_logW
#define write_error_log write_error_logW
#define debug_write_log debug_write_logW
#else
#define GetTimeStamp GetTimeStampA
#define _write_log WriteLogA
#define write_log write_logA
#define write_error_log write_error_logA
#define debug_write_log debug_write_logA
#endif


#endif