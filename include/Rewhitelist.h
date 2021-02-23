#pragma once
BOOLEAN IsRewhitelisting();

DWORD SetRewhitelistMode(DWORD mode);
DWORD GetRewhitelistMode();

void SetStartRewhitelistFlags();
void StopRewhitelist();

///////////////////////////////////////////

void SetNumberOfWindowsFiles(ULONGLONG number_of_files, OPTIONAL CRITICAL_SECTION *pcs);
void AdjustNumberOfWindowsFiles(ULONGLONG number_of_files, OPTIONAL CRITICAL_SECTION *pcs);

DWORD SetRewhitelistMaxCounter(ULONGLONG size);
ULONGLONG GetRewhitelistMaxCounter();
