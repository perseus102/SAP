#pragma once

#include <QWidget>
#include <QPropertyAnimation>
#include <QWidget>
#include <qDebug>
#include <QVBoxLayout>
#include <QLabel>
#include "Config.h"
#include "define.h"
#include <QIcon>
#include <QtXml>
#include <QSvgRenderer>
#include "util.h"
#include "appsetting.h"
#include <QGraphicsOpacityEffect>
#include "ui_homecontent.h"
#include <QStackedWidget>
namespace Ui {
	class HomeContent;
}
class HomeContent : public QWidget
{
	Q_OBJECT

public:
	HomeContent(QWidget *parent = Q_NULLPTR);
	~HomeContent();
	void fadeIn();

public slots:
	void onFadeInFinished();

protected:
	void showEvent(QShowEvent *);
	void resizeEvent(QResizeEvent *);
private:
	Ui::HomeContent *ui;
	QPropertyAnimation *mpFadeIn;
	//QPropertyAnimation *mpFadeOut;
	QGraphicsOpacityEffect *eff;
	QLabel			*m_homeIcon;
	QLabel			*m_homeText;
	QVBoxLayout		*m_homeLayout;

	QWidget *firstPageWidget;
	QWidget *secondPageWidget;
	QWidget *thirdPageWidget;
	QStackedWidget *stackedWidget;

};
