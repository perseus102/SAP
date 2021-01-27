#pragma once

#include <QWidget>
#include <QPropertyAnimation>
#include <qDebug>
#include <QVBoxLayout>
#include <QLabel>
#include <QIcon>
#include <QGraphicsOpacityEffect>
#include <QStackedWidget>
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
#include "ui_settingscontent.h"
#include "topbar.h"
#include "gridwidget.h"
#include "flowlayout.h"
#include "settinggridcontent.h"
#include "settingslanguagepersonal.h"
#include "settingsprotectionmodes.h"
#include "scansettings.h"

namespace Ui {
	class SettingsContent;
}
class SettingsContent : public QWidget
{
	Q_OBJECT

public:
	SettingsContent(QWidget *parent = Q_NULLPTR);
	~SettingsContent();

	void fadeIn();
	void changeToAntivirusTab();

public slots:
	void onFadeInFinished();
	void changeSettingsView(QString widgetName);
	void backBtnPressed();
	void directoryClicked(Directory dir);
protected:
	void showEvent(QShowEvent *);

private:
	Ui::SettingsContent *ui;

	QPropertyAnimation		*mpFadeIn;
	QGraphicsOpacityEffect	*eff;

	QVBoxLayout			*m_settingLayout;
	QStackedWidget		*stackedWidget;
	TopBar				*m_settingTopBar;
	SettingGridContent	*m_SettingGridContent;
	SettingsLanguagePersonal	*m_languagePersonal;
	SettingsProtectionModes		*m_protectionModes;
	ScanSettings		*m_scanSettings;
	Directory			m_curSettingDir;
};
