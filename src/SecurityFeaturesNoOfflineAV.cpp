#include "stdafx.h"
#include <atlstr.h>
#include <qstring.h>
#include <QObject>
#include "Expiry.h"
#include "registry.h"
#include "ServiceStatusString.h"
#include "UniversalAV_NamedPipeClient.h"
#include "UniversalAV_Enable.h"
#include "DriverCommand.h"
#include "Mode.h"
#include "SecurityFeaturesNoOfflineAV.h"
// #include "OfflineAV.h" // UNCOMMENT TO ENABLE AVIRA CHECK
// #include "SAAvira.h" // UNCOMMENT TO ENABLE AVIRA CHECK
// #include "OfflineAVAvailable.h" // UNCOMMENT TO ENABLE AVIRA CHECK
#include "DeepAVAvailable.h"
#include "SecureAPlusLite.h"

#ifdef INCLUDE_SEARCH_SERVICE
const wchar_t *secureaplus_status_service_name[MAX_STATUS_ITEM]={L"License", L"SAAppCtl", L"SAAppSvc", L"SecureAPlusService", L"SAEverythingServer", L"SAUAVSvc", L"SAScan", L"SAScanSvc", L"ClamAV"};
#else
const wchar_t *secureaplus_status_service_name[MAX_STATUS_ITEM]={L"License", L"SAAppCtl", L"SAAppSvc", L"SecureAPlusService", L"SAUAVSvc", L"SAScan", L"SAScanSvc", L"ClamAV"};
#endif 
/*
const wchar_t *dialog_status_item[MAX_STATUS_ITEM]={
	L"License",
	L"App Whitelisting Driver", 
	L"App Whitelisting Service", 
	L"SecureAPlus Service", 
	L"Search Service", 
	L"Universal AV Service", 
	L"Antivirus Driver",
	L"Antivirus Service",
	L"Offline Antivirus engine"};
*/
BOOLEAN bStatus[MAX_STATUS_ITEM];

QString dialog_status_item[MAX_STATUS_ITEM];
QString dialog_status_string[MAX_STATUS_ITEM];

QString qstr_av_service;
QString qstr_real_time_scanning;

BOOLEAN bCachedSecurityFeaturesStatus = 99;

void InitSecurityFeatures()
{
	static BOOLEAN bInit = FALSE;

	if (!bInit)
	{
		dialog_status_item[STATUS_SECUREAPLUS_LICENSE] = QObject::tr("License");
		dialog_status_item[STATUS_APP_WHITELISTING_DRIVER] = QObject::tr("App Whitelisting Driver");
		dialog_status_item[STATUS_APP_WHITELISTING_SERVICE] = QObject::tr("App Whitelisting Service");
		dialog_status_item[STATUS_SECUREAPLUS_SERVICE] = QObject::tr("SecureAPlus Service");
		#ifdef INCLUDE_SEARCH_SERVICE
		dialog_status_item[STATUS_SEARCH_SERVICE] = QObject::tr("Search Service");
		#endif
		dialog_status_item[STATUS_UNIVERSAL_AV_SERVICE] = QObject::tr("Universal AV Service");
		dialog_status_item[STATUS_ANTIVIRUS_DRIVER] = QObject::tr("Antivirus Driver");
		qstr_av_service = QObject::tr("Antivirus Service");
		qstr_real_time_scanning = QObject::tr("Real-time scanning");
		dialog_status_item[STATUS_ANTIVIRUS_SERVICE] = qstr_real_time_scanning;
		dialog_status_item[STATUS_OFFLINE_AV] = QObject::tr("Offline Antivirus engine");

		for (int i = 0; i < MAX_STATUS_ITEM; i++)
		{
			dialog_status_string[i] = "";
		}

		bInit = TRUE;
	}
}



BOOLEAN IsSAScanAvailable()
{
	BOOLEAN bAvailable = TRUE;
	DWORD dwLastError = 0;
	DWORD dwValue = 0;

	bAvailable = TRUE;
	dwLastError = RegQueryDwordValueW(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\services\\SAScan", L"Start", &dwValue);
	if (dwLastError == 0)
	{
		bAvailable = TRUE;
	}
	else
	{
		bAvailable = FALSE;
	}

	return bAvailable;
}

BOOLEAN IsSecurityFeaturesRunning()
{
	BOOLEAN bSecurityFeatures = TRUE;
	ULONGLONG current_time;
	QString title;
	QString msg;
	const wchar_t *service_name;
	static ULONGLONG prev_time = 0;
	CStringW sub_key;
	DWORD dwStatus;
	DWORD dwValue;
	DWORD dwLastError = 0;
	DWORD whitelist_mode;
	NTSTATUS status = 0;
	static ULONGLONG start_time = 0;
	BOOLEAN bAPEXAvailable;

	bAPEXAvailable = IsDeepAVAvailable();

	if (start_time==0)
	{
		GetSystemTimeAsFileTime((LPFILETIME)&start_time);
	}

	InitSecurityFeatures();

	GetSystemTimeAsFileTime((LPFILETIME)&current_time);
	for (int i = 0; i < MAX_STATUS_ITEM; i++)
	{
		title = dialog_status_item[i];
		service_name = secureaplus_status_service_name[i];

		switch(i)
		{
		case STATUS_SECUREAPLUS_LICENSE:
			if (IsSoftwareExpired())
			{
				if (IsEligibleForSecureAPlusLite())
				{
					//License is valid
					bStatus[i] = TRUE;
					msg = QObject::tr("Valid"); 
				}
				else
				{
					bStatus[i] = FALSE;
					if (RegValueExistW(HKEY_LOCAL_MACHINE, REGISTRY_EXPIRY, L"ExpiryDate"))
					{
						msg = QObject::tr("Expired");
					}
					else
					{
						msg = QObject::tr("Not available");
					}
				}
			}
			else
			{
				//License is valid
				bStatus[i] = TRUE;
				msg = QObject::tr("Valid"); 
			}
			break;

		case STATUS_OFFLINE_AV:
			// UNCOMMENT TO ENABLE AVIRA CHECK
			/*if (_wcsicmp(GetActiveEngine(), L"Avira")==0)
			{
				dwStatus = 0;
				dwValue = 0;
				sub_key.Format(L"SYSTEM\\CurrentControlSet\\services\\%s", L"savapi");
				dwLastError = RegQueryDwordValueW(HKEY_LOCAL_MACHINE, sub_key, _T("Start"), &dwValue);
				if (dwLastError != 0)
				{
					msg = QObject::tr("Not installed");
					bStatus[i] = FALSE;				
				}
				else
				{
					msg = GetServiceStateString(L"savapi", &dwStatus);

					if (dwStatus == SERVICE_RUNNING || dwStatus == SERVICE_START_PENDING)
					{
						bStatus[i] = TRUE;				
					}
					else
					{
						bStatus[i] = FALSE;				
					}
				}
			} else */
			if (IsDeepAVAvailable())
			{
				prev_time = current_time;
				bStatus[i] = TRUE;
				msg = QObject::tr("APEX");
			}
			else
			{
				prev_time = current_time;
				bStatus[i] = TRUE;
				msg = QObject::tr("Not available");
			}
			break;
			// ClamAV
			/////////////////////////////////////////////////////////////


		default:
			dwStatus = 0;
			dwValue = 0;
			sub_key.Format(L"SYSTEM\\CurrentControlSet\\services\\%s", service_name);
			dwLastError = RegQueryDwordValueW(HKEY_LOCAL_MACHINE, sub_key, _T("Start"), &dwValue);
			if (dwLastError != 0)
			{
				msg = QObject::tr("Not installed");
			}
			else
			{
				msg = GetServiceStateString(service_name, &dwStatus);
				if (dwStatus != SERVICE_RUNNING)
				{
					if (wcscmp(service_name, L"SAUAVSvc")==0)
					{
						//Another way to check
						if (IsUniversalAVNamedPipeAvailable())
						{
							dwStatus = SERVICE_RUNNING;
							msg = GetServiceStateQString(SERVICE_RUNNING);
						}
					}
				}
			}

			if (dwStatus == SERVICE_RUNNING || dwStatus == SERVICE_START_PENDING)
			{
				bStatus[i] = TRUE;				
				switch(i)
				{
				case STATUS_APP_WHITELISTING_DRIVER:
					whitelist_mode = GetApplicationWhitelistingMode();
					if (whitelist_mode >= TRUST_ALL_FOR_5_MINUTES || (IsSoftwareExpired() && !IsEligibleForSecureAPlusLite()))
					{
						msg = QObject::tr("Trust all mode");
						bStatus[i] = FALSE;
					}
					break;

				case STATUS_ANTIVIRUS_SERVICE:
					if (IsSAScanDisabled(&status))
					{
						DWORD dwDisableOfflineAV = FALSE;
						DWORD dwLastError;

						if (IsDeepAVAvailable()) dwDisableOfflineAV = TRUE; // COMMENT TO ENABLE AVIRA CHECK
						
						// UNCOMMENT ALL BELOW TO ENABLE AVIRA CHECK
						// if (!IsOfflineAVAvailable()) dwDisableOfflineAV = TRUE; 

						//if (dwDisableOfflineAV == FALSE)
						//{
						//	dwDisableOfflineAV = !IsOfflineAVEnabled();
						//}

						if (!IsUniversalAVEnabled() && dwDisableOfflineAV)
						{
							//Both UAV and Offline AV are off, so real-time off is expected, not a security risk.
							bStatus[i] = TRUE;	
						}
						else
						{
							bStatus[i] = FALSE;	
						}

						msg = QObject::tr("Off");
					}
					else
					{
						bStatus[i] = TRUE;
						msg = QObject::tr("On");
					}
					break;
				}				
			}
			else
			{
				bStatus[i] = FALSE;	
				/*
				if ((current_time - start_time) > 10000000I64 * 30)
				{
					//It has been more than 30 seconds not running
					bStatus[i] = FALSE;	
				}
				else
				{
					// Wait until it run. 
					// Since the service is running, we will give a few minutes until it runs
					bStatus[i] = TRUE;
				}
				*/
				//bStatus[i] = FALSE;	
				//There are several exceptions, in some cases they may not be consider as "At Risk".				
				switch(i)
				{
					case STATUS_UNIVERSAL_AV_SERVICE:
						if (IsUniversalAVAvailable())
						{
							if (dwLastError == 0 && dwValue != SERVICE_AUTO_START && dwValue != SERVICE_BOOT_START)
							{
								msg = QObject::tr("Disabled");
								bStatus[i] = TRUE;
							}
						}
						else
						{
							bStatus[i] = TRUE;
							msg = QObject::tr("Not available");
						}
						break;

					case STATUS_ANTIVIRUS_SERVICE:
					case STATUS_ANTIVIRUS_DRIVER:
						if (IsSAScanAvailable())
						{
							if (dwLastError == 0 && dwValue != SERVICE_AUTO_START && dwValue != SERVICE_BOOT_START)
							{
								//Exception, this is not a security risk.
								bStatus[i] = TRUE;
								msg = QObject::tr("Disabled");
								if (i==STATUS_ANTIVIRUS_SERVICE)
								{
									NTSTATUS status;
									if (!IsSAScanDisabled(&status))
									{
										//Real-time is enabled, but the service is not running, this is a risk
										bStatus[i] = FALSE;
									}
									dialog_status_item[STATUS_ANTIVIRUS_SERVICE] = qstr_av_service;
								}
							}
						}
						else
						{
							if (i==STATUS_ANTIVIRUS_SERVICE)
							{
								dialog_status_item[STATUS_ANTIVIRUS_SERVICE] = qstr_av_service;
							}
							bStatus[i] = TRUE;
							msg = QObject::tr("Not available");
						}
						break;
				}
			}
			break;

		}

		if (bStatus[i]==FALSE) 
		{
			bSecurityFeatures = FALSE;
		}

		if (dialog_status_string[i].compare(msg) != 0)
		{
			dialog_status_string[i] = msg;
		}
	}

	bCachedSecurityFeaturesStatus = bSecurityFeatures;

	return bSecurityFeatures;
}

BOOLEAN GetCachedSecurityFeaturesStatus()
{
	if (bCachedSecurityFeaturesStatus == 99)
	{
		bCachedSecurityFeaturesStatus = IsSecurityFeaturesRunning();
	}

	return bCachedSecurityFeaturesStatus;
}

BOOLEAN GetSecurityFeatureStatus(int index)
{
	return bStatus[index];
}

void getSecurityFeatureString(OUT QString &str, int index)
{
	str = QString("%1: %2") . arg(dialog_status_item[index], dialog_status_string[index]);
}