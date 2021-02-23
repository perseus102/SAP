#include "SafeParamThreadExportWhitelist.h"

BOOLEAN callback_progress_thread_export_whitelist(LPVOID lpContext, ULONGLONG pos, ULONGLONG max)
{
	SafeParamThreadExportWhitelist* param = (SafeParamThreadExportWhitelist*)lpContext;

	param->lock();
	param->pos = pos;
	param->max = max;
	param->unlock();
	return TRUE;
}

SafeParamThreadExportWhitelist::SafeParamThreadExportWhitelist()
{
	filename = NULL;
}

SafeParamThreadExportWhitelist::~SafeParamThreadExportWhitelist()
{
	if (filename) free(filename);
	filename = NULL;
}

void freeSafeParamThreadExportWhitelist(SafeParamThreadExportWhitelist *paramThreadExportWhitelist, HANDLE hThreadExportWhitelist)
{
	BOOLEAN bFree = FALSE;

	if (paramThreadExportWhitelist)
	{
		paramThreadExportWhitelist->stop();
		if (hThreadExportWhitelist)
		{
			WaitForSingleObject(hThreadExportWhitelist, INFINITE);
		}

		paramThreadExportWhitelist->lock();
		if (paramThreadExportWhitelist->isCompleted())
		{
			bFree = TRUE;
		}
		paramThreadExportWhitelist->unlock();
	}
	
	if (bFree)
	{
		delete paramThreadExportWhitelist;
		paramThreadExportWhitelist = NULL;
	}	
}
