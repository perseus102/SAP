#include "appsetting.h"
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
	m_currentStatus = Status::Protected_Status;
	m_themeType = Theme_Type::Dark_Theme;
	m_protectionMode = Protection_Modes::Automatic_Mode; //can save and get from ini file
}

AppSetting::~AppSetting()
{
}

void AppSetting::setStatus(Status status)
{
	m_currentStatus = status;
}

Status AppSetting::getStatus()
{
	return m_currentStatus;
}

void AppSetting::setTheme(Theme_Type theme)
{
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



void AppSetting::toggleClicked(bool isChecked)
{
	if (!isChecked)
	{
		m_protectionMode = Protection_Modes::Interactive_Mode;
	}
	emit signal_toggleChanged(isChecked);
}

void AppSetting::changeProtectionMode(Protection_Modes mode)
{
	m_protectionMode = mode;
	emit signal_changeMode(mode);
}