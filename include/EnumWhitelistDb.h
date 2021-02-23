#pragma once
#include "WhitelistDb.h"

char *URLEncodeWhitelistName(LPCSTR filename);
//char *URLDecodeWhitelistName(LPCSTR filename);

ULONGLONG EnumWhitelistHashTable(HTABLE whitelist_hashtable, LPVOID lpContext, OPTIONAL LPCRITICAL_SECTION pcs, BOOLEAN(*callback)(LPVOID lpContext, PWHITELIST_KEY pKey, PWHITELIST_DATA pData, ULONGLONG pos, ULONGLONG max), BOOLEAN bAutoURLEncode = FALSE);

ULONGLONG EnumWhitelistFile(LPCWSTR filename, LPVOID lpContext, OPTIONAL LPCRITICAL_SECTION pcs, BOOLEAN(*callback)(LPVOID lpContext, PWHITELIST_KEY pKey, PWHITELIST_DATA pData, ULONGLONG pos, ULONGLONG max), BOOLEAN bAutoURLEncode = FALSE);
ULONGLONG EnumWhitelistDatabase(LPVOID lpContext, OPTIONAL LPCRITICAL_SECTION pcs, BOOLEAN(*callback)(LPVOID lpContext, PWHITELIST_KEY pKey, PWHITELIST_DATA pData, ULONGLONG pos, ULONGLONG max), BOOLEAN bAutoURLEncode = FALSE);
