#pragma once

#include <QWidget>
#include "ui_homewidget.h"

class HomeWidget : public QWidget
{
	Q_OBJECT

public:
	HomeWidget(QWidget *parent = Q_NULLPTR);
	~HomeWidget();
protected:
	void mousePressEvent(QMouseEvent *event);

private:
	Ui::HomeWidget ui;
};
