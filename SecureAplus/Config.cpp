#include "Config.h"
#include<qDebug>

Config* Config::m_instance = nullptr;
Config * Config::getInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new Config();
	}

	return m_instance;

}

QString Config::getConfigValue(QString value)
{
	//QStringList childKeys = settings->allKeys();
	return settings->value(value).toString();
}

Config::~Config()
{
	settings->endGroup();
}

//Theme_Type Config::getThemeMode()
//{
//	return m_current_Mode;
//}
//
//void Config::setMode(Theme_Type mode)
//{
//	m_current_Mode = mode;
//}



Config::Config()
{
	settings = new QSettings("config.ini", QSettings::IniFormat);
	//settings->beginGroup("Color");
	//QSettings settings("config.ini", QSettings::IniFormat);
	//settings.beginGroup("Color");
	////QStringList childKeys = settings.allKeys();

	//qDebug() << "background" << settings.value("background").toString();
	//settings.endGroup();
	//m_current_Mode = Theme_Type::Dark_Theme;
}
