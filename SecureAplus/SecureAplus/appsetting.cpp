#include "stdafx.h"
#include "appsetting.h"
#include "CatchPulseUserSettings.h"
#include "SecurityFeaturesNoOfflineAV.h"
AppSetting* AppSetting::m_instance = nullptr;

AppSetting * AppSetting::getInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new AppSetting();
	}

	return m_instance;
}

AppSetting::AppSetting()
{
	DWORD dwLastError = 0;

	m_currentStatus = Status::Protected_Status;
	m_protectionMode = Protection_Modes::Automatic_Mode; //can save and get from ini file
	m_appLicense = License::License_Expire_Soon;
	m_prevProtectionMode = Protection_Modes::Automatic_Mode;
	m_appManagedByServer = false; //call api for init
	dwLastError = getCurrentThemeCP((DWORD&)m_themeType);
	if (dwLastError) m_themeType = Theme_Type::Dark_Theme;
	dwLastError = getFullScreenCP((DWORD&)m_isFullScreen);
	if (dwLastError) m_isFullScreen = false;
}

AppSetting::~AppSetting()
{
}

// queries backend for current status
Status AppSetting::refreshStatus()
{
	BOOLEAN bProtected = GetCachedSecurityFeaturesStatus();

	if (bProtected)
	{
		m_currentStatus = Protected_Status;
		return Protected_Status;
	}
	else
	{
		m_currentStatus = Warning_Status;
		return Warning_Status;
	}
}

void AppSetting::setStatus(Status status)
{
	m_currentStatus = status;
	emit signal_changeStatus();
}

Status AppSetting::getStatus()
{
	return m_currentStatus;
}

void AppSetting::setTheme(Theme_Type theme)
{
	DWORD dwLastError;
	dwLastError = setCurrentThemeCP((DWORD)theme);
	m_themeType = theme;
	emit signal_changeTheme();
}

Theme_Type AppSetting::getTheme()
{
	return m_themeType;
}

Protection_Modes AppSetting::getProtectionMode()
{
	return m_protectionMode;
}

void AppSetting::setProtectionMode(Protection_Modes mode)
{
	m_prevProtectionMode = m_protectionMode;
	m_protectionMode = mode;
}

QRect AppSetting::getAppGeometry()
{
	emit signal_getAppGeometry();

	return m_appGeometry;
}

void AppSetting::setAppGeometry(QRect geometry)
{
	m_appGeometry = geometry;
}

void AppSetting::setFullScreen(bool fullScreen)
{
	DWORD dwLastError;
	dwLastError = setFullScreenCP((DWORD)fullScreen);
	m_isFullScreen = fullScreen;
}

bool AppSetting::isFullScreen()
{
	return m_isFullScreen;
}

void AppSetting::changePrevMode()
{
	emit signal_changeToPrevMode();
}

Protection_Modes AppSetting::getPrevMode()
{
	return m_prevProtectionMode;
}

License AppSetting::getLicense()
{
	return m_appLicense;
}

void AppSetting::setLicense(License license)
{
	m_appLicense = license;
}

void AppSetting::changeProtectModeByOtherSetting(Protection_Modes mode)
{
	m_prevProtectionMode = m_protectionMode;
	m_protectionMode = mode;
	signal_ChangeModeByOtherSetting(mode);
}

bool AppSetting::getManagedByServer()
{
	return m_appManagedByServer;
}

void AppSetting::toggleClicked(bool isChecked)
{
	if (!isChecked)
	{
		m_protectionMode = Protection_Modes::Interactive_Mode;
	}
	else
	{
		m_protectionMode = Protection_Modes::Automatic_Mode;
	}
	emit signal_toggleChanged(isChecked);
}

void AppSetting::appChangeScreen(Screen screen)
{
	emit signal_ChangeScreen(screen);
}



void AppSetting::changeProtectionMode(Protection_Modes mode, bool editMode)
{
	if (!editMode)
	{
		m_prevProtectionMode = m_protectionMode;
	}
	m_protectionMode = mode;
	emit signal_changeMode(mode);
}