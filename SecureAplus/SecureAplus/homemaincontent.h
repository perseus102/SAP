#pragma once

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"

#include "ui_homemaincontent.h"

class FeatureDetailsLabel : public QLabel
{
	Q_OBJECT
public:
	FeatureDetailsLabel(QLabel *parent = Q_NULLPTR);
	~FeatureDetailsLabel();
signals:
	void clicked();
protected:
	void mousePressEvent(QMouseEvent* event);
};

namespace Ui {
	class HomeContent;
}

class HomeMainContent : public QWidget
{
	Q_OBJECT

public:
	HomeMainContent(QWidget *parent = Q_NULLPTR);
	~HomeMainContent();
	void setStatusText(QString text);
	void setLastScanText(QString text);
	void setSecurityFearuteText(QString text);
	void setSecureFearuteDetailsText(QString text);

signals:
	void scanNowButtonClicked();
	void featureDetailsClicked();

public slots:
	void scanButtonClick();
	void featureDetailsClick();
	void changeTheme();
	void changeStatus();

private:
	Ui::HomeMainContent *ui;
	QLabel	*m_statusIcon;
	QLabel	*m_statusText;
	QLabel	*m_lastScan;
	QLabel	*m_securityFeature;
	QLabel	*m_policy;
	QPushButton	*m_btn_scanNow;
	QGridLayout * m_vBoxlayout;
	FeatureDetailsLabel *m_featureDetails;
	void setIcon();
	void setStyle();

};


