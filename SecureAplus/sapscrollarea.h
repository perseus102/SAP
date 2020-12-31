#pragma once

#include <QWidget>
#include <QSCrollArea>
#include <QScrollBar>
#include "ui_sapscrollarea.h"
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
#include <QMargins>
class SAPSCrollArea : public QScrollArea
{
	Q_OBJECT

public:
	SAPSCrollArea(QMargins margins,QWidget *parent = Q_NULLPTR);
	~SAPSCrollArea();
private slots:
	void changeTheme();
	void scrollBarChangeValue(int);
	void scrollBarTimeout();
private:
	Ui::SAPSCrollArea ui;
	QTimer*				m_scrollBarTimer;
	void setStyle();
	QMargins m_margins;
};
