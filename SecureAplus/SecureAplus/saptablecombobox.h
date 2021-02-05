#pragma once

#include <QWidget>
#include "ui_saptablecombobox.h"
#include <QComboBox>
#include "Config.h"
#include "define.h"
#include "util.h"
#include "appsetting.h"
class SAPTableCombobox : public QComboBox
{
	Q_OBJECT

public:
	SAPTableCombobox(int arrowPadding, QWidget *parent = Q_NULLPTR);
	~SAPTableCombobox();
private slots:
	void changeTheme();
private:
	Ui::SAPTableCombobox ui;
	void setStyle();
	int m_arrowPadding;
};
