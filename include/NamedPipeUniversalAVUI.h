#pragma once

//wchar_t *NamedPipeUniversalAVUI_GetCurrentStatus();

ULONGLONG NamedPipeUniversalAVUI_GetNumberOfNewHashes();

void NamedPipeUniversalAVUI_GetSampleFileInfo(OUT ULONGLONG *pnumber_of_requested_file_by_the_server, 
											  OUT ULONGLONG *pnumber_of_files_successfully_uploaded,
											  OUT ULONGLONG *pnumber_of_files_not_successfully_uploaded,
											  OUT ULONGLONG *pnumber_of_missing_files);

BOOLEAN NamedPipeUniversalAVUI_IsSubmitForScanEnabled();

DWORD NamedPipeUniversalAVUI_SubmitForScan();

ULONGLONG NamedPipeUniversalAVUI_GetNumberOfUploadedHash();

int NamedPipeUniversalAVUI_GetNumberOfLocalNtfsHardDisk(OPTIONAL OUT BOOLEAN drive[26]);

DWORD NamedPipeUniversalAVUI_GetScanResultV2();

DWORD NamedPipeUniversalAVUI_SetDailyUploadLimit(ULONGLONG daily_upload_limit_in_bytes);

BOOLEAN NamedPipeUniversalAVUI_IsProcessingScanResult();

DWORD NamedPipeUniversalAVUI_RefreshScanResult();

DWORD NamedPipeUniversalAVUI_PurgeUAVLogFile();

//////////////////////////////////////////////////////////////////////////////////////

DWORD NamedPipeUniversalAVUI_EnableUpload(BOOLEAN bEnable);

DWORD NamedPipeUniversalAVUI_EnableGoodNews(BOOLEAN bEnable);

//////////////////////////////////////////////////////////////////////////////////////

DWORD NamedPipeUniversalAVUI_SaveUAVEngines(const char *data);
DWORD NamedPipeUniversalAVUI_SaveExcludedUAVEngines(const char *data);

//////////////////////////////////////////////////////////////////////////////////////

DWORD NamedPipeUniversalAVUI_EnableSearchOptimization(BOOLEAN bEnable);

//////////////////////////////////////////////////////////////////////////////////////

DWORD NamedPipeUniversalAVUI_RefreshUAVStatus();
