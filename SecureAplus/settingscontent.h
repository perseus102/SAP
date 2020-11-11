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
#include "languagepersonal.h"
#include "protectionmodes.h"

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

public slots:
	void onFadeInFinished();
	void changeSettingsView(QString widgetName);
	void backBtnPressed();

protected:
	void showEvent(QShowEvent *);

private:
	Ui::SettingsContent *ui;

	QPropertyAnimation		*mpFadeIn;
	QGraphicsOpacityEffect	*eff;

	QLabel				*m_settingIcon;
	QLabel				*m_settingText;
	QVBoxLayout			*m_settingLayout;
	QStackedWidget		*stackedWidget;
	TopBar				*m_settingTopBar;
	SettingGridContent	*m_SettingGridContent;
	LanguagePersonal	*m_languagePersonal;
	ProtectionModes		*m_protectionModes;
};
