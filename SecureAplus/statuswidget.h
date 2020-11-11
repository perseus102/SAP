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

namespace Ui {
	class StatusWidget;
}

class StatusWidget : public QWidget
{
	Q_OBJECT

public:
	StatusWidget(QWidget *parent = Q_NULLPTR);
	~StatusWidget();


signals:
	void toggleChanged(bool isChecked);

public slots:
	void protectionModeChanged(Protection_Modes mode);
	void toggleClicked();
	void changeTheme();

private:
	Ui::StatusWidget	*ui;
	QLabel				*m_statusIcon;
	QLabel				*m_statusText;
	QVBoxLayout			*m_statusLayout;
	Switch				*m_toggle;
	QWidget				*m_iconWidget;
	QIcon				m_icon;
	void setStyle();
	void setIcon();
};

#endif