#pragma once

#ifndef HOMEWIDGET_H
#define HOMEWIDGET_H

#include <QWidget>
#include <qDebug>
#include <QVBoxLayout>
#include <QLabel>
#include "Config.h"
#include "define.h"
#include <QIcon>
#include <QtXml>
#include <QSvgRenderer>
#include "ui_homewidget.h"
#include "util.h"
#include "appsetting.h"
#include <QGraphicsOpacityEffect>

namespace Ui {	
	class HomeWidget;
}

class HomeWidget : public QWidget
{
	Q_OBJECT

public:
	HomeWidget(QWidget *parent = Q_NULLPTR);
	~HomeWidget();

	void changeBackground(ColorType type);
	void setWidgetText(QString text);
	void setSelected(bool isSeletected);
	void changeStatus();
	void setIcon();
	void setWidgetTextStyle();
	void setBackground();

signals:
	void setActive();

public slots:
	void changeTheme();

protected:
	void mousePressEvent(QMouseEvent *event);

private:
	Ui::HomeWidget	*ui;
	QLabel			*m_homeIcon;
	QLabel			*m_homeText;
	QVBoxLayout		*m_homeLayout;
	bool			m_Selected;


};
#endif