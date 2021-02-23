#pragma once
#include "stdafx.h"
#include "ht.h"

#pragma pack(push, 1)
// TODO: reference additional headers your program requires here

#pragma pack(pop)

BOOLEAN LockAndReadFile(
  __in          HANDLE hFile,
  __out         LPVOID lpBuffer,
  __in          DWORD nNumberOfBytesToRead,
  __out         LPDWORD lpNumberOfBytesRead,
  __in			LARGE_INTEGER offset,
  __out			DWORD *pdwLastError
);


//return 0 if successful, otherwise return error code
DWORD LockAndWriteFileByHandle(IN HANDLE hFile, IN void* buffer, IN ULONG length, IN PLARGE_INTEGER offset);

// length - length in bytes
DWORD LockAndReadFileByHandle(IN HANDLE hFile, IN void* buffer, IN ULONG length, IN PLARGE_INTEGER offset);

BOOLEAN FlushHashTable(HTABLE table_id);