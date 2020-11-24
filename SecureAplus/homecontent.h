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
#include "ui_homecontent.h"
#include "homemaincontent.h"
#include "featuredetails.h"
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
	void showDetails();
protected:
	void showEvent(QShowEvent *);
	void resizeEvent(QResizeEvent *);

private:
	Ui::HomeContent *ui;
	QPropertyAnimation		*mpFadeIn;
	QGraphicsOpacityEffect	*eff;
	QLabel					*m_homeIcon;
	QLabel					*m_homeText;
	QVBoxLayout				*m_homeContentLayout;
	HomeMainContent			*m_homeMainContent;
	QStackedWidget			*stackedWidget;
	FeatureDetails			*m_featureDetails;
};
