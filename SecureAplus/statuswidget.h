#pragma once

#ifndef STATUSWIDGET_H
#define STATUSWIDGET_H

#include <QWidget>
#include <qDebug>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "Config.h"
#include "define.h"
#include "ui_statuswidget.h"
#include "switch.h"

namespace Ui {
	class StatusWidget;
}

class StatusWidget : public QWidget
{
	Q_OBJECT

public:
	StatusWidget(QWidget *parent = Q_NULLPTR);
	~StatusWidget();

	void setBackground(ColorType type);
	void setIcon(ColorType type);

signals:
	void setActive();

private:
	Ui::StatusWidget	*ui;
	QLabel				*m_statusIcon;
	QLabel				*m_statusText;
	QVBoxLayout			*m_statusLayout;
	Switch* switch4;

};

#endif