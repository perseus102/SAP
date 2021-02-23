#pragma once
#include "AppControl.h"
#if (APPWHITELISTING_HASH_SIZE == 20)
#include "sha1.h"
#endif
#if (APPWHITELISTING_HASH_SIZE == 32)
#include "sha256.h"
#endif

#if (APPWHITELISTING_HASH_SIZE == 20)
#define HASH_CTX	SHA1_CTX
#define HashInit	SHA1Init
#define HashUpdate	SHA1Update
#define HashFinal	SHA1Final
#endif

#if (APPWHITELISTING_HASH_SIZE == 32)
#define HASH_CTX sha256_context
#define HashInit	sha256_starts	
#define HashUpdate	sha256_update
#define HashFinal(digest, ctx)	sha256_finish(ctx, digest)
#endif

struct file_hash_and_trust
{
	BYTE hash_standard[APPWHITELISTING_HASH_SIZE];
	BYTE hash_whole_file[APPWHITELISTING_HASH_SIZE];
	BYTE trust_level;
};

extern BYTE salt[11];
extern int salt_size;

BOOLEAN IsStopHashing();

void SetStopHashing(BOOLEAN status);

void init_hash();
/*
#ifndef USE_HASHTABLE
DWORD calculate_sha1_header(__out BYTE hash_standard[APPWHITELISTING_HASH_SIZE], BYTE *salt, int salt_size, LPCWSTR filename, ULONGLONG *offset, BOOLEAN wait_if_file_is_locked, __out HASH_CTX *last_hash_ctx);
#endif
*/
DWORD continue_calculate_file_hash(__out BYTE hash_whole_file[APPWHITELISTING_HASH_SIZE], BYTE *salt, int salt_size, LPCWSTR filename, __inout ULONGLONG *offset, BOOLEAN wait_if_file_is_locked, __inout HASH_CTX *last_hash_ctx);

#ifndef _WDMDDK_
DWORD hash_file(__out BYTE hash_standard[APPWHITELISTING_HASH_SIZE], __out BYTE hash_whole_file[APPWHITELISTING_HASH_SIZE], BYTE *salt, int salt_size, LPCWSTR filename, BOOLEAN wait_if_file_is_locked, OUT OPTIONAL BOOLEAN *bExecutable = NULL, BOOLEAN bSlow=FALSE, HANDLE hStopEvent = NULL, DWORD slow_down_if_idle_time_less_than_in_seconds = INFINITE);
#else
DWORD hash_file(__out BYTE hash_standard[APPWHITELISTING_HASH_SIZE], __out BYTE hash_whole_file[APPWHITELISTING_HASH_SIZE], BYTE *salt, int salt_size, LPCWSTR filename, BOOLEAN wait_if_file_is_locked, OUT OPTIONAL BOOLEAN *bExecutable);
#endif

void stop_hash();

BOOLEAN IsNullHash(BYTE hash_value[APPWHITELISTING_HASH_SIZE]);

#ifdef _CPUUSAGE_H
BOOLEAN StartTimeLessThan5Minutes(DWORD *pelapsed_time_in_minutes /*= NULL*/);
#endif

void HashMemory(void *buffer, size_t buffer_size, OUT UCHAR *hash_whole_file);

void HashMemoryV2(void *buffer, size_t buffer_size, OUT UCHAR *hash_whole_file);

void Sha256ToSecureAPlusHash(BYTE *hash_standard, OUT BYTE *hash_secureaplus);