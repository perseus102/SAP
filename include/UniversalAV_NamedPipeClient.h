#pragma once

BOOLEAN IsUniversalAVNamedPipeAvailable();

DWORD UniversalAV_NamedPipe_Report_Missing_File(LPCSTR utf8_filename_only, ULONGLONG filesize, BYTE *hash, size_t hash_size);

