#pragma once

#include <QWidget>
#include <QSCrollArea>
#include <QScrollBar>
#include "ui_sapscrollarea.h"
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
class SAPSCrollArea : public QScrollArea
{
	Q_OBJECT

public:
	SAPSCrollArea(QWidget *parent = Q_NULLPTR);
	~SAPSCrollArea();
private slots:
	void changeTheme();
private:
	Ui::SAPSCrollArea ui;

	void setStyle();
};
