#pragma once

#ifndef STATUSWIDGET_H
#define STATUSWIDGET_H

#include <QWidget>
#include <qDebug>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "ui_statuswidget.h"
#include "switch.h"
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
#include "circleprocess.h"
namespace Ui {
	class StatusWidget;
}

class StatusWidget : public QWidget
{
	Q_OBJECT

public:
	StatusWidget(QWidget *parent = Q_NULLPTR);
	~StatusWidget();

	void setTrustAllText(QString text);

signals:
	void toggleChanged(bool isChecked);

public slots:
	void protectionModeChanged(Protection_Modes mode);
	void toggleClicked();
	void changeTheme();
	void countDownFinished();
private:
	Ui::StatusWidget	*ui;
	QLabel				*m_statusIcon;
	QLabel				*m_statusText;
	QVBoxLayout			*m_statusLayout;
	Switch				*m_toggle;
	QWidget				*m_iconWidget;
	QIcon				m_icon;
	QLabel				*m_trustAllText;
	CircleProcess		*m_circleProcess;
	void setStyle();
	void setIcon();
	void setTrustAllMode();
};

#endif