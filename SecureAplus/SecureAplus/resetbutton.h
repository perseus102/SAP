#pragma once

#include <QWidget>
#include "ui_resetbutton.h"
#include <QPushButton>
#include <QAbstractButton>
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
#include "resetdialog.h"
#include "widgettransparent.h"
class ResetButton : public QPushButton
{
	Q_OBJECT

public:
	ResetButton(QWidget *parent = Q_NULLPTR);
	~ResetButton();

signals:
	void signalResetToDefault();

protected:
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);

private slots:
	void changeTheme();
	void btnClicked();

private:
	Ui::ResetButton ui;
	void setButtonStyle();

	WidgetTransparent*	transparent;
	ResetDialog* m_resetDialog;
};
