#pragma once

#include <QWidget>
#include "ui_refeshbutton.h"
#include <QPushButton>
#include <QAbstractButton>
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
class RefreshButton : public QPushButton
{
	Q_OBJECT

public:
	RefreshButton(QWidget *parent = Q_NULLPTR);
	~RefreshButton();
signals:
	void signalRefesh();

protected:
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);

private slots:
	void changeTheme();
	void btnClicked();
private:
	Ui::RefeshButton ui;
	void setButtonStyle();
};
