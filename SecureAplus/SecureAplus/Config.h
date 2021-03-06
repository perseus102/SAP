#pragma once
#include <QString>
#include <QSettings>
#include <QStringList>

class Config
{

public:
	static Config*	getInstance();
	QString			getConfigValue(QString value);
	~Config();

private:
	Config();
	static Config* m_instance;
	QSettings *settings;
	const QStringList childKeys;
};

