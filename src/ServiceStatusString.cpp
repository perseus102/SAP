#include "stdafx.h"
#include "service.h"
#include "ServiceStatusString.h"
#include <qobject.h>

QString qstring_service_status_not_installed;
QString qstring_service_status[SERVICE_PAUSED+2];

void InitQStringServiceStatus()
{
	BOOLEAN bInit = FALSE;

	if (!bInit)
	{
		qstring_service_status_not_installed = QObject::tr("Not installed");
		qstring_service_status[SERVICE_STOPPED] = QObject::tr("Not running");
		qstring_service_status[SERVICE_START_PENDING] = QObject::tr("Start pending");
		qstring_service_status[SERVICE_STOP_PENDING] = QObject::tr("Stop pending");
		qstring_service_status[SERVICE_RUNNING] = QObject::tr("Running");
		qstring_service_status[SERVICE_CONTINUE_PENDING]= QObject::tr("Continue pending");
		qstring_service_status[SERVICE_PAUSE_PENDING] = QObject::tr("Pause pending");
		qstring_service_status[SERVICE_PAUSED] = QObject::tr("Paused");
		qstring_service_status[SERVICE_PAUSED+1] = QObject::tr("Unknown state");
		bInit = TRUE;
	}
}

QString GetServiceStateQString(DWORD CurrentState)
{
	DWORD dwLastError = 0;

	InitQStringServiceStatus();

	if (CurrentState >= SERVICE_STOPPED && CurrentState <= SERVICE_PAUSED)
	{
		return qstring_service_status[CurrentState];
	}

	return qstring_service_status[SERVICE_PAUSED+1];
}

QString GetServiceStateString(__in const wchar_t *ServiceName, OUT OPTIONAL DWORD *pCurrentState)
{
	DWORD CurrentState = 0;
	DWORD dwLastError = 0;

	InitQStringServiceStatus();
	if (pCurrentState) *pCurrentState = CurrentState;
	dwLastError = QueryServiceCurrentState(ServiceName, &CurrentState);
	if (dwLastError != 0)
	{
		dwLastError = GetLastError();

		switch (dwLastError)
		{
		case ERROR_INVALID_HANDLE:
		case ERROR_SERVICE_DOES_NOT_EXIST:
			return qstring_service_status_not_installed;
			break;
		default:
			return QString(QObject::tr("Error %1").arg(dwLastError));
			break;
		}

		//return pstatus;
	}

	if (pCurrentState) *pCurrentState = CurrentState;

	return GetServiceStateQString(CurrentState);
}
