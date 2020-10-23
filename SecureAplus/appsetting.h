#pragma once

#include <QWidget>
#include <qDebug>
#include <QVBoxLayout>
#include <QLabel>
#include "Config.h"
#include "define.h"
#include <QIcon>
#include <QPainter>

class AppSetting : public QObject
{
	Q_OBJECT

public:
	static AppSetting* getInstance();
	~AppSetting();


	void setStatus(Status status);
	Status getStatus();

	void setTheme(Theme_Type theme);
	Theme_Type getTheme();

signals:
	void signal_changeTheme();

private:
	AppSetting();
	static AppSetting* m_instance;
	Status m_currentStatus;
	Theme_Type m_themeType;
};