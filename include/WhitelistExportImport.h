#pragma once

BOOLEAN IsHashtableResizing();

DWORD ExportWhitelistDb(LPCWSTR filename, BOOLEAN bOverwriteWhitelist = FALSE, OPTIONAL HANDLE hStopEvent = NULL, OPTIONAL BOOLEAN(*callback_progress)(LPVOID lpContext, ULONGLONG pos, ULONGLONG max) = NULL, OPTIONAL LPVOID lpContext = NULL);

DWORD ImportWhitelistDbV2(LPCWSTR filename);

#define ImportWhitelistDb(filename) import_sawl(filename)

//Include everything
void ClearExcludedExportWhitelist();

//Exclude everything, except TAG_SMS_OS_VERSION and TAG_SMS_COMPUTER_INFORMATION
void ExcludeAllExportWhitelist();

void SetExcludedExportWhitelist(unsigned long tag);
void SetIncludedExportWhitelist(unsigned long tag);

///////////////////////////////////////////////////////////////////////////////////////////////////////

DWORD ExportOverwriteCommandLineRules(LPCWSTR filename, OPTIONAL HANDLE hStopEvent = NULL);
