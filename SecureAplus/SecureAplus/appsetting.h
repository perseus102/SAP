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
	Status refreshStatus();

	void setTheme(Theme_Type theme);
	Theme_Type getTheme();

	Protection_Modes getProtectionMode();
	void setProtectionMode(Protection_Modes mode);
	QRect getAppGeometry();
	void setAppGeometry(QRect geometry);
	void setFullScreen(bool fullScreen);
	bool isFullScreen();
	void changePrevMode();
	Protection_Modes getPrevMode();
	License getLicense();
	void setLicense(License license);
	void changeProtectModeByOtherSetting(Protection_Modes mode);
	bool getManagedByServer();

public slots:
	void changeProtectionMode(Protection_Modes mode, bool editMode = false);
	void toggleClicked(bool isChecked);
	void appChangeScreen(Screen screen);

signals:
	void signal_changeTheme();
	void signal_changeMode(Protection_Modes mode);
	void signal_toggleChanged(bool isChecked);
	void signal_getAppGeometry();
	void signal_changeStatus();
	void signal_changeToPrevMode();
	void signal_ChangeModeByOtherSetting(Protection_Modes mode);
	void signal_ChangeScreen(Screen screen);

private:
	AppSetting();
	static AppSetting* m_instance;
	Status m_currentStatus;
	Theme_Type m_themeType;
	Protection_Modes m_protectionMode;
	Protection_Modes m_prevProtectionMode;
	QRect m_appGeometry;
	bool m_isFullScreen;
	License m_appLicense;
	bool m_appManagedByServer;
};
