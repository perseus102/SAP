#pragma once

#include <QWidget>
#include "ui_sapradiobutton.h"
#include <QPushButton>
#include <QAbstractButton>
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
class SAPRadioButton : public QPushButton
{
	Q_OBJECT

public:
	SAPRadioButton(QWidget *parent = Q_NULLPTR);
	~SAPRadioButton();
	void setButtonChecked(Qt::CheckState state);
private slots:
	void changeTheme();
private:
	Ui::SAPRadioButton ui;
	void setButtonStyle(Qt::CheckState state);
	Qt::CheckState m_state;
};
