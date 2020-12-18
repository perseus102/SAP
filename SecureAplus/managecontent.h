#pragma once

#include <QWidget>
#include "ui_managecontent.h"
#include <QStackedWidget>
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
#include "topbar.h"
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include "managegridcontent.h"
class ManageContent : public QWidget
{
	Q_OBJECT

public:
	ManageContent(QWidget *parent = Q_NULLPTR);
	~ManageContent();
	void fadeIn();
public slots:
	void onFadeInFinished();
	void changeManageView(QString widgetName);
	void backBtnPressed();
	void directoryClicked(Directory dir);
private:
	Ui::ManageContent ui;
	QPropertyAnimation		*mpFadeIn;
	QGraphicsOpacityEffect	*eff;
	QVBoxLayout			*m_manageLayout;
	QStackedWidget		*stackedWidget;
	TopBar				*m_manageTopBar;
	ManageGridContent	*m_manageGridContent;
	Directory			m_curManageDir;
};
