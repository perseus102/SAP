#pragma once

#include <QWidget>
#include "ui_sapcheckbox.h"
#include <QPushButton>
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
class SAPCheckBox : public QPushButton
{
	Q_OBJECT

public:
	SAPCheckBox(QWidget *parent = Q_NULLPTR);
	~SAPCheckBox();
	void setButtonChecked(Qt::CheckState state);
	Qt::CheckState getCheckState();
private slots:
	void changeTheme();
	void boxClicked();
signals:
	void boxSetChecked(Qt::CheckState);
private:
	Ui::SAPCheckBox ui;
	void setButtonStyle(Qt::CheckState state);
	Qt::CheckState m_state;
};
