#pragma once

//To write to the log, please include the following in the stdafx.h:
//#include "log.h"

typedef struct _EXPIRY_TIME
{
	FILETIME start;
	ULONGLONG length;
	FILETIME expiry;
} EXPIRY_TIME, *PEXPIRY_TIME;

DWORD _SetExpiryDate(ULONGLONG start_date, ULONGLONG length, ULONGLONG expiry_date, BOOLEAN bLock = TRUE);
DWORD SetExpiryDate(ULONGLONG start_date, ULONGLONG length, ULONGLONG expiry_date);
DWORD GetExpiryDate(OPTIONAL PULONGLONG pStartDate, OPTIONAL PULONGLONG pLengthOfPeriod, OPTIONAL PULONGLONG pExpiryDate);

unsigned __int64 GetValidStartDate();

BOOLEAN IsAppExpired(unsigned __int64 start_date, unsigned __int64 length, unsigned __int64 expiry_date,  unsigned __int64 today_date, OPTIONAL IN BOOLEAN bWriteLog = FALSE);

FILETIME GetExpiryFileTime();

unsigned __int64 NumberOfDaysBeforeExpire();

#ifdef SECUREAPLUS_SYNC_EXPIRY_DATE_WITH_SERVER
BOOLEAN IsSoftwareExpired(BOOLEAN bWriteLog = FALSE, BOOLEAN bSyncWithServer = FALSE);
#else
BOOLEAN IsSoftwareExpired(BOOLEAN bWriteLog = FALSE);
#endif

wchar_t *GetLicenseString();

//BOOLEAN ExpiryDateExists();

BOOLEAN IsInvalidExpiryDate();

DWORD SetExpiryDateByFileTime(PFILETIME pftExpiry);

#define REGISTRY_EXPIRY _T("SYSTEM\\CurrentControlSet\\Services\\SAPlus")

unsigned __int64 NumberOfMSecBeforeExpire();
