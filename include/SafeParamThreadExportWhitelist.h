#pragma once
#include "SafeParam.h"

BOOLEAN callback_progress_thread_export_whitelist(LPVOID lpContext, ULONGLONG pos, ULONGLONG max);

class SafeParamThreadExportWhitelist : public SafeParam
{
public:
	SafeParamThreadExportWhitelist();
	~SafeParamThreadExportWhitelist();

public:
	wchar_t *filename;
};

void freeSafeParamThreadExportWhitelist(SafeParamThreadExportWhitelist *paramThreadExportWhitelist, HANDLE hThreadExportWhitelist);

