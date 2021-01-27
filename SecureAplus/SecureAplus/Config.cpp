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

Config::Config()
{
	settings = new QSettings("config.ini", QSettings::IniFormat);
}
