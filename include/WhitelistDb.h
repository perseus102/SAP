#include "ht.h"
#include "hash.h"
#ifndef _WDMDDK_
#include "AppWhitelistDriverCmd.h"
#endif

#ifndef _WHITELIST_DB_H_
#define _WHITELIST_DB_H_
#ifndef USE_HASHTABLE
#define USE_HASHTABLE
#endif

//#define DEFAULT_HASHTABLE_SIZE 204600 //200K
//#define DEFAULT_HASHTABLE_SIZE 512000 //500K
#define DEFAULT_HASHTABLE_SIZE 2097152 //2M

#if (APPWHITELISTING_HASH_SIZE == 20)
#ifndef _WDMDDK_
#define WHITELIST_DB_FILENAME L"%systemroot%\\system32\\drivers\\whitelist.sa"
#else
#define WHITELIST_DB_FILENAME L"\\systemroot\\system32\\drivers\\whitelist.sa"
#endif
#endif
#if (APPWHITELISTING_HASH_SIZE == 32)
#ifndef _WDMDDK_
#define WHITELIST_DB_FILENAME L"%systemroot%\\system32\\drivers\\whitelist2.sa"
#else
#define WHITELIST_DB_FILENAME L"\\systemroot\\system32\\drivers\\whitelist2.sa"
#endif
#endif

#pragma pack(push, 1)
typedef struct {
	unsigned __int32 size;
	unsigned __int32 checksum;
	unsigned __int64 filesize;
	unsigned char hash_whole_file[APPWHITELISTING_HASH_SIZE];
	char filename[1]; //arbitrary size, terminated with NULL
} WHITELIST_KEY, *PWHITELIST_KEY;

/*
typedef struct {
	BYTE trust_level;
} HASH_AND_DATA, *PHASH_AND_DATA;
*/
typedef struct {
	unsigned __int32 size;
	unsigned __int32 checksum;
	unsigned char trust_level;
	//unsigned __int32 size_per_entry; //sizeof(HASH_AND_DATA). In the future, this size may grow, if we decided to put more data
	//HASH_AND_DATA data[1];
} WHITELIST_DATA, *PWHITELIST_DATA;

extern HTABLE whitelist_hashtable;

#pragma pack(pop)

BOOLEAN is_valid_whitelist_key(PWHITELIST_KEY pKey);

#ifndef _WDMDDK_
wchar_t *get_whitest_db_filename();

BOOLEAN IsAppWhitelistingDriverRunning();
HRESULT OpenAppWhitelistingCmd();
void CloseAppWhitelistingCmd();

HRESULT AppWhitelistingCmd(IN LPVOID  lpInBuffer OPTIONAL,
							IN DWORD  dwInBufferSize,
							IN OUT LPVOID  lpOutBuffer OPTIONAL,
							IN DWORD  dwOutBufferSize,
							OUT LPDWORD  lpBytesReturned);

//unsigned __int64 AppWhitelistingCmd_GetNumberOfWhitelistEntries(OUT OPTIONAL HRESULT *phr);

//filename - full path file name
//return trust_level
int AppWhitelistingCmd_GetTrustLevel(const wchar_t *filename, unsigned __int64 filesize, OUT OPTIONAL HRESULT *phr);

int AppWhitelistingCmd_GetTrustLevelFromDb(const wchar_t *filename, unsigned __int64 filesize, const UCHAR *hash_standard, const UCHAR *hash_whole_file, OUT OPTIONAL HRESULT *phr);

ULONG AppWhitelistingCmd_SetTrustLevelAndCertificate(const wchar_t *filename, unsigned __int64 filesize, const UCHAR *hash_whole_file, UCHAR trust_level, BOOLEAN bSetNonInstallerList, OUT OPTIONAL HRESULT *phr);

ULONG AppWhitelistingCmd_DeleteByHash(const wchar_t *filename_only, unsigned __int64 filesize, const UCHAR *hash_whole_file);
#endif

PWHITELIST_KEY allocate_whitelist_key_a(const char *filename_only_utf8, unsigned __int64 filesize, const unsigned char *hash_whole_file);
PWHITELIST_KEY allocate_whitelist_key(const wchar_t *filename_only, unsigned __int64 filesize, const unsigned char *hash_whole_file);

HTABLE create_memory_hashtable(unsigned __int64 size);
HTABLE create_hashtable(const wchar_t *filename, unsigned __int64 size, PFLT_INSTANCE instance);
HTABLE open_hashtable_set_max_size(const wchar_t *filename, BOOLEAN bWriteAccess, PFLT_INSTANCE instance, unsigned __int64 hashtable_max_size);
#define open_hashtable(filename, bWriteAccess, instance) open_hashtable_set_max_size(filename, bWriteAccess, instance, DEFAULT_HASHTABLE_SIZE);
//HTABLE open_hashtable(const wchar_t *filename, BOOLEAN bWriteAccess, PFLT_INSTANCE instance);
void close_hashtable(HTABLE hashtable);
HANDLE close_hashtable_in_thread(HTABLE ht, DWORD dwDelayInMSec, OPTIONAL LPVOID lpContext, OPTIONAL void(*callback_on_close)(LPVOID lpContext));

//BOOLEAN search_in_whitelist(HTABLE hashtable, const wchar_t *filename, unsigned __int64 filesize, OUT ENTRY *result);
//PHASH_AND_DATA search_whitelist_data_by_hash(const BYTE *hash, PWHITELIST_DATA pdata);

DWORD add_to_whitelist_utf8(HTABLE *hashtable, const char *filename_only, unsigned __int64 filesize, BYTE hash_whole_file[APPWHITELISTING_HASH_SIZE], BYTE trust_level);

#ifndef _WDMDDK_
DWORD add_to_whitelist(HTABLE *hashtable, const wchar_t *filename_only, unsigned __int64 filesize, BYTE hash_whole_file[APPWHITELISTING_HASH_SIZE], BYTE trust_level, OPTIONAL BOOLEAN bDriverLog = TRUE);
#define add_to_whitelist_hashtable_log(filename_only, filesize, hash_whole_file, trust_level, bDriverLog) add_to_whitelist(&whitelist_hashtable, filename_only, filesize, hash_whole_file, trust_level, bDriverLog)
#else
DWORD add_to_whitelist(HTABLE *hashtable, const wchar_t *filename_only, unsigned __int64 filesize, BYTE hash_whole_file[APPWHITELISTING_HASH_SIZE], BYTE trust_level);
#endif
#define add_to_whitelist_hashtable(filename_only, filesize, hash_whole_file, trust_level) add_to_whitelist(&whitelist_hashtable, filename_only, filesize, hash_whole_file, trust_level)

DWORD update_whitelist_if_exists(HTABLE *hashtable, const wchar_t *filename_only, unsigned __int64 filesize, BYTE hash_whole_file[APPWHITELISTING_HASH_SIZE], BYTE trust_level);

//user is responsible to free() the result
PWHITELIST_DATA get_whitelist_data_a(HTABLE *hashtable, const char *filename_only, unsigned __int64 filesize, const UCHAR *hash_whole_file);

//check whether whitelist entry exists. return TRUE if found
BOOLEAN whitelist_entry_exists_a(HTABLE *hashtable, const char *filename_only, unsigned __int64 filesize, const UCHAR *hash_whole_file);
BOOLEAN whitelist_entry_exists(HTABLE *hashtable, const wchar_t *filename_only, unsigned __int64 filesize, const UCHAR *hash_whole_file);

//return default_trust_level if not found
int get_trust_level_from_whitelist_default(HTABLE *hashtable, const wchar_t *filename_only, unsigned __int64 filesize, const UCHAR *hash_whole_file, int default_trust_level);
#define get_trust_level_from_whitelist_hashtable_default(filename_only, filesize, hash_whole_file, default_trust_level) get_trust_level_from_whitelist_default(&whitelist_hashtable, filename_only, filesize, hash_whole_file, default_trust_level)

//return 0 if not found
int get_trust_level_from_whitelist(HTABLE *hashtable, const wchar_t *filename_only, unsigned __int64 filesize, const UCHAR *hash_whole_file);
#define get_trust_level_from_whitelist_hashtable(filename_only, filesize, hash_whole_file) get_trust_level_from_whitelist(&whitelist_hashtable, filename_only, filesize, hash_whole_file)


DWORD delete_from_whitelist(HTABLE *hashtable, const wchar_t *filename_only, unsigned __int64 filesize, BYTE *hash_whole_file);
#define delete_from_whitelist_hashtable(filename_only, filesize, hash_whole_file) delete_from_whitelist(&whitelist_hashtable, filename_only, filesize, hash_whole_file)

DWORD use_new_whitelist_file();
DWORD delete_old_whitelist_file();

DWORD open_whitelist_hashtable(BOOLEAN bWriteAccess, PFLT_INSTANCE instance);
void close_whitelist_hashtable();
void close_whitelist_file_handles();

unsigned __int64 get_whitelist_number_of_entries();
unsigned __int64 get_whitelist_max_entries();


void set_whitelist_hashtable(HTABLE ht);

#ifndef _WDMDDK_
//return 0 on successful, otherwise return windows error code
DWORD save_hashtable(HTABLE table_id, const wchar_t *filename);
DWORD ExportWhitelistWithProgressBar(const wchar_t *filename, OPTIONAL DWORD dwProgressBarDelayInMSec, OPTIONAL LPVOID lpContext, OPTIONAL BOOLEAN (*callback_progress)(LPVOID context, ULONGLONG pos, ULONGLONG max));
DWORD ExportWhitelist(const wchar_t *filename);
DWORD ImportWhitelist(IN const wchar_t *filename, OUT HRESULT *hr);
DWORD get_hashtable_info(LPCWSTR filename, OUT OPTIONAL PULONGLONG pnumber_of_entries, OUT OPTIONAL PULONGLONG pmax_size);
ULONGLONG get_hashtable_number_of_entries(LPCWSTR filename);
#endif
//#define close_whitelist_hashtable() close_hashtable(whitelist_hashtable);

#endif