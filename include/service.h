#include <WinSvc.h>
#ifndef _SERVICE_H_
#define _SERVICE_H_

//#define SERVICE_NAME "Service Name"
//#define SERVICE_FILE_NAME "Service.exe"


DWORD InstallDriverW(wchar_t *ServiceName, wchar_t *FullPathFileName, DWORD dwStartType);
DWORD InstallDriverA(char *ServiceName, char *FullPathFileName, DWORD dwStartType);
DWORD InstallServiceW(wchar_t *ServiceName, LPCWSTR ServiceDisplayName, wchar_t *ServiceFullPathFileName, DWORD dwStartType= SERVICE_DEMAND_START);
DWORD InstallServiceA(char *ServiceName, LPCSTR ServiceDisplayName, char *ServiceFullPathFileName, DWORD dwStartType= SERVICE_DEMAND_START);
DWORD UninstallServiceW(wchar_t *ServiceName);
DWORD UninstallServiceA(char *ServiceName);
DWORD StartServiceW(const wchar_t *ServiceName);
DWORD StartServiceA(char *ServiceName);
DWORD StopServiceW(const wchar_t *ServiceName);
DWORD StopServiceA(char *ServiceName);

//Automatically add double quote if the filename contains space
DWORD InstallServiceSafeW(wchar_t *ServiceName, LPCWSTR ServiceDisplayName, wchar_t *filename, DWORD dwStartType= SERVICE_DEMAND_START);
DWORD SafeImagePathW(LPCWSTR ServiceName);

/*
Possible state value:
SERVICE_CONTINUE_PENDING
0x00000005
 The service continue is pending.
 
SERVICE_PAUSE_PENDING
0x00000006
 The service pause is pending.
 
SERVICE_PAUSED
0x00000007
 The service is paused.
 
SERVICE_RUNNING
0x00000004
 The service is running.
 
SERVICE_START_PENDING
0x00000002
 The service is starting.
 
SERVICE_STOP_PENDING
0x00000003
 The service is stopping.
 
SERVICE_STOPPED
0x00000001
 The service is not running.
*/
DWORD QueryServiceCurrentStateW(__in const wchar_t *ServiceName, __out DWORD *CurrentState);
DWORD QueryServiceCurrentStateA(__in const char *ServiceName, __out DWORD *CurrentState);

BOOLEAN IsServiceStoppedW(__in const wchar_t *ServiceName);

#define IsServiceRunningW IsDriverRunningW
BOOLEAN IsDriverRunningW(__in const wchar_t *ServiceName);
BOOLEAN IsDriverRunningA(__in const char *ServiceName);

wchar_t *get_service_state_string(DWORD CurrentState);

#if (UNICODE || _UNICODE)
#define QueryServiceCurrentState QueryServiceCurrentStateW
#define IsDriverRunning IsDriverRunningW
#define IsServiceRunning IsDriverRunningW
#define InstallDriver InstallDriverW
#define InstallService InstallServiceW
#define UninstallService UninstallServiceW
#define StopService StopServiceW
#else
#define QueryServiceCurrentState QueryServiceCurrentStateA
#define IsServiceRunning IsDriverRunningA
#define IsDriverRunning IsDriverRunningA
#define InstallDriver InstallDriverA
#define InstallService InstallServiceA
#define UninstallService UninstallServiceA
#define StopService StopServiceA
#endif

#endif
