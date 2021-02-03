#pragma once

#include <QWidget>
#include "ui_copybutton.h"
#include <QPushButton>
#include <QAbstractButton>
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"

class CopyButton : public QPushButton
{
	Q_OBJECT

public:
	CopyButton(QWidget *parent = Q_NULLPTR);
	~CopyButton();
protected:
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);

private slots:
	void changeTheme();

private:
	Ui::CopyButton ui;
	void setButtonStyle();

};
