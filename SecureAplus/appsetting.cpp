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
	m_themeType = Theme_Type::Light_Theme;
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