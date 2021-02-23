#pragma once

ULONGLONG GetNumberOfInitialWhitelistEntries();
DWORD RecordInitialWhitelistEntries();

unsigned __int64 AppWhitelistingCmd_GetNumberOfWhitelistEntries(OUT OPTIONAL HRESULT *phr);


// Mode:
// 0 - Interactive, 
// 1 - LockDown, 
// 2 - Trust all for 5 minutes
// 3 - Trust all for 30 minutes
// 4 - Trust all until computer restarted
DWORD SetApplicationWhitelistingModeCmd(DWORD mode);
DWORD AppWhitelistingCmd_GetApplicationWhitelistingMode(OUT DWORD *pmode, OUT OPTIONAL ULONGLONG *ptrust_all_expiry_time);

DWORD AppWhitelistingCmd_EnableFileJournal();

DWORD AppWhitelistingCmd_SetBackgroundWhitelistingSpeed(DWORD speed);

//return 0 on successrul, other return NTSTATUS
ULONG AppWhitelistingCmd_SetTrustLevel(const wchar_t *filename_only, unsigned __int64 filesize, const UCHAR *hash_whole_file, UCHAR trust_level, OUT OPTIONAL HRESULT *phr, OPTIONAL BOOLEAN bDriverLog = TRUE);

//return TRUE if whitelist exists
//When return FALSE, GetLastError() to get the error code. If the error code is 0, that means the whitelist does not exist, otherwise the error code indicates the error while searching for the whitelist entries.
BOOLEAN AppWhitelistingCmd_WhitelistExists(const wchar_t *filename_only, unsigned __int64 filesize, const UCHAR *hash_whole_file);


//Stop auto trusting file by its previous file size and file hash
//Usually this will be automatically started after Windows Update
DWORD AppWhitelistingCmd_StopWhitelistFileSizeFileHash();

DWORD AppWhitelistingCmd_StartWhitelistFileSizeFileHash();

int AppWhitelistingCmd_GetTrustLevelByHash(const wchar_t *filename_only, unsigned __int64 filesize, const UCHAR *hash_whole_file, OUT OPTIONAL HRESULT *phr);

